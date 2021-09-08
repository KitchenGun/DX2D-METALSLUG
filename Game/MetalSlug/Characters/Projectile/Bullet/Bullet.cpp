#include "stdafx.h"
#include "Bullet.h"
#include "Utilities/Animator.h"
Bullet::Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
	:Projectile(position, size, rotation,dir,BT)
{
	texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
	animClips.push_back(new AnimationClip(L"NormalBullet", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"TestBox", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	
	switch (pt)
	{
	case PROJECTILETYPE::NONE:
	break;
	case PROJECTILETYPE::KNIFE:
		Damage = 3; 
		Speed = 0.0f;
		texture = new Texture2D(L"./_Textures/TestBox.png");
		animator->SetCurrentAnimClip(L"TestBox");
		break;
	case PROJECTILETYPE::PISTOL:
		Damage = 1;
		Speed = 2000.0f;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
		animator->SetCurrentAnimClip(L"NormalBullet");
	break;
	case PROJECTILETYPE::HEAVY:
		Damage = 1;
		Speed = 2000;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
		animator->SetCurrentAnimClip(L"NormalBullet");
		break;
	default:
		break;
	}
}

Bullet::~Bullet()
{
	Projectile::~Projectile();
}

void Bullet::Update()
{
	if (rotation != 0)
	{
		Move(Speed *Vector3(cosf(D3DXToRadian(rotation)), sinf(D3DXToRadian(rotation)), 0));
	}
	else if (Dir == DIRECTION::RIGHT)
		Move(Vector3(Speed, 0, 0));
	else if(Dir==DIRECTION::LEFT)
		Move(Vector3(-Speed, 0, 0));
	Projectile::Update();
}

void Bullet::Render()
{
	Projectile::Render();
}

void Bullet::Move(Vector3 position)
{
	AnimationRect::Move(position*Time::Delta());
}
