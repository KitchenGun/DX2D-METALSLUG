#include "stdafx.h"
#include "EnemySoldier.h"
#include "Utilities/Animator.h"

EnemySoldier::EnemySoldier(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:Enemy(position, size, rotation, enemyType)
{
	this->enemyType = enemyType;
	SetAnimation();
	obbInfo = new OBBInfo;

	switch (enemyType)
	{
	case ENEMYTYPE::NONE:
		break;
	case ENEMYTYPE::Grenadier:
		{	
			enemyState = ENEMYSOLDIERSTATE::IDLE;
			//26*44≈©±‚
			SetSize(Vector3(26 * 3, 44 * 3, 1));
			RootPos = Vector3(position.x + 13 * 3, position.y, 0);
			SetClip();
			EnemyHP = 1;
			break;
		}
	default:
		break;
	}
}

EnemySoldier::~EnemySoldier()
{
	Enemy::~Enemy();
}

void EnemySoldier::Update()
{
	if (EnemyHP <= 0)
	{
		Die();
	}
	Enemy::Update();
}

void EnemySoldier::Render()
{
	Enemy::Render();
}

void EnemySoldier::Die()
{
	enemyState = ENEMYSOLDIERSTATE::DIE;
}



void EnemySoldier::SetAnimation()
{
	if (enemyType == ENEMYTYPE::Grenadier)
	{
		//IDLE
		texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
		animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		//ªÁ∏¡
		texture = new Texture2D(L"./_Textures/EnemySoldier/Die/LDie.png");
		animClips.push_back(new AnimationClip(L"LDie", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	}

	animator = new Animator(animClips);

}

void EnemySoldier::SetClip()
{
	switch (enemyState)
	{
		case ENEMYSOLDIERSTATE::IDLE:
		{
			if (dir == DIRECTION::RIGHT)
			{

			}
			else if(dir == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
				animator->SetCurrentAnimClip(L"LIdle");
			}
			break;
		}
		case ENEMYSOLDIERSTATE::DIE:
		{
			animator->bLoop = false;
			if (dir == DIRECTION::RIGHT)
			{

			}
			else if (dir == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/EnemySoldier/Die/LDie.png");
				animator->SetCurrentAnimClip(L"LDie");
			}
			break;
		}
		default:
			break;
	}
}


void EnemySoldier::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//≥ª∫Œø°º≠ transpose«ÿ¡‹
	TransformVertices();
}