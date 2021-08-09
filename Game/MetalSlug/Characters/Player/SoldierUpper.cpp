#include "stdafx.h"
#include "SoldierUpper.h"
#include "Utilities/Animator.h"

SoldierUpper::SoldierUpper(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
	animator->SetCurrentAnimClip(L"Idle");
	animator->bLoop = true;
}

SoldierUpper::~SoldierUpper()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void SoldierUpper::Update()
{
	PlayerAnimationRect::Update();
}

void SoldierUpper::Render()
{
	PlayerAnimationRect::Render();
}

void SoldierUpper::SetAnimation()
{//�ؽ��� �ּ� �Է��Ͽ��� �ؽ��� �ڿ� ����
	texture = new Texture2D(L"./_Textures/Character/Idle/Upper.png");
	//idle
	animClips.push_back(new AnimationClip(L"Idle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
}
