#include "stdafx.h"
#include "Rock1.h"
#include "Utilities/Animator.h"

Rock1::Rock1(Vector3 position, Vector3 size, float rotation)
	:
	Object(position,size,rotation)
{
	texture = new Texture2D(L"./_Textures/Object/Rock/Idle.png");
	animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);

	animator->SetCurrentAnimClip(L"temp");
	animator->bLoop = true;
}

Rock1::~Rock1()
{
	Object::~Object();
}

void Rock1::Update()
{
	Object::Update();
}

void Rock1::Render()
{
	Object::Render();
}
