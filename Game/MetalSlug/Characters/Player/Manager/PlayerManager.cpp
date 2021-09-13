#include "stdafx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager(ProjectileManager* ppm, EnemyManager* em)
:PPM(ppm),EM(em)
{
}

PlayerManager::~PlayerManager()
{
	SAFE_DELETE(PPM);

	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}

	for (Player* tempPlayer : playerList)
	{
		SAFE_DELETE(tempPlayer);
	}

}

void PlayerManager::Update()
{
	for (Player* tempPlayer : playerList)
	{
		if (tempPlayer != nullptr)
		{
			tempPlayer->SetisGround(Math::GroundIntersect(tempPlayer, GroundList));
			tempPlayer->Update();
		}
	}
}

void PlayerManager::Render()
{
	for (Player* tempPlayer : playerList)
	{
		if (tempPlayer != nullptr)
		{
			tempPlayer->Render();
		}
	}
}

void PlayerManager::AddPlayer(Vector3 position)
{
	Player* tempPlayer = nullptr;
	tempPlayer = new Player(position, Vector3(30 * 3, 40 * 3, 1), 0);
	tempPlayer->SetPM(PPM);
	tempPlayer->SetEM(EM);
	playerList.push_back(tempPlayer);
}

void PlayerManager::RemovePlayer(Player* tempPlayer)
{
	for (iter = playerList.begin(); iter != playerList.end(); ++iter)
	{
		if (*iter == tempPlayer)
		{
			iter = playerList.erase(iter);
			break;
		}
	}
}
