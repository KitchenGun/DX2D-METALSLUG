#include "stdafx.h"
#include "Ground.h"
#include "Utilities/Animator.h"

Ground::Ground(Vector3 position, Vector3 size, float rotation,bool isObb)
	:PlayerAnimationRect( position,  size,  rotation),
	isObb(isObb)
{
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);

	animator->SetCurrentAnimClip(L"temp");
	animator->bLoop = true;
	TransformVertices();
}

Ground::~Ground()
{
}

void Ground::Update()
{
	PlayerAnimationRect::Update();
}

void Ground::Render()
{
	PlayerAnimationRect::Render();
}
