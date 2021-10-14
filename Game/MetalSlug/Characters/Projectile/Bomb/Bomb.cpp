#include "stdafx.h"
#include "Bomb.h"
#include "Utilities/Animator.h"

Bomb::Bomb(Vector3 position, Vector3 size, float rotation, SFXManager* sfxm, bool bisPPM)
	:Projectile(position,size,rotation,DIRECTION::NONE,PROJECTILETYPE::HELIBOMB, sfxm, bisPPM)
{
	texture = new Texture2D(L"./_Textures/SFX/Weapon/HelicopterBomb.png");
	animClips.push_back(new AnimationClip(L"HelicopterBomb", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	Damage = 1;
	animator->bLoop = true;
}

Bomb::~Bomb()
{
	Projectile::~Projectile();
}

void Bomb::Update()
{
	Projectile::Update();
	Move(Vector3(0, -250, 0));
}

void Bomb::Render()
{
	Projectile::Render();
}

void Bomb::Move(Vector3 position)
{
	this->position += position * Time::Delta();
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void Bomb::Hit()
{
	--PHP;
	if (PHP == 0)
	{
		SFXM->AddSFX(position, DIRECTION::NONE, PROJECTILETYPE::EnemyGrenade);
		isNeedDestroy = true;
	}
}
