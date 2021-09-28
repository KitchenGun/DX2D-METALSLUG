#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(ProjectileManager* epm)
	:EPM(epm)
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
			if(tempEnemy->GetET()!=ENEMYTYPE::Boss)
			{
				tempEnemy->SetisGround(Math::GroundIntersect(tempEnemy, GroundList));
			}
			tempEnemy->Update();
			if (tempEnemy->GetisNeedDestroy())
			{
				RemoveEnemy(tempEnemy);
				break;
			}
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

void EnemyManager::AddEnemy(Vector3 position, ENEMYTYPE enemyType)
{
	Enemy* tempEnemy = nullptr;
	switch (enemyType)
	{
	case ENEMYTYPE::Grenadier:
		tempEnemy = new EnemySoldier(position, Vector3(30 * 3, 40 * 3, 1), 0, enemyType);
		break;
	default:
		break;
	}
	tempEnemy->SetPM(PM);
	tempEnemy->SetEPM(EPM);
	enemyList.push_back(tempEnemy);
}

void EnemyManager::AddBoss(Vector3 position)
{
	Enemy* tempEnemy = nullptr;
	tempEnemy = new Boss(position, Vector3(384 * 3, 288 * 3, 1), 0);
	tempEnemy->SetPM(PM);
	tempEnemy->SetEPM(EPM);
	enemyList.push_back(tempEnemy);
}

void EnemyManager::RemoveEnemy(Enemy* tempEnemy)
{
	for (iter = enemyList.begin(); iter != enemyList.end(); ++iter)
	{
		if (*iter == tempEnemy)
		{
			GM->ScoreChange(100);
			iter = enemyList.erase(iter);
			break;
		}
	}
}

