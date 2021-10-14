#include "stdafx.h"
#include "SFXManager.h"

SFXManager::SFXManager()
{
}

SFXManager::~SFXManager()
{
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
				break;//������ ������Ʈ ����Ʈ�� ����Ǽ� break�ɰ� �ٽ� ��������
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

void SFXManager::AddSFX(Vector3 position, DIRECTION dir, PROJECTILETYPE BT)
{
	BulletSFX* tempB = nullptr;
	switch (BT)
	{
	case PROJECTILETYPE::NONE:
		tempB = new BulletSFX(position, SFXTYPE::BLOOD, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::PISTOL:
		tempB = new BulletSFX(position,SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::HEAVY:
		tempB = new BulletSFX(position, SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::EnemyGrenade:
		tempB = new BulletSFX(position, SFXTYPE::ENEMYGRENADE, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::HELIBOMB:
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
