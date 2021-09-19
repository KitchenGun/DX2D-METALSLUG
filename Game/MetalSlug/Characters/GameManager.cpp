#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(PlayerManager* pm, EnemyManager* em)
	:PM(pm),
	EM(em)
{
	Camera::Get()->Move(PM->GetPlayer()->GetPosition() - Vector3(200, 400, 0));
}

GameManager::~GameManager()
{
	SAFE_DELETE(EM);
	SAFE_DELETE(PM);
}

void GameManager::AddEnemy(ENEMYTYPE ET, Vector3 Pos)
{
	EM->AddEnemy(Pos, ET);
}

void GameManager::AddPlayer(Vector3 Pos)
{
	PM->AddPlayer(Pos);
}

void GameManager::EnemySpawn()
{
	static float DeltaTime = 0;
	if (DeltaTime > SpawnRate)
	{
		//AddEnemy(ENEMYTYPE::Grenadier,PM->GetPlayer()->GetPosition() + Vector3(1300, 300, 0));
		DeltaTime = 0;
	}
	else
		DeltaTime += Time::Delta();
}

void GameManager::Update()
{
	if (PM->GetPlayerList().size() <= 0)
	{
		AddPlayer(Vector3(4000, 400, 0));
	}
	else
	{
		Camera::Get()->Move(PM->GetPlayer()->GetPosition() - Vector3(200, 150, 0));
		PlayerTracking();
		EnemySpawn();
	}
}

void GameManager::PlayerTracking()
{
	if (PM->GetPlayer()->GetPosition().x > 5994)
	{
		phase = 1;
	}
	else if(PM->GetPlayer()->GetPosition().x > 10395)
	{
		phase = 2;
	}
	else if (PM->GetPlayer()->GetPosition().x > 11479)
	{
		phase = 3;
	}
	else if (PM->GetPlayer()->GetPosition().x > 15324)
	{
		phase = 3;
	}
}
