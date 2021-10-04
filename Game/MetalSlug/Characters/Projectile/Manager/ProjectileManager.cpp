#include"stdafx.h"
#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(bool isPM)
	:bIsPM(isPM)
{
}

ProjectileManager::~ProjectileManager()
{
	SAFE_DELETE(EPM);
	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}
	SAFE_DELETE(OM);
	SAFE_DELETE(PM);
	SAFE_DELETE(EM);
	for (Projectile* tempProjectile : projectileList)
	{
		SAFE_DELETE(tempProjectile);
	}
}

void ProjectileManager::Update()
{
	for (Projectile* tempProjectile : projectileList)
	{
		if (tempProjectile != nullptr)
		{
			tempProjectile->Update();
			if (Math::Distance(tempProjectile->GetStartPos(), tempProjectile->GetPosition()) > 1200.0f)//일정 거리 이상일 경우 삭제
			{
				RemoveProjectile(tempProjectile);
				break;//삭제시 프로젝트 리스트가 변경되서 break걸고 다시 돌려야함
			}
			if (tempProjectile->GetPT() != PROJECTILETYPE::Grenade)
			{
				if (Math::GroundIntersect(tempProjectile, GroundList))
				{
					RemoveProjectile(tempProjectile);
					break;//삭제시 프로젝트 리스트가 변경되서 break걸고 다시 돌려야함
				}
			}
			if (tempProjectile->GetIsNeedDestroy())
			{
				RemoveProjectile(tempProjectile);
				break;//삭제시 프로젝트 리스트가 변경되서 break걸고 다시 돌려야함
			}
		}
	}
}

void ProjectileManager::Render()
{
	for (Projectile* tempProjectile : projectileList)
	{
		if (tempProjectile != nullptr)
		{
			if (tempProjectile->GetPT() != PROJECTILETYPE::KNIFE)
			{
				tempProjectile->Render();
			}
		}
	}
}


void ProjectileManager::AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	Bullet* tempBullet=nullptr;
	if (bIsPM)
	{
		tempBullet	= new Bullet(position, size, rotation, dir, BT);
		tempBullet->SetGroundList(GroundList);
		tempBullet->SetEPM(EPM);
		tempBullet->SetEM(EM);
		tempBullet->SetOM(OM);
	}
	else
	{
		tempBullet = new Bullet(position, size, rotation, dir, BT,false);
		tempBullet->SetGroundList(GroundList);
		tempBullet->SetPM(PM);
		tempBullet->SetOM(OM);
	}
	projectileList.push_back(tempBullet);
}

void ProjectileManager::AddGrenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	Grenade* tempGrenade = nullptr;
	if (bIsPM)
	{
		tempGrenade = new Grenade(position, size, rotation, dir, BT);
		tempGrenade->SetGroundList(GroundList);
		tempGrenade->SetEPM(EPM);
		tempGrenade->SetEM(EM);
		tempGrenade->SetOM(OM);
	}
	else
	{
		tempGrenade = new Grenade(position, size, rotation, dir, BT, false);
		tempGrenade->SetGroundList(GroundList);
		tempGrenade->SetPM(PM);
	}
	projectileList.push_back(tempGrenade);
}

void ProjectileManager::AddArty(Vector3 position, Vector3 size, float rotation, PROJECTILETYPE BT)
{
	Grenade* tempGrenade = nullptr;
	tempGrenade = new Grenade(position, size, rotation, DIRECTION::NONE, BT, false);
	tempGrenade->SetPM(PM);
	projectileList.push_back(tempGrenade);
}

void ProjectileManager::AddLaser(Vector3 position, Vector3 size, PROJECTILETYPE BT)
{
	Bullet* tempBullet = nullptr;
	tempBullet = new Bullet(position, size,0,DIRECTION::NONE,PROJECTILETYPE::BOSSLASER, false);
	tempBullet->SetPM(PM);
	tempBullet->SetOM(OM);
	projectileList.push_back(tempBullet);
}

void ProjectileManager::AddHeliBomb(Vector3 position, Vector3 size)
{
	Bomb* tempBomb = nullptr;
	tempBomb = new Bomb(position, size, 0, false);
	tempBomb->SetPM(PM);
	tempBomb->SetOM(OM);
	projectileList.push_back(tempBomb);
}


void ProjectileManager::RemoveProjectile(Projectile* Target)
{
	for (iter=projectileList.begin();iter!=projectileList.end();++iter)
	{
		if (*iter == Target)
		{
			iter=projectileList.erase(iter);
			break;
		}
	}
}
