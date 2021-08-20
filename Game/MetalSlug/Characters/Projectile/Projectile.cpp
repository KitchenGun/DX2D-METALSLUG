#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir)
	:AnimationRect(position, size, rotation),
	Dir(dir)
{
	StartPos = position;
}

Projectile::~Projectile()
{
	AnimationRect::~AnimationRect();
}

void Projectile::Update()
{
	AnimationRect::Update();
}

void Projectile::Render()
{
	AnimationRect::Render();
}
