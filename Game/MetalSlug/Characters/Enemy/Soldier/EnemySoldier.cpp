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
	Enemy::Update();
	if (beforeEnemyState == ENEMYSOLDIERSTATE::IDLE)
	{
		ScoutRangeCheck();
	}
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		grenadierAni->Update();
		break;
	default:
		break;
	}
	//가장 중요
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

void EnemySoldier::Die()
{
	enemyState = ENEMYSOLDIERSTATE::DIE;
}

void EnemySoldier::ScoutRangeCheck()
{
	if (pm->GetPlayerList().size() <= 0)
	{
		enemyState = ENEMYSOLDIERSTATE::IDLE;
	}
	else if(beforeEnemyState == ENEMYSOLDIERSTATE::IDLE)
	{
		for (Player* tempP : pm->GetPlayerList())
		{
			if (Math::Distance(tempP->GetPointPos(), r.Point) < 800)
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
						//도망치도록 제작
						nextEnemyState = ENEMYSOLDIERSTATE::RUN;
					}
					else
					{//플레이어보다 오른쪽에 있을 경우
						dir = DIRECTION::LEFT;
						enemyState = ENEMYSOLDIERSTATE::SURPRISE;
						//공격하도록 제작
					}
				}
			}
		}
	}
	else if (beforeEnemyState == ENEMYSOLDIERSTATE::SURPRISE)
	{
		if (!EnemyAnimator->isFirstPlay)
		{
			for (Player* tempP : pm->GetPlayerList())
			{
				switch (nextEnemyState)
				{
				case ENEMYSOLDIERSTATE::RUN:
					enemyState = ENEMYSOLDIERSTATE::RUN;
				case ENEMYSOLDIERSTATE::THROW:
					enemyState = ENEMYSOLDIERSTATE::THROW;
				case ENEMYSOLDIERSTATE::KNIFE:
					enemyState = ENEMYSOLDIERSTATE::KNIFE;
				default:
					break;
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