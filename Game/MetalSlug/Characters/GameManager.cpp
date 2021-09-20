#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(PlayerManager* pm, EnemyManager* em)
	:PM(pm),
	EM(em)
{
	Camera::Get()->SetCamPos(Vector3(100, 60, 0));
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

void GameManager::CameraMove()
{
	switch (phase)
	{
	case 0:
		Camera::Get()->SetCamPosLimit(6200, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x+(WinMaxWidth/4))
		{
			Camera::Get()->Move(Vector3(340, 0, 0));
		}
		break;
	case 1:
		Camera::Get()->SetCamPosLimit(10800, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(340, 0, 0));
		}
		break;
	case 2:
		Camera::Get()->SetCamPosLimit(128000, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(340, 0, 0));
		}
		break;
	case 3:
		Camera::Get()->SetCamPosLimit(128000, 480, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(340, 90, 0));
		}
		break;
	case 4:
		Camera::Get()->SetCamPosLimit(15400, 14200, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(340, 0, 0));
		}
		break;
	default:
		break;
	}
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
		cout <<"Cam :"<< String::ToString(Camera::Get()->GetCamPos()) << endl;
		cout <<"Player :"<< String::ToString(PM->GetPlayer()->GetPointPos()) << endl;

		PlayerTracking();
		CameraMove();
		EnemySpawn();
	}
}

void GameManager::PlayerTracking()
{
	if (PM->GetPlayer()->GetPosition().x > 14700)
	{
		phase = 4;
	}
	else if (PM->GetPlayer()->GetPosition().x > 13200)
	{
		phase = 3;
	}
	else if(PM->GetPlayer()->GetPosition().x > 10600)
	{
		phase = 2;
	}
	else if (PM->GetPlayer()->GetPosition().x > 6200)
	{
		phase =	1;
	}
	else
	{
		phase = 0;
	}
}
