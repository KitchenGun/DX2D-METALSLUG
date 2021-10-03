#include "stdafx.h"
#include "Bullet.h"
#include "Utilities/Animator.h"
Bullet::Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, bool bisPPM)
	:Projectile(position, size, rotation,dir,BT, bisPPM)
{
	texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
	animClips.push_back(new AnimationClip(L"NormalBullet", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/SFX/Weapon/EnemyBossLaser.png");
	animClips.push_back(new AnimationClip(L"EnemyBossLaser", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"TestBox", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->bLoop = false;
	
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
		Speed = 150000;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
		animator->SetCurrentAnimClip(L"NormalBullet");
	break;
	case PROJECTILETYPE::HEAVY:
		Damage = 1;
		Speed = 140000;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
		animator->SetCurrentAnimClip(L"NormalBullet");
		break;
	case PROJECTILETYPE::BOSSLASER:
		Damage = 1;
		Speed = 0;
		animator->playRate = 1.0f / 3;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/EnemyBossLaser.png");
		animator->SetCurrentAnimClip(L"EnemyBossLaser");
		TransformVertices();
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
	if (pt != PROJECTILETYPE::BOSSLASER)
	{
		if (rotation != 0 || rotation != 180)
		{
			Move(Speed * Vector3(cosf(D3DXToRadian(rotation)) * Time::Delta(), sinf(D3DXToRadian(rotation)) * Time::Delta(), 0));
		}
		else if (Dir == DIRECTION::RIGHT)
			Move(Vector3(Speed * Time::Delta(), 0, 0));
		else if (Dir == DIRECTION::LEFT)
			Move(Vector3(-Speed * Time::Delta(), 0, 0));
	}

	
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
