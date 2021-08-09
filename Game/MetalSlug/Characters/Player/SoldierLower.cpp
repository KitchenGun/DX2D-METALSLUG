#include "stdafx.h"
#include "SoldierLower.h"
#include "Utilities/Animator.h"

SoldierLower::SoldierLower(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
	animator->SetCurrentAnimClip(L"Idle");
	animator->bLoop=true;
}

SoldierLower::~SoldierLower()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void SoldierLower::Update()
{
	PlayerAnimationRect::Update();
}

void SoldierLower::Render()
{
	PlayerAnimationRect::Render();
}

void SoldierLower::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	texture = new Texture2D(L"./_Textures/Character/Idle/Lower.png");
	//idle
	animClips.push_back(new AnimationClip(L"Idle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
}
