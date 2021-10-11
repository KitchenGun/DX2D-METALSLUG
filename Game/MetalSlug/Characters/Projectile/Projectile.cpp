#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE PT, SFXManager* sfxm, bool isPPM)
	:AnimationRect(position, size, rotation),
	Dir(dir),
	pt(PT),
	SFXM(sfxm),
	IsPPM(isPPM)
{
	StartPos = position;
}

Projectile::~Projectile()
{
	for (Ground* tempGround : GroundList)
	{
		SAFE_DELETE(tempGround);
	}
	SAFE_DELETE(SFXM);
	SAFE_DELETE(EPM);
	SAFE_DELETE(OM);
	SAFE_DELETE(PM);
	SAFE_DELETE(EM);
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
	if (IsPPM)
	{
		for (Enemy* tempE : EM->GetEnemyList())
		{
			if (Math::Distance(tempE->GetTransformedCoord().Point, this->GetPosition()) < 50 * 4)
			{
				//obb
				if (Math::OBBIntersect(tempE, this))
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
						if (pt != PROJECTILETYPE::KNIFE && pt != PROJECTILETYPE::Grenade)
						{
							isNeedDestroy = true;
						}
					}
					
				}
			}

		}
		for (Object* tempO : OM->GetObjectList())
		{
			if (tempO->GetObjType()==ObjectType::BUILDING||tempO->GetObjType() == ObjectType::BOX)
			{
				//obb
				if (Math::OBBIntersect(tempO, this))
				{
					if (this->GetPT() == PROJECTILETYPE::Grenade)
					{
						if (!dynamic_cast<Grenade*>(this)->GetIsHit())
						{
							this->HitPos = this->position;
						}
						dynamic_cast<Grenade*>(this)->SetIsHit(true);
						tempO->Hit(this->GetDamage(), this);
					}
					else
					{
						tempO->Hit(this->GetDamage(), this);
						if (pt != PROJECTILETYPE::KNIFE && pt != PROJECTILETYPE::Grenade)
						{
							isNeedDestroy = true;
						}
					}
				
				}
			}

		}
		for (Projectile* tempEP : EPM->GetList())
		{
			if (tempEP->GetPT() == PROJECTILETYPE::HELIBOMB)
			{
				if (Math::OBBIntersect(this,tempEP))
				{
					dynamic_cast<Bomb*>(tempEP)->Hit();
					isNeedDestroy = true;
				}
			}
		}
	}
	else
	{
		for (Player* tempP : PM->GetPlayerList())
		{
			//obb
			if (Math::OBBIntersect(tempP, this))
			{
				if (pt == PROJECTILETYPE::KNIFE || pt == PROJECTILETYPE::EnemyGrenade|| pt == PROJECTILETYPE::BOSSARTY|| pt == PROJECTILETYPE::BOSSLASER || pt==PROJECTILETYPE::HELIBOMB)
				{
					if (pt == PROJECTILETYPE::EnemyGrenade)
					{
						if (!dynamic_cast<Grenade*>(this)->GetIsHit())
						{
							this->HitPos = this->position;
						}
						dynamic_cast<Grenade*>(this)->SetIsHit(true);
						tempP->Hit(this->GetDamage(), this);
					}
					else
					{
						tempP->Hit(this->GetDamage(), this);
					}
					if (pt == PROJECTILETYPE::HELIBOMB)
					{
						isNeedDestroy = true;
					}
				}
				else
				{
					tempP->Hit(this->GetDamage());
					isNeedDestroy = true;
				}
			}
		}
	}
}
