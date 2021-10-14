#include "stdafx.h"
#include "BulletSFX.h"
#include "Utilities/Animator.h"

BulletSFX::BulletSFX(Vector3 pos, SFXTYPE sfxt, DIRECTION dir)
	:SFX(pos, size, rotation, sfxt),
	dir(dir),
	sfxt(sfxt)
{
	SetSFX();
	animator->bLoop = false;
	switch (sfxt)
	{
	case SFXTYPE::BULLET:
		animator->playRate = 1.0f / 60;
		animator->SetCurrentAnimClip(L"NormalBulletExplosion");
		switch (dir)
		{
		case DIRECTION::NONE:
			SetPos(Vector3(0, 10 * 3, 0));
			SetSize(Vector3(32 * 2, 68 * 2, 1));
			break;
		case DIRECTION::LEFT:
			SetSize(Vector3(68 * 2, 32 * 2, 1));
			break;				 
		case DIRECTION::RIGHT:	
			SetSize(Vector3(68 * 2, 32 * 2, 1));
			break;
		default:
			break;
		}
		break;
	case SFXTYPE::ENEMYGRENADE:
		animator->SetCurrentAnimClip(L"EnemyGrenadeExplosion");
		SetSize(Vector3(32 * 3, 32 * 3, 1));
		break; 
	case SFXTYPE::BLOOD:
		animator->SetCurrentAnimClip(L"Blood");
		switch (dir)
		{
		case DIRECTION::NONE:
			break;
		case DIRECTION::LEFT:
			SetPos(Vector3(-5 * 3, 0 * 3, 0));
			break;
		case DIRECTION::RIGHT:
			SetPos(Vector3(20*3, 0 * 3, 0));
			break;
		default:
			break;
		}
		SetSize(Vector3(47 * 2, 49 * 2, 1));
		break;
	default:
		break;
	}
}

BulletSFX::~BulletSFX()
{
	SFX::~SFX();
}

void BulletSFX::Update()
{
	SFX::Update();

	switch (sfxt)
	{
	case SFXTYPE::BULLET:
		
		if (animator->GetIndex() >= 11)
		{
			isNeedDestroy = true;
		}
		break;
	case SFXTYPE::ENEMYGRENADE:
		if (animator->GetIndex() >= 7)
		{
			isNeedDestroy = true;
		}
		break;
	case SFXTYPE::BLOOD:

		if (animator->GetIndex() >= 7)
		{
			isNeedDestroy = true;
		}
		break;
	default:
		break;
	}
	
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
			texture = new Texture2D(L"./_Textures/SFX/Explosion/NormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case DIRECTION::LEFT:
			texture = new Texture2D(L"./_Textures/SFX/Explosion/LNormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case DIRECTION::RIGHT:
			texture = new Texture2D(L"./_Textures/SFX/Explosion/RNormalBulletExplosion.png");
			animClips.push_back(new AnimationClip(L"NormalBulletExplosion", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		default:
			break;
		}
		break;
	case SFXTYPE::ENEMYGRENADE:
		texture = new Texture2D(L"./_Textures/SFX/Explosion/EnemyGrenadeExplosion.png");
		animClips.push_back(new AnimationClip(L"EnemyGrenadeExplosion", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case SFXTYPE::BLOOD:
		texture = new Texture2D(L"./_Textures/SFX/Explosion/Blood.png");
		animClips.push_back(new AnimationClip(L"Blood", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	default:
		break;
	}
	animator = new Animator(animClips);
}

void BulletSFX::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}

void BulletSFX::SetPos(Vector3 tempPos)
{
	this->position += tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}
