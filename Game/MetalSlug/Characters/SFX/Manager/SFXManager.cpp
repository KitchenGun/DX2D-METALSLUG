#include "stdafx.h"
#include "SFXManager.h"

SFXManager::SFXManager()
{
	sound = new SoundSystem();
}

SFXManager::~SFXManager()
{
	SAFE_DELETE(sound);
	for (SFX* temp : SFXList)
	{
		SAFE_DELETE(temp);
	}
}

void SFXManager::Update()
{
	for (SFX* temp : SFXList)
	{
		if (temp != nullptr)
		{
			temp->Update();
			
			if (temp->GetIsNeedDestroy())
			{
				RemoveSFX(temp);
				break;//삭제시 프로젝트 리스트가 변경되서 break걸고 다시 돌려야함
			}
		}
	}
}

void SFXManager::Render()
{
	for (SFX* temp : SFXList)
	{
		if (temp != nullptr)
		{
			temp->Render();
		}
	}
}

void SFXManager::AddSFX(Vector3 position, DIRECTION dir, PROJECTILETYPE BT, bool loop)
{
	BulletSFX* tempB = nullptr;
	switch (BT)
	{
	case PROJECTILETYPE::NONE:
		sound->CreateEffSound("_Sounds/SFX/HitMetal.wav");
		sound->Play();
		tempB = new BulletSFX(position, SFXTYPE::BLOOD, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::PISTOL:
		sound->CreateEffSound("_Sounds/SFX/HitMetal.wav");
		sound->Play();
		tempB = new BulletSFX(position,SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::HEAVY:
		sound->CreateEffSound("_Sounds/SFX/HitMetal.wav");
		sound->Play();
		tempB = new BulletSFX(position, SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::EnemyGrenade:
		sound->CreateEffSound("_Sounds/SFX/EnemyGrenade.wav");
		sound->Play();
		tempB = new BulletSFX(position, SFXTYPE::ENEMYGRENADE, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::HELIBOMB:
		if (rand() % 2 == 0)
		{
			sound->CreateEffSound("_Sounds/SFX/Explosion.wav");
		}
		else
		{
			sound->CreateEffSound("_Sounds/SFX/Explosion1.wav");
		}
		sound->Play();
		tempB = new BulletSFX(position, SFXTYPE::EXPLOSION, dir, loop);
		SFXList.push_back(tempB);
		break;
	default:
		break;
	}
}

void SFXManager::RemoveSFX(SFX* tempSFX)
{
	for (iter = SFXList.begin(); iter != SFXList.end(); ++iter)
	{
		if (*iter == tempSFX)
		{
			iter = SFXList.erase(iter);
			break;
		}
	}
}
