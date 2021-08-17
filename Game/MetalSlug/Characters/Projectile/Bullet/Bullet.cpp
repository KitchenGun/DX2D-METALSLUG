#include "stdafx.h"
#include "Bullet.h"
#include "Utilities/Animator.h"

Bullet::Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, BULLETTYPE BT)
	:Projectile(position, size, rotation,dir),
	bt(BT)
{
	switch (bt)
	{
	case BULLETTYPE::NONE:
	break;
	case BULLETTYPE::PISTOL:
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
		fSpeed = 500.0f;
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
	Move(Vector3(fSpeed, 0, 0));
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
