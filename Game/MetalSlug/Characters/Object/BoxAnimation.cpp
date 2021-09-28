#include "stdafx.h"
#include "BoxAnimation.h"
#include "Utilities/Animator.h"

BoxAnimation::BoxAnimation(Vector3 position, Vector3 size, float rotation, ItemBox* box)
	:PlayerAnimationRect(position,size,rotation),
	box(box)
{
	texture = new Texture2D(L"./_Textures/Object/Item/Box/BoxIdle.png");
	animClips.push_back(new AnimationClip(L"BoxIdle", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Object/Item/Box/BoxDestroy.png");
	animClips.push_back(new AnimationClip(L"BoxDestroy", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->bLoop = false;
	texture = new Texture2D(L"./_Textures/Object/Item/Box/BoxIdle.png");
	animator->SetCurrentAnimClip(L"BoxIdle");
}

BoxAnimation::~BoxAnimation()
{
	SAFE_DELETE(box);
}

void BoxAnimation::Update()
{
	if (box->GetState()==BOXSTATE::DESTROY)
	{
		texture = new Texture2D(L"./_Textures/Object/Item/Box/BoxDestroy.png");
		animator->SetCurrentAnimClip(L"BoxDestroy");
	}
	PlayerAnimationRect::Update();
}

void BoxAnimation::Render()
{
	PlayerAnimationRect::Render();
}
