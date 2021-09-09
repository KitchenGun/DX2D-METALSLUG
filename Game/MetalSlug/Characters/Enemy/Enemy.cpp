#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:PlayerAnimationRect(position, size, rotation)
{

}

Enemy::~Enemy()
{
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
		Move({ 0,GravatiyPower,0 });
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
		this->position += tempPos;
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
	pos = Vector3(pos.x, (obbInfo->Gradient * pos.x) + obbInfo->alphaVal, 0);
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
			GravatiyPower = -5;
		}
	}
}

void Enemy::Die()
{
	//자식 객체에서 정의
}

void Enemy::Hit(DAMAGE val,Projectile* tempProjectile)
{
	static Projectile *PrevTemp;
	Projectile *NowTemp;
	NowTemp = tempProjectile;
	cout << EnemyHP << endl;
	
	if (tempProjectile == nullptr)
	{
		EnemyHP -= val;
		return;
	}

	if (NowTemp!=PrevTemp)
	{
		EnemyHP -= val;
		cout << EnemyHP << endl;
	}
	PrevTemp = NowTemp;
	
}


