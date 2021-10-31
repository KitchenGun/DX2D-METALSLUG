#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:PlayerAnimationRect(position, size, rotation)
{
	this->enemyType = enemyType;
	if (enemyType == ENEMYTYPE::Helicopter || enemyType == ENEMYTYPE::Boss)
	{
	
	}
	else
	{
		ColliderSizeChange(COLLIDER::BIG);
	}
}

Enemy::~Enemy()
{
	SAFE_DELETE(EM);
	SAFE_DELETE(epm);
	SAFE_DELETE(pm);
	SAFE_DELETE(PrevTemp);
	SAFE_DELETE(obbInfo);
	PlayerAnimationRect::~PlayerAnimationRect();
}

void Enemy::Update()
{
	//jump
	Jump();

	if (isGround)
	{
		isJumpEnd = false;
		nJumpCount = 0;
	}
	else
	{
		if (enemyType == ENEMYTYPE::Boss || enemyType == ENEMYTYPE::Helicopter)
		{

		}
		else
		{
			Move({ 0,GravatiyPower,0 });
		}
	}

	PlayerAnimationRect::Update();
}

void Enemy::Render()
{
	PlayerAnimationRect::Render();
}

void Enemy::Move(Vector3 tempPos)
{
	if (obbInfo->isObb && !isJump)
	{
		ObbGroundMove(tempPos);
	}
	else
	{
		this->position += tempPos * Time::Delta();
		D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

		world = S * R * T;
		WB->SetWorld(world);

		RootPos = position + Vector3(size.x / 2, 0, 0);
		TransformVertices();
	}
}

void Enemy::ObbGroundMove(Vector3 tempPos)
{
	Vector3 pos = Vector3(position.x + tempPos.x, 0, 0);
	pos = Vector3(pos.x, (obbInfo->Gradient * pos.x) + obbInfo->alphaVal, 0) * Time::Delta();
	this->position = pos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);

	RootPos = position + Vector3(size.x / 2, 0, 0);
	TransformVertices();
}

void Enemy::Jump()
{
	static float fJumpTime = 0;
	if (isJump)
	{
		//상승 상황 점프
		if (fJumpPower <= fMaxJumpSpeed)
		{
			fJumpPower = fMaxJumpSpeed - Math::Lerpf(0, fMaxJumpSpeed, fJumpTime);
			Move({ 0,fJumpPower,0 });
		}


		if (fJumpTime >= 1)
		{
			fJumpPower = 0;
			isJump = false;
			isJumpEnd = true;
		}
		fJumpTime += Time::Delta();
	}
	else
	{
		if (isJumpEnd == true)
		{
			GravatiyPower *= (fJumpTime);
		}
		else
		{
			fJumpTime = 0;
			GravatiyPower = -600;
		}
	}
}

void Enemy::Die()
{
	//자식 객체에서 정의
	ColliderSizeChange(COLLIDER::NONE);
}

void Enemy::Hit(DAMAGE val,Projectile* tempProjectile)
{
	//HLSL작업
	SB->SetHit(true);
	Projectile *NowTemp;
	NowTemp = tempProjectile;
	HitBy = tempProjectile->GetPT();
	if (tempProjectile == nullptr)
	{
		EnemyHP -= val;
		return;
	}
	else if (NowTemp!=PrevTemp)
	{
		EnemyHP -= val;
	}
	PrevTemp = NowTemp;

}

void Enemy::ColliderSizeChange(COLLIDER val)
{
	if (val == COLLIDER::SMALL)
	{
		this->size = Vector3(90, 25 * 3, 1);
	}
	else if (val == COLLIDER::BIG)
	{
		this->size = Vector3(90, 40 * 3, 1);
	}
	else if (val == COLLIDER::NONE)
	{
		this->size = Vector3(1, 1, 1);
	}

	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}



