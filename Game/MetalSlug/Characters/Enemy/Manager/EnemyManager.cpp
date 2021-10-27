#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(ProjectileManager* epm)
	:EPM(epm)
{
}

EnemyManager::~EnemyManager()
{
	SAFE_DELETE(boss);
	SAFE_DELETE(SFXM);
	SAFE_DELETE(GM);
	SAFE_DELETE(PM);
	SAFE_DELETE(EPM);

	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}
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
			if (tempEnemy->GetET() == ENEMYTYPE::Boss || tempEnemy->GetET() == ENEMYTYPE::Helicopter)
			{

			}
			else
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

	if (boss != nullptr)
	{
		static bool die = false;
		if (boss->GetHP() < 0)
		{
			if (die == false)
			{
				SFXM->AddSFX(boss->GetPosition() + Vector3(-100, 300, 0), DIRECTION::NONE, PROJECTILETYPE::HELIBOMB,true);
				SFXM->AddSFX(boss->GetPosition() + Vector3(-100, 0, 0), DIRECTION::NONE, PROJECTILETYPE::HELIBOMB, true);
				die = true;
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
	case ENEMYTYPE::Helicopter:
		tempEnemy = new Helicopter(position, Vector3(89 * 3, 68 * 3, 1), 500);
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
	boss = tempEnemy;
}

void EnemyManager::RemoveEnemy(Enemy* tempEnemy)
{
	for (iter = enemyList.begin(); iter != enemyList.end(); ++iter)
	{
		if (*iter == tempEnemy)
		{
			if (tempEnemy->GetET() == ENEMYTYPE::Helicopter)
			{
				GM->HeliDestroy();
				SFXM->AddSFX(tempEnemy->GetPosition(), DIRECTION::NONE, PROJECTILETYPE::HELIBOMB);
				GM->ScoreChange(1000);
			}
			else
			{
				GM->ScoreChange(100);
			}
			iter = enemyList.erase(iter);
			break;
		}
	}
}

