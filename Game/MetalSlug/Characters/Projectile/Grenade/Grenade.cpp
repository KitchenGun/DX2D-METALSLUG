#include "stdafx.h"
#include "Grenade.h"
#include "Utilities/Animator.h"

Grenade::Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, EnemyManager* EnemyM)
	:Projectile(position,size,rotation,dir,BT)
{
	SetEM(EnemyM);
	texture = new Texture2D(L"./_Textures/SFX/Weapon/RGrenade.png");
	animClips.push_back(new AnimationClip(L"RGrenade", texture, 16, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/SFX/Weapon/LGrenade.png");
	animClips.push_back(new AnimationClip(L"LGrenade", texture, 16, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	StartPos = position;
	if (Dir == DIRECTION::RIGHT)
	{
		Angle = (float)D3DXToRadian(45);
		texture = new Texture2D(L"./_Textures/SFX/Weapon/RGrenade.png");
		animator->SetCurrentAnimClip(L"RGrenade",false);
	}
	else if (Dir == DIRECTION::LEFT)
	{
		Angle = (float)D3DXToRadian(135);
		texture = new Texture2D(L"./_Textures/SFX/Weapon/LGrenade.png");
		animator->SetCurrentAnimClip(L"LGrenade", false);
	}
}

Grenade::~Grenade()
{
	Projectile::~Projectile();
}

void Grenade::Update()
{
	ThrowingTime += Time::Delta();
	Projectile::Update();
	Move();
	if (GroundList.size() > 0)
	{
		if (Math::GroundIntersect(this, GroundList))
		{
			StartPos = position;
			Speed -= 60;
			ThrowingTime = 0;
		}
	}
}

void Grenade::Render()
{
	Projectile::Render();
}

void Grenade::Move()
{
	this->position = StartPos+
		Vector3((Speed * cosf(Angle) * ThrowingTime), ((Speed * sinf(Angle) * ThrowingTime) - (0.5f * Gravity * powf(ThrowingTime,2))), 0);
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}
