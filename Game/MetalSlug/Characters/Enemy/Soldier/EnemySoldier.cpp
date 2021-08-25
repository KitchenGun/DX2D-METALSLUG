#include "stdafx.h"
#include "EnemySoldier.h"
#include "Utilities/Animator.h"

EnemySoldier::EnemySoldier(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:Enemy(position, size, rotation, enemyType)
{
	this->enemyType = enemyType;
	SetAnimation();

	switch (enemyType)
	{
	case ENEMYTYPE::NONE:
		break;
	case ENEMYTYPE::Grenadier:
		{	
			//26*44크기
			enemyState = ENEMYSOLDIERSTATE::IDLE;
			SetSize(Vector3(26 * 3, 44 * 3, 1));
			SetClip();
			break;
		}
	default:
		break;
	}
}

EnemySoldier::~EnemySoldier()
{

}

void EnemySoldier::Update()
{
	Enemy::Update();
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

}

void EnemySoldier::Render()
{
	Enemy::Render();
}



void EnemySoldier::SetAnimation()
{
	if (enemyType == ENEMYTYPE::Grenadier)
	{
		//IDLE
		texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
		animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		//사망
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
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}

void EnemySoldier::Move(Vector3 pos)
{
	PlayerAnimationRect::Move(pos);
}

void EnemySoldier::Jump()
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
