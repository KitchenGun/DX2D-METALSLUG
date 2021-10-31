#include "stdafx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager(ProjectileManager* ppm, EnemyManager* em)
:PPM(ppm),EM(em)
{
	Voice = new SoundSystem();
	Sfx = new SoundSystem();
	Sfx->CreateEffSound("_Sounds/Player/HMG_Fire.mp3");
	Sfx->CreateEffSound("_Sounds/Player/Pistol.mp3");
	Sfx->CreateEffSound("_Sounds/Player/Knife.wav");
}

PlayerManager::~PlayerManager()
{
	SAFE_DELETE(Sfx);
	SAFE_DELETE(Voice);

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
			if (!tempPlayer->GetisObject())
			{
				tempPlayer->SetisGround(Math::GroundIntersect(tempPlayer, GroundList));
			}
			tempPlayer->Update();
			DieSoundPlay();
			if (tempPlayer->GetisDestroy())
			{
				RemovePlayer(tempPlayer);
				break;
			}
			
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
	player = nullptr;
	player = new Player(position, Vector3(30 * 3, 40 * 3, 1), 0);
	player->SetPM(PPM);
	player->SetEM(EM);
	player->SetPlayerM(this);
	isDieTrigger = false;
	playerList.push_back(player);
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

void PlayerManager::DieSoundPlay()
{
	if (player!=nullptr&&player->GetDie())
	{
		Voice->CreateEffSound("_Sounds/Player/Die.wav");
		if (!isDieTrigger)
		{
			Voice->Play();
			isDieTrigger = true;
		}
	}
}

void PlayerManager::GetHeavy()
{
	Voice->CreateEffSound("_Sounds/Item/Heavy.wav");
	Voice->Play();
}

void PlayerManager::GunFireSoundPlay(bool isHeavy)
{
	Sfx->SetVolume(0.1f);
	if (isHeavy)
	{
		Sfx->CreateEffSound("_Sounds/Player/HMG_Fire.mp3");
		Sfx->Play();
	}
	else
	{
		Sfx->ChangeSoundFunc(L"_Sounds/Player/Pistol.mp3");
		Sfx->Play();
	}
}

void PlayerManager::KnifeSoundPlay()
{
	Sfx->CreateEffSound("_Sounds/Player/Knife.wav");
	Sfx->Play();
}
