#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE PT)
	:AnimationRect(position, size, rotation),
	Dir(dir),
	pt(PT)
{
	StartPos = position;
}

Projectile::~Projectile()
{
	AnimationRect::~AnimationRect();
}

void Projectile::Update()
{
	ProjectileCollisionCheck();
	AnimationRect::Update();
}

void Projectile::Render()
{
	AnimationRect::Render();
}

void Projectile::ProjectileCollisionCheck()
{
	for (Enemy* tempE : EM->GetEnemyList())
	{
		if (Math::Distance(tempE->GetTransformedCoord().Point, this->GetPointPos()) < 100)
		{
			//aabb
			if (Math::Intersect(tempE, this))
			{
				if (this->GetPT() == PROJECTILETYPE::KNIFE)
				{
					tempE->Hit(this->GetDamage(), this);
					break;
				}
				else
				{
					tempE->Hit(this->GetDamage());
					isNeedDestroy = true;
					break;
				}
			}
			//obb
			else
			{
				if (Math::OBBIntersect(tempE, this))
				{
					if (this->GetPT() == PROJECTILETYPE::KNIFE)
					{
						tempE->Hit(this->GetDamage(), this);
					}
					else
					{
						tempE->Hit(this->GetDamage());
						isNeedDestroy = true;
					}
				}
			}
		}
	}
}
