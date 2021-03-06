#include "stdafx.h"
#include "Object.h"
#include "Utilities/Animator.h"

Object::Object(Vector3 position, Vector3 size, float rotation, ObjectType OT, bool isRender)
	:PlayerAnimationRect(position,size,rotation),
	IsRender(isRender),
	ot(OT)
{
	TransformVertices();
}

Object::~Object()
{
	for (Projectile* tempP : vecHitProjectile)
	{
		SAFE_DELETE(tempP);
	}
	SAFE_DELETE(PrevTemp);
	SAFE_DELETE(PPM);
	SAFE_DELETE(target);
	SAFE_DELETE(EM);
	PlayerAnimationRect::~PlayerAnimationRect();
}

void Object::Update()
{
	PlayerAnimationRect::Update();
}

void Object::Render()
{
	if (IsRender)
	{
		PlayerAnimationRect::Render();
	}
}

void Object::PlayerBlock()
{
	if (Math::Intersect(this, target->GetPlayer()))
	{
		if (Math::GroundIntersect(target->GetPlayer(), this))
		{//오브젝트로 인한 바닥으로 충돌이 되는 경우
			target->GetPlayer()->SetisObject(true);
			return;
		}
		else if (target->GetPlayer()->GetBlockDir() == DIRECTION::NONE)
		{
			if (this->GetTransformedCoord().LT.x > target->GetPlayer()->GetTransformedCoord().LT.x && this->GetTransformedCoord().LT.x < target->GetPlayer()->GetTransformedCoord().RB.x)
			{
				target->GetPlayer()->SetBlockDir(DIRECTION::RIGHT);
			}
			else if (this->GetTransformedCoord().RB.x > target->GetPlayer()->GetTransformedCoord().LT.x && this->GetTransformedCoord().RB.x < target->GetPlayer()->GetTransformedCoord().RB.x)
			{
				target->GetPlayer()->SetBlockDir(DIRECTION::LEFT);
			}
		}
	}
	else
	{
		target->GetPlayer()->SetisObject(false);
		target->GetPlayer()->SetBlockDir(DIRECTION::NONE);
	}
}

void Object::EnemyBlock()
{
	for (Enemy* tempE : EM->GetEnemyList())
	{
		if (Math::Intersect(this, tempE))
		{
			if (Math::GroundIntersect(tempE, this))
			{//오브젝트로 인한 바닥으로 충돌이 되는 경우
				tempE->SetisGround(true);
			}
			if (tempE->GetBlockDir() == DIRECTION::NONE)
			{
				if (this->GetTransformedCoord().LT.x > tempE->GetTransformedCoord().LT.x && this->GetTransformedCoord().LT.x < tempE->GetTransformedCoord().RB.x)
				{
					tempE->SetBlockDir(DIRECTION::RIGHT);
				}
				else if (this->GetTransformedCoord().RB.x > tempE->GetTransformedCoord().LT.x && this->GetTransformedCoord().RB.x < tempE->GetTransformedCoord().RB.x)
				{
					tempE->SetBlockDir(DIRECTION::LEFT);
				}
			}
		}
		else
		{
			tempE->SetBlockDir(DIRECTION::NONE);
		}
	}
}

void Object::Hit(DAMAGE val, Projectile* tempProjectile)
{
	if (ot == ObjectType::BUILDING|| ot == ObjectType::BOX)
	{
		Projectile* NowTemp;
		NowTemp = tempProjectile;
	
		bool TempSearchResult = false;

		for (Projectile* tempP : vecHitProjectile)
		{
			if (tempP == NowTemp)
			{
				TempSearchResult = true;
			}
		}
		//수류탄 중복 데미지 때문에 이렇게 처리
		if(TempSearchResult == false)
		{
			if (tempProjectile == nullptr)
			{
				ObjHP -= val;
				return;
			}
			else if (NowTemp != PrevTemp)
			{
				ObjHP -= val;
			}
			if (NowTemp->GetPT() == PROJECTILETYPE::Grenade)
			{
				PrevTemp = NowTemp;
				vecHitProjectile.push_back(PrevTemp);
			}
		}
	}
}

