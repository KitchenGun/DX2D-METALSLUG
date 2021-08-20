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
	cout << projectileList.size() << endl;
	for (Projectile* tempProjectile : projectileList)
	{
		if (tempProjectile != nullptr)
		{
			tempProjectile->Update();

			if (Math::Distance(tempProjectile->GetStartPos(), tempProjectile->GetPosition()) > 2000.0f)//일정 거리 이상일 경우 삭제
			{
				RemoveProjectile(tempProjectile);
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


void ProjectileManager::AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, BULLETTYPE BT)
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
