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
			RootPos = Vector3(position.x + 13 * 3, position.y, 0);
			grenadierAni = new GrenadierAni(position,size,rotation,this);
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
}

void EnemySoldier::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}