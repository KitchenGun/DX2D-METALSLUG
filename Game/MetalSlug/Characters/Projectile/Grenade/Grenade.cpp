#include "stdafx.h"
#include "Grenade.h"
#include "Utilities/Animator.h"

Grenade::Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, EnemyManager* EnemyM)
	:Projectile(position,size,rotation,dir,BT)
{
	SetEM(EnemyM);
	texture = new Texture2D(L"./_Textures/SFX/Weapon/NormalBullet.png");
	animClips.push_back(new AnimationClip(L"NormalBullet", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
}

Grenade::~Grenade()
{
}

void Grenade::Update()
{
}

void Grenade::Render()
{
}

void Grenade::Move(Vector3 position)
{
}
