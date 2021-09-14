#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE PT, bool isPPM)
	:AnimationRect(position, size, rotation),
	Dir(dir),
	pt(PT),
	IsPPM(isPPM)
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
	if (IsPPM)
	{
		for (Enemy* tempE : EM->GetEnemyList())
		{
			if (Math::Distance(tempE->GetTransformedCoord().Point, this->GetPosition()) < 50 * 4)
			{
				//obb
				if (Math::OBBIntersect(tempE, this))
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
	else
	{
		for (Player* tempP : PM->GetPlayerList())
		{
			if (Math::Distance(tempP->GetTransformedCoord().Point, this->GetPosition()) < 50 * 4)
			{
				//obb
				if (Math::OBBIntersect(tempP, this))
				{

					if (this->GetPT() == PROJECTILETYPE::KNIFE || this->GetPT() == PROJECTILETYPE::EnemyGrenade)
					{
						if (this->GetPT() == PROJECTILETYPE::EnemyGrenade)
						{
							if (!dynamic_cast<Grenade*>(this)->GetIsHit())
							{
								this->HitPos = this->position;
							}
							dynamic_cast<Grenade*>(this)->SetIsHit(true);
							//tempP->Hit(this->GetDamage(), this);
						}
						else
						{
							//tempP->Hit(this->GetDamage(), this);
						}
					}
					else
					{
						//tempP->Hit(this->GetDamage());
						isNeedDestroy = true;
					}
				}
				//aabb
				else if (Math::Intersect(tempP, this))
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
							//tempP->Hit(this->GetDamage(), this);
						}
						else
						{
							//tempP->Hit(this->GetDamage(), this);
						}
					}
					else
					{
						//tempP->Hit(this->GetDamage());
						isNeedDestroy = true;
					}
				}
			}

		}
	}
}
