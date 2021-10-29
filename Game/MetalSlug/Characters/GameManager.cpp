#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager(PlayerManager* pm, EnemyManager* em)
	:PM(pm),
	EM(em)
{
	Camera::Get()->SetCamPos(Vector3(80, 50, 0));//높이50
	//사운드
	BGM = new SoundSystem();
	BGM->CreateBGSound("_Sounds/GM/Stage.mp3");
	Announcer = new SoundSystem();
	Announcer->CreateEffSound("_Sounds/GM/mission-start.mp3");
	BGM->Play();
	Announcer->Play();
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
	switch (phase)
	{
	case 0:
		Camera::Get()->SetCamPosLimit(6000, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x+(WinMaxWidth/4))
		{
			Camera::Get()->Move(Vector3(350, 0, 0));
		}
		break;
	case 1:
		Camera::Get()->SetCamPosLimit(10660, 80, 80);
		if (PM->GetPlayer()->GetPointPos().x >= Camera::Get()->GetCamPos().x + (WinMaxWidth / 4))
		{
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
	static int CamXPos = 0;
	
	switch (phase)
	{
	case 0:
		if (DeltaTime > SpawnRate)
		{
			if (CamXPos != (int)Camera::Get()->GetCamPos().x)
			{
				AddEnemy(ENEMYTYPE::Grenadier, PM->GetPlayer()->GetPosition() + Vector3(1300, 300, 0));
			}
			DeltaTime = 0;
		}
		CamXPos = Camera::Get()->GetCamPos().x;
		DeltaTime += Time::Delta();
		break;
	case 1:
		if (DeltaTime > SpawnRate)
		{
			if (CamXPos != (int)Camera::Get()->GetCamPos().x)
			{
				AddEnemy(ENEMYTYPE::Grenadier, PM->GetPlayer()->GetPosition() + Vector3(1300, 300, 0));
			}
			DeltaTime = 0;
		}
		CamXPos = Camera::Get()->GetCamPos().x;
		DeltaTime += Time::Delta();
		break;
	case 2:
		if (DeltaTime > SpawnRate)
		{
			if (CamXPos != (int)Camera::Get()->GetCamPos().x)
			{
				AddEnemy(ENEMYTYPE::Grenadier, PM->GetPlayer()->GetPosition() + Vector3(1300, 800, 0));
			}
			DeltaTime = 0;
		}
		CamXPos = Camera::Get()->GetCamPos().x;
		DeltaTime += Time::Delta();
		break;
	case 5:
		if (DeltaTime > SpawnRate)
		{
			if (CamXPos != (int)Camera::Get()->GetCamPos().x)
			{
				AddEnemy(ENEMYTYPE::Grenadier, PM->GetPlayer()->GetPosition() + Vector3(2000, 1000, 0));
			}
			DeltaTime = 0;
		}
		CamXPos = Camera::Get()->GetCamPos().x;
		DeltaTime += Time::Delta();
		break;
	default:
		
		break;
	}
}

void GameManager::Update()
{
	if (PM->GetPlayerList().size() <= 0)
	{
		AddPlayer(Camera::Get()->GetCamPos()+Vector3(200,600,0));
	}
	else
	{
		PlayerTracking();
		CameraMove();
		EnemySpawn();
		Win();
	}
	BGM->Update();
	Announcer->Update();
}

void GameManager::PlayerTracking()
{
	if (PM->GetPlayer()->GetPosition().x > 14900)
	{
		static bool Trigger = false;
		if (Trigger == false)
		{
			BGM->Stop();
			BGM->ChangeSoundFunc(L"_Sounds/GM/Boss.mp3");
			BGM->Play();
			Trigger = true;
		}
	}
	else if (PM->GetPlayer()->GetPosition().x > 14600)
	{
		//보스전
		phase = 6;
	}
	else if (PM->GetPlayer()->GetPosition().x > 13400)
	{//폭포수 조우
		static bool Trigger = false;
		if (Trigger == false)
		{
			EM->AddBoss(Vector3(15900, 810, 0));
			Trigger = true;
		}
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
	else if(Target->GetHP() < 40)
	{//건물 단계가 터지기 일보 직전단계일때 헬기 스폰
		static bool Trigger = false;
		if (Trigger == false)
		{
			AddEnemy(ENEMYTYPE::Helicopter, PM->GetPlayer()->GetPosition() + Vector3(-200, 700, 0));
			Trigger = true;
		}
	}
	else if (PM->GetPlayer()->GetPosition().x > 5600)
	{//헬기 등장이후
		static bool Trigger = false;
		if (Trigger == false)
		{
			AddEnemy(ENEMYTYPE::Helicopter, PM->GetPlayer()->GetPosition() + Vector3(-200, 700, 0));
			Trigger = true;
		}
	}
	else
	{//시작하고 헬기 등장까지
		phase = 0;
	}
}

void GameManager::HeliDestroy()
{
	if (phase == 0)
	{
		phase++;
	}
	else if (phase == 1)
	{
		phase++;
	}
}

void GameManager::Win()
{

	if (phase > 5)
	{
		for (Enemy* temp : EM->GetEnemyList())
		{
			if (temp->GetET() == ENEMYTYPE::Boss)
			{
				if (temp->GetHP() <= 0)
				{
					PM->GetPlayer()->Win();
					isWin = true; 
					static bool Trigger = false;
					if (Trigger == false)
					{
						BGM->Stop();
						Announcer->Stop();
						BGM->ChangeSoundFunc(L"_Sounds/GM/StageClear.mp3");
						Announcer->ChangeSoundFunc(L"_Sounds/GM/mission-complete.wav");
						BGM->Play();
						Announcer->Play();
						Trigger = true;
					}
				}
			}
		}
	}
}

void GameManager::ScoreChange(int val)
{
	Score += val;
}
