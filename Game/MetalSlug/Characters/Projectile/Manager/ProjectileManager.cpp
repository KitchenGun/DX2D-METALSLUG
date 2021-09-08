#include"stdafx.h"
#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
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
			if (Math::Distance(tempProjectile->GetStartPos(), tempProjectile->GetPosition()) > 2000.0f)//일정 거리 이상일 경우 삭제
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
			tempProjectile->Render();
		}
	}
}


void ProjectileManager::AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	Bullet* tempBullet = new Bullet(position, size, rotation, dir, BT);
	
	projectileList.push_back(tempBullet);
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
