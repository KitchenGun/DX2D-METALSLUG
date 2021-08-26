#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (Enemy* tempEnemy : enemyList)
	{
		SAFE_DELETE(tempEnemy);
	}
}

void EnemyManager::Update()
{
	for (Enemy* tempEnemy : enemyList)
	{
		if (tempEnemy != nullptr)
		{
			tempEnemy->SetisGround(Math::GroundIntersect(tempEnemy, GroundList));
			ProjectileCollisionCheck(tempEnemy);
			tempEnemy->Update();
		}
	}
}

void EnemyManager::Render()
{
	for (Enemy* tempEnemy : enemyList)
	{
		if (tempEnemy != nullptr)
		{
			tempEnemy->Render();
		}
	}
}

void EnemyManager::ProjectileCollisionCheck(Enemy* tempEnemy)
{
	//이부분에서 터짐 문제 해결 필요함 아마 총알이 없는데 충돌을 처리하기위해서 총알을 찾는 듯함
	if (PPM->GetList().size() > 0)
	{
		for (Projectile* tempProj : PPM->GetList())
		{
			if (Math::Intersect(tempEnemy, tempProj))
			{
				tempEnemy->Hit(tempProj->GetDamage());
			}
		}
	}
}

void EnemyManager::AddEnemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
{
	Enemy* tempEnemy = nullptr;
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		tempEnemy = new EnemySoldier(position, size, rotation, enemyType);
		break;
	default:
		break;
	}
	enemyList.push_back(tempEnemy);
}

void EnemyManager::RemoveEnemy(Enemy* tempEnemy)
{
	for (iter = enemyList.begin(); iter != enemyList.end(); ++iter)
	{
		if (*iter == tempEnemy)
		{
			iter = enemyList.erase(iter);
			break;
		}
	}
}

