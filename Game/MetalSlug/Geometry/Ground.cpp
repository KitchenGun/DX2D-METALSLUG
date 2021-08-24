#include "stdafx.h"
#include "Ground.h"
#include "Utilities/Animator.h"

Ground::Ground(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect( position,  size,  rotation)
{
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);

	animator->SetCurrentAnimClip(L"temp");
	animator->bLoop = true;
	TransformVertices();
	cout << GetTransformedCoord().LT.x << endl;
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
