#include "stdafx.h"
#include "SFX.h"
#include "Utilities/Animator.h"

SFX::SFX(Vector3 pos, Vector3 size, float rotation, SFXTYPE sfxt)
	:AnimationRect(pos,size,rotation),
	SFXT(sfxt)
{

}

SFX::~SFX()
{
	AnimationRect::~AnimationRect();
}

void SFX::Update()
{
	AnimationRect::Update();
}

void SFX::Render()
{
	AnimationRect::Render();
}
