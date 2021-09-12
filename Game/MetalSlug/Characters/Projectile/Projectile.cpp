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
	SAFE_DELETE(EM);
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
		if (Math::Distance(tempE->GetTransformedCoord().Point, this->GetPosition()) < 50*4)
		{
			//obb
			if (Math::OBBIntersect(tempE, this))
			{

				if (this->GetPT() == PROJECTILETYPE::KNIFE||this->GetPT()==PROJECTILETYPE::Grenade)
				{
					if (this->GetPT() == PROJECTILETYPE::Grenade)
					{
						if (!dynamic_cast<Grenade*>(this)->GetIsHit())
						{
							this->HitPos = this->position;
						}
						dynamic_cast<Grenade*>(this)->SetIsHit(true);
						tempE->Hit(this->GetDamage(), this);
					}
					else
					{
						tempE->Hit(this->GetDamage(), this);
					}
				}
				else
				{
					tempE->Hit(this->GetDamage());
					isNeedDestroy = true;
				}
			}
			//aabb
			else if (Math::Intersect(tempE, this))
			{
				if (this->GetPT() == PROJECTILETYPE::KNIFE || this->GetPT() == PROJECTILETYPE::Grenade)
				{
					if (this->GetPT() == PROJECTILETYPE::Grenade)
					{
						if (!dynamic_cast<Grenade*>(this)->GetIsHit())
						{
							this->HitPos = this->position;
						}
						dynamic_cast<Grenade*>(this)->SetIsHit(true);
						tempE->Hit(this->GetDamage(), this);
					}
					else
					{
						tempE->Hit(this->GetDamage(), this);
					}
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
