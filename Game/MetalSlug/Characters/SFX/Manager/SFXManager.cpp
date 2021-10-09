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

void SFXManager::AddSFX(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	SFX* temp = nullptr;
	switch (BT)
	{
	case PROJECTILETYPE::PISTOL:
		temp = new BulletSFX(position, size, rotation, dir, BT);
		break;
	case PROJECTILETYPE::HEAVY:
		break;
	case PROJECTILETYPE::EnemyGrenade:
		break;
	case PROJECTILETYPE::HELIBOMB:
		break;
	default:
		break;
	}
	SFXList.push_back(temp);
}

void SFXManager::RemoveSFX(SFX* tempSFX)
{
}
