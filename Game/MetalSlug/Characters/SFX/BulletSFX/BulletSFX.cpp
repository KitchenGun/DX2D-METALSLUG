#include "stdafx.h"
#include "BulletSFX.h"
#include "Utilities/Animator.h"

BulletSFX::BulletSFX(Vector3 pos, Vector3 size, float rotation, SFXTYPE sfxt, DIRECTION dir)
	:SFX(pos, size, rotation, sfxt),
	dir(dir)
{
	
}

BulletSFX::~BulletSFX()
{
	SFX::~SFX();
}

void BulletSFX::Update()
{
	SFX::Update();
}

void BulletSFX::Render()
{
	SFX::Render();
}

void BulletSFX::SetRotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R, this->rotation);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void BulletSFX::SetSFX()
{
	switch (sfxt)
	{
	case SFXTYPE::BULLET:
		switch (dir)
		{
		case DIRECTION::NONE:
			texture = new Texture2D(L"./_Textures/SFX/Jump/Explosion/NormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case DIRECTION::LEFT:
			texture = new Texture2D(L"./_Textures/SFX/Jump/Explosion/NormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case DIRECTION::RIGHT:
			texture = new Texture2D(L"./_Textures/SFX/Jump/Explosion/NormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		default:
			break;
		}
		break;
	case SFXTYPE::ENEMYGRENADE:
		break;
	default:
		break;
	}
	animator = new Animator(animClips);
}