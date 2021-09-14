#include "stdafx.h"
#include "EnemySoldier.h"
#include "Utilities/Animator.h"

EnemySoldier::EnemySoldier(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:Enemy(position, size, rotation, enemyType)
{
	this->enemyType = enemyType;
	obbInfo = new OBBInfo;

	//temp
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"TestBox", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->SetCurrentAnimClip(L"TestBox");
	//temp

	switch (enemyType)
	{
	case ENEMYTYPE::NONE:
		break;
	case ENEMYTYPE::Grenadier:
		{	
			enemyState = ENEMYSOLDIERSTATE::IDLE;
			dir = DIRECTION::LEFT;
			SetSize(Vector3(26 * 3, 44 * 3, 1));
			RootPos = position + Vector3(size.x / 2, 0, 0);
			grenadierAni = new GrenadierAni(position,size,rotation,this);
			EnemyAnimator = grenadierAni->GetAnimator();
			EnemyHP = 10;
			walkSpeed = 250;
			runSpeed = 350.0f;;
			break;
		}
	default:
		break;
	}
}

EnemySoldier::~EnemySoldier()
{
	SAFE_DELETE(grenadierAni);
	Enemy::~Enemy();
}

void EnemySoldier::Update()
{
	MoveFirePos();
	Enemy::Update();
	if (beforeEnemyState == ENEMYSOLDIERSTATE::IDLE)
	{
		ScoutRangeCheck();
	}
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		grenadierAni->Update();
		Move();
		ATK();
		break;
	default:
		break;
	}
	//가장 중요
	GroundCheck();
	HPCheck();
	beforeEnemyState = enemyState;
}

void EnemySoldier::Render()
{
	Enemy::Render();
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		grenadierAni->Render();
		break;
	default:
		break;
	}
}

void EnemySoldier::HPCheck()
{
	if (EnemyHP <= 0)
	{
		Die();
	}
}

void EnemySoldier::GroundCheck()
{
	if (!isGround)
	{
		enemyState = ENEMYSOLDIERSTATE::JUMP;
	}
	else
	{
		if (beforeEnemyState == ENEMYSOLDIERSTATE::JUMP)
		{
			enemyState = ENEMYSOLDIERSTATE::IDLE;
		}
	}
}

void EnemySoldier::Move()
{
	if (enemyState == ENEMYSOLDIERSTATE::WALK)
	{
		if (dir == DIRECTION::LEFT)
		{
			Enemy::Move(Vector3(-walkSpeed, 0, 0));
		}
		else if (dir == DIRECTION::RIGHT)
		{
			Enemy::Move(Vector3(walkSpeed, 0, 0));
		}
	}
	else if (enemyState == ENEMYSOLDIERSTATE::RUN)
	{
		if (dir == DIRECTION::LEFT)
		{
			Enemy::Move(Vector3(-runSpeed, 0, 0));
		}
		else if (dir == DIRECTION::RIGHT)
		{
			Enemy::Move(Vector3(runSpeed, 0, 0));
		}
	}
}

void EnemySoldier::Die()
{
	enemyState = ENEMYSOLDIERSTATE::DIE;
}

void EnemySoldier::ATK()
{
	if (beforeEnemyState == ENEMYSOLDIERSTATE::SURPRISE)
	{
		if (EnemyAnimator->GetIndex()>=10)
		{
			switch (nextEnemyState)
			{
			case ENEMYSOLDIERSTATE::RUN:
				enemyState = ENEMYSOLDIERSTATE::RUN;
				break;
			case ENEMYSOLDIERSTATE::THROW:
				enemyState = ENEMYSOLDIERSTATE::THROW;
				break;
			case ENEMYSOLDIERSTATE::KNIFE:
				enemyState = ENEMYSOLDIERSTATE::KNIFE;
				break;
			default:
				break;
			}
		}
	}

	if (beforeEnemyState == ENEMYSOLDIERSTATE::KNIFE)
	{
		if (EnemyAnimator->GetIndex() == 10)
		{//데미지 주는 구간
			cout << epm << endl;
		}
		else if (EnemyAnimator->GetIndex() == 12)
		{
			enemyState = ENEMYSOLDIERSTATE::IDLE;
		}
	}
	else if (beforeEnemyState == ENEMYSOLDIERSTATE::THROW)
	{
		if (EnemyAnimator->GetIndex() == 10)
		{//던지는 구간
			epm->AddGrenade(firePos.Pos, Vector3(24 * 3, 24 * 3, 0), 0, dir, PROJECTILETYPE::EnemyGrenade);
		}
		else if (EnemyAnimator->GetIndex() == 17)
		{
			enemyState = ENEMYSOLDIERSTATE::IDLE;
		}
	}
}

void EnemySoldier::MoveFirePos()
{
	if (dir == DIRECTION::LEFT)
	{
		firePos.Pos = position + Vector3(11 * 3, 55 * 3, 0);
		firePos.Rotation = 90.0f;
	}
	else if (dir == DIRECTION::RIGHT)
	{
		firePos.Pos = position + Vector3(12 * 3, 55 * 3, 0);
		firePos.Rotation = 90.0f;
	}
}

void EnemySoldier::ScoutRangeCheck()
{
	static Player* Target = nullptr;
	if (ppm->GetPlayerList().size() <= 0)
	{
		enemyState = ENEMYSOLDIERSTATE::IDLE;
	}
	else if(beforeEnemyState == ENEMYSOLDIERSTATE::IDLE)
	{
		for (Player* tempP : ppm->GetPlayerList())
		{
			if (Math::Distance(tempP->GetPointPos(), r.Point) < 800)
			{
				if (tempP != Target)
				{
					if (dir == DIRECTION::LEFT)
					{
						if (r.Point.x - tempP->GetPointPos().x <= 0)
						{//플레이어보다 왼쪽에 있을 경우
							dir = DIRECTION::LEFT;
							enemyState = ENEMYSOLDIERSTATE::WALK;
						}
						else
						{//플레이어보다 오른쪽에 있을 경우
							dir = DIRECTION::LEFT;
							enemyState = ENEMYSOLDIERSTATE::SURPRISE;
							//공격하도록 제작
							if (Math::Distance(tempP->GetPointPos(), r.Point) < 150)
							{
								nextEnemyState = ENEMYSOLDIERSTATE::KNIFE;
							}
							else
							{
								nextEnemyState = ENEMYSOLDIERSTATE::THROW;
							}
						}
					}
					else if (dir == DIRECTION::RIGHT)
					{
						if (r.Point.x - tempP->GetPointPos().x <= 0)
						{//플레이어보다 왼쪽에 있을 경우
							dir = DIRECTION::RIGHT;
							enemyState = ENEMYSOLDIERSTATE::SURPRISE;
							//공격하도록 제작
							if (Math::Distance(tempP->GetPointPos(), r.Point) < 150)
							{
								nextEnemyState = ENEMYSOLDIERSTATE::KNIFE;
							}
							else
							{
								nextEnemyState = ENEMYSOLDIERSTATE::THROW;
							}
						}
						else
						{//플레이어보다 오른쪽에 있을 경우
							dir = DIRECTION::LEFT;
							enemyState = ENEMYSOLDIERSTATE::SURPRISE;
							//도망치도록 제작
							nextEnemyState = ENEMYSOLDIERSTATE::RUN;
						}
					}
				}
				else
				{
					if (dir == DIRECTION::LEFT)
					{
						if (r.Point.x - tempP->GetPointPos().x <= 0)
						{//플레이어보다 왼쪽에 있을 경우
							dir = DIRECTION::LEFT;
							enemyState = ENEMYSOLDIERSTATE::WALK;
						}
						else
						{//플레이어보다 오른쪽에 있을 경우
							dir = DIRECTION::LEFT;
							//공격하도록 제작
							if (Math::Distance(tempP->GetPointPos(), r.Point) < 150)
							{
								enemyState = ENEMYSOLDIERSTATE::KNIFE;
							}
							else
							{
								enemyState = ENEMYSOLDIERSTATE::THROW;
							}
						}
					}
					else if (dir == DIRECTION::RIGHT)
					{
						if (r.Point.x - tempP->GetPointPos().x <= 0)
						{//플레이어보다 왼쪽에 있을 경우
							dir = DIRECTION::RIGHT;
							//공격하도록 제작
							if (Math::Distance(tempP->GetPointPos(), r.Point) < 150)
							{
								enemyState = ENEMYSOLDIERSTATE::KNIFE;
							}
							else
							{
								enemyState = ENEMYSOLDIERSTATE::THROW;
							}
						}
						else
						{//플레이어보다 오른쪽에 있을 경우
							dir = DIRECTION::LEFT;
							//도망치도록 제작
							nextEnemyState = ENEMYSOLDIERSTATE::RUN;
						}
					}
				}
			}
		}
	}
}

void EnemySoldier::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}