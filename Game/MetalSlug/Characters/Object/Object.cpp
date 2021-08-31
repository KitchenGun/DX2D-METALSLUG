#include "stdafx.h"
#include "Object.h"
#include "Utilities/Animator.h"

Object::Object(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position,size,rotation)
{
	/*임시*/
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);

	animator->SetCurrentAnimClip(L"temp");
	animator->bLoop = true;
	/*임시*/
	TransformVertices();
}

Object::~Object()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void Object::Update()
{
	PlayerAnimationRect::Update();
	PlayerBlock();
}

void Object::Render()
{
	PlayerAnimationRect::Render();
}

void Object::PlayerBlock()
{
	if (Math::Intersect(this, target))
	{
		target->SetisGround(true);
		if (Math::GroundIntersect(target, this))
		{//오브젝트로 인한 바닥으로 충돌이 되는 경우
			return;
		}
		else if (target->GetBlockDir() == DIRECTION::NONE)
		{
			if (this->GetTransformedCoord().LT.x > target->GetTransformedCoord().LT.x && this->GetTransformedCoord().LT.x < target->GetTransformedCoord().RB.x)
			{
				target->SetBlockDir(DIRECTION::RIGHT);
			}
			else if (this->GetTransformedCoord().RB.x > target->GetTransformedCoord().LT.x && this->GetTransformedCoord().RB.x < target->GetTransformedCoord().RB.x)
			{
				target->SetBlockDir(DIRECTION::LEFT);
			}
		}
	}
	else
	{
		target->SetBlockDir(DIRECTION::NONE);
	}
}
