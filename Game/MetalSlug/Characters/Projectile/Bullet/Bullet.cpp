#include "stdafx.h"
#include "Bullet.h"
#include "Utilities/Animator.h"
Bullet::Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, BULLETTYPE BT)
	:Projectile(position, size, rotation,dir),
	bt(BT)
{
	texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
	animClips.push_back(new AnimationClip(L"NormalBullet", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	
	switch (bt)
	{
	case BULLETTYPE::NONE:
	break;
	case BULLETTYPE::PISTOL:
		fSpeed = 900.0f;
		animator->SetCurrentAnimClip(L"NormalBullet");
	break;
	case BULLETTYPE::HEAVY:
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
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
		Move(fSpeed*Vector3(cosf(D3DXToRadian(rotation)), sinf(D3DXToRadian(rotation)), 0));
	}
	else if (Dir == DIRECTION::RIGHT)
		Move(Vector3(fSpeed, 0, 0));
	else if(Dir==DIRECTION::LEFT)
		Move(Vector3(- fSpeed, 0, 0));
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
