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
			EnemyHP = 1;
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
	if (!isDie)
	{
		MoveFirePos();
		if (beforeEnemyState == ENEMYSOLDIERSTATE::IDLE || beforeEnemyState == ENEMYSOLDIERSTATE::WALK)
		{
			ScoutRangeCheck();
		}
		Move();
		ATK();
		//가장 중요
		GroundCheck();
		HPCheck();
		beforeEnemyState = enemyState;
	}
	else
	{
		static float DeltaTime = 0;

		if (DeltaTime > 2.0f)
		{
			DeltaTime = 0;
			isNeedDestroy = true;
		}
		else
			DeltaTime += Time::Delta();
	}
	
	
	Enemy::Update();
	//애니메이션
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		grenadierAni->Update();
		break;
	default:
		break;
	}
	
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
			if (BlockDir != DIRECTION::LEFT)
			{
				Enemy::Move(Vector3(-walkSpeed, 0, 0));
			}
			else
			{
				dir = DIRECTION::RIGHT;
			}
		}
		else if (dir == DIRECTION::RIGHT)
		{
			if (BlockDir != DIRECTION::RIGHT)
			{
				Enemy::Move(Vector3(walkSpeed, 0, 0));
			}
			else
			{
				dir = DIRECTION::LEFT;
			}
		}
	}
	else if (enemyState == ENEMYSOLDIERSTATE::RUN)
	{
		if (dir == DIRECTION::LEFT)
		{
			if (BlockDir != DIRECTION::LEFT)
			{
				Enemy::Move(Vector3(-runSpeed, 0, 0));
			}
		}
		else if (dir == DIRECTION::RIGHT)
		{
			if (BlockDir != DIRECTION::RIGHT)
			{
				Enemy::Move(Vector3(runSpeed, 0, 0));
			}
		}
	}
}

void EnemySoldier::Die()
{
	isDie = true;
	enemyState = ENEMYSOLDIERSTATE::DIE;
	Enemy::Die();
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
			isSpot = true;
		}
	}
	else if (beforeEnemyState == ENEMYSOLDIERSTATE::IDLE)
	{
		static float AtkRate = 2;
		static float DeltaTime = 0;
		if (DeltaTime > AtkRate)
		{
			DeltaTime = 0;
			if (EnemyAnimator->GetIndex() >= 2)
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
		else
			DeltaTime += Time::Delta();
	}

	if (beforeEnemyState == ENEMYSOLDIERSTATE::KNIFE)
	{
		if (EnemyAnimator->GetIndex() == 10)
		{//데미지 주는 구간
			if (!isCreateProjectile)
			{
				if (dir == DIRECTION::LEFT)
				{
					epm->AddBullet(firePos.Pos - Vector3(20, 20 * 3, 0), Vector3(35 * 3, 20 * 3, 0), 0, dir, PROJECTILETYPE::KNIFE);
				}
				else if (dir == DIRECTION::RIGHT)
				{
					epm->AddBullet(firePos.Pos - Vector3(20, 20 * 3, 0), Vector3(-20 * 3, 20 * 3, 0), 0, dir, PROJECTILETYPE::KNIFE);
				}
			}
			isCreateProjectile = true;
			
		}
		else if (!EnemyAnimator->isFirstPlay && enemyState == ENEMYSOLDIERSTATE::KNIFE)
		{
			beforeEnemyState = ENEMYSOLDIERSTATE::KNIFE;
			enemyState = ENEMYSOLDIERSTATE::IDLE;
			isCreateProjectile = false;

			for (Projectile* temp : epm->GetList())
			{
				if (temp->GetPT() == PROJECTILETYPE::KNIFE)
				{
					epm->RemoveProjectile(temp);
				}
			}
			nextEnemyState = ENEMYSOLDIERSTATE::IDLE;
		}
	}
	else if (beforeEnemyState == ENEMYSOLDIERSTATE::THROW)
	{
		if (EnemyAnimator->GetIndex() == 10)
		{//던지는 구간
			if (!isCreateProjectile)
			{
				epm->AddGrenade(firePos.Pos, Vector3(24 * 3, 24 * 3, 0), 0, dir, PROJECTILETYPE::EnemyGrenade);
				isCreateProjectile = true;
			}
		}
		else if (!EnemyAnimator->isFirstPlay&&enemyState==ENEMYSOLDIERSTATE::THROW)
		{
			beforeEnemyState = ENEMYSOLDIERSTATE::THROW;
			enemyState= ENEMYSOLDIERSTATE::IDLE;
			isCreateProjectile = false;
			nextEnemyState = ENEMYSOLDIERSTATE::IDLE;
		}
	}
}

void EnemySoldier::MoveFirePos()
{
	if (dir == DIRECTION::LEFT)
	{
		firePos.Pos = position + Vector3(15 * 3, 55 * 3, 0);
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
	static Player* target = nullptr;
	if (target == nullptr)
	{
		isSpot = false;
	}
	if (ppm->GetPlayerList().size() <= 0)
	{
		enemyState = ENEMYSOLDIERSTATE::IDLE;
		target = nullptr;
	}
	else 
	{
		if (ppm->GetPlayer() != nullptr)
		{
			if (Math::Distance(ppm->GetPlayer()->GetPointPos(), r.Point) < 600)
			{
				if (dir == DIRECTION::LEFT)
				{
					if (r.Point.x - ppm->GetPlayer()->GetPointPos().x <= 0)
					{//플레이어보다 왼쪽에 있을 경우
						dir = DIRECTION::LEFT;
						enemyState = ENEMYSOLDIERSTATE::WALK;
					}
					else
					{//플레이어보다 오른쪽에 있을 경우
						dir = DIRECTION::LEFT;
						if (target == nullptr)
						{
							enemyState = ENEMYSOLDIERSTATE::SURPRISE;
						}
						else
						{
							if (!isSpot)
							{
								enemyState = ENEMYSOLDIERSTATE::SURPRISE;
							}
							else if (isSpot == true)
							{
								enemyState = ENEMYSOLDIERSTATE::IDLE;
							}
						}
						//공격하도록 제작
						if (Math::Distance(ppm->GetPlayer()->GetPointPos(), r.Point) < 150)
						{
							target = ppm->GetPlayer();
							nextEnemyState = ENEMYSOLDIERSTATE::KNIFE;
						}
						else
						{
							target = ppm->GetPlayer();
							nextEnemyState = ENEMYSOLDIERSTATE::THROW;
						}
					}
				}
				else if (dir == DIRECTION::RIGHT)
				{
					if (r.Point.x - ppm->GetPlayer()->GetPointPos().x <= 0)
					{//플레이어보다 왼쪽에 있을 경우
						dir = DIRECTION::RIGHT;
						if (target == nullptr)
						{
							enemyState = ENEMYSOLDIERSTATE::SURPRISE;
						}
						else
						{
							if (!isSpot)
							{
								enemyState = ENEMYSOLDIERSTATE::SURPRISE;
							}
							else if (isSpot == true)
							{
								enemyState = ENEMYSOLDIERSTATE::IDLE;
							}
						}
						//공격하도록 제작
						if (Math::Distance(ppm->GetPlayer()->GetPointPos(), r.Point) < 150)
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
				enemyState = ENEMYSOLDIERSTATE::WALK;
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