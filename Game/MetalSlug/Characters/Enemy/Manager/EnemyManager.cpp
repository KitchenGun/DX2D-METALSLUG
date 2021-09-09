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

