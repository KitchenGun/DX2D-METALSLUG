#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(PlayerManager* pm, EnemyManager* em)
	:PM(pm),
	EM(em)
{
	Camera::Get()->SetCamPos(Vector3(80, 50, 0));//높이50
	EM->AddBoss(Vector3(15900, 810, 0));
	AddEnemy(ENEMYTYPE::Helicopter, PM->GetPlayer()->GetPosition() + Vector3(300, -00, 0));
}

GameManager::~GameManager()
{
	SAFE_DELETE(Target);
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
	cout << phase << endl;
	switch (phase)
	{
	case 0:
		Camera::Get()->SetCamPosLimit(6200, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x+(WinMaxWidth/4))
		{
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 1:
		Camera::Get()->SetCamPosLimit(10660, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			//AddEnemy(ENEMYTYPE::Helicopter, PM->GetPlayer()->GetPosition() + Vector3(300, -00, 0));
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 2:
		Camera::Get()->SetCamPosLimit(10660, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 3:
		Camera::Get()->SetCamPosLimit(11600, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 4:
		Camera::Get()->SetCamPosLimit(12800, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 5:
		Camera::Get()->SetCamPosLimit(14800, 480, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
			Camera::Get()->Move(Vector3(350, 90, 0));
		}
		break;
	case 6:
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
	switch (phase)
	{
	case 0:
		if (DeltaTime > SpawnRate)
		{
			AddEnemy(ENEMYTYPE::Grenadier,PM->GetPlayer()->GetPosition() + Vector3(1300, 300, 0));
			DeltaTime = 0;
		}
		break;
	default:
		break;
	}
	DeltaTime += Time::Delta();
}

void GameManager::Update()
{
	if (PM->GetPlayerList().size() <= 0)
	{
		AddPlayer(Camera::Get()->GetCamPos()+Vector3(200,600,0));
	}
	else
	{
		//cout <<"Cam :"<< String::ToString(Camera::Get()->GetCamPos()) << endl;
		cout <<"Player :"<< String::ToString(PM->GetPlayer()->GetPointPos()) << endl;

		PlayerTracking();
		CameraMove();
		EnemySpawn();
		Win();
	}
}

void GameManager::PlayerTracking()
{
	if (PM->GetPlayer()->GetPosition().x > 14700)
	{
		//보스전
		phase = 6;
	}
	else if (PM->GetPlayer()->GetPosition().x > 13400)
	{//폭포수 조우
		phase = 5;
	}
	else if (PM->GetPlayer()->GetPosition().x > 12300)
	{//배 장애물 조우
		phase = 4;
	}
	else if (Target->GetHP() <= 0)
	{
		//건물 파괴이후
		phase = 3;
	}
	else if(Target->GetHP() < 30)
	{//건물 단계가 터지기 일보 직전단계일때 헬기 스폰
		phase = 2;
	}
	else if (PM->GetPlayer()->GetPosition().x > 7000)
	{//헬기 등장이후
		phase =	1;
	}
	else
	{//시작하고 헬기 등장까지
		phase = 0;
	}
}

void GameManager::Win()
{
	if (phase > 3)
	{
		for (Enemy* temp : EM->GetEnemyList())
		{
			if (temp->GetET() == ENEMYTYPE::Boss)
			{
				if (temp->GetHP() <= 0)
				{
					PM->GetPlayer()->Win();
					isWin = true;
				}
			}
		}
	}
}

void GameManager::ScoreChange(int val)
{
	Score += val;
}
