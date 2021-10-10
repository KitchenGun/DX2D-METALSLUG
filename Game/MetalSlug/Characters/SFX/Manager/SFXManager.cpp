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

void SFXManager::AddSFX(Vector3 position, DIRECTION dir, PROJECTILETYPE BT)
{
	BulletSFX* tempB = nullptr;
	switch (BT)
	{
	case PROJECTILETYPE::PISTOL:
		tempB = new BulletSFX(position,SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::HEAVY:
		tempB = new BulletSFX(position, SFXTYPE::BULLET, dir);
		SFXList.push_back(tempB);
		break;
	case PROJECTILETYPE::EnemyGrenade:
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
			cout <<"삭제" <<endl;
			break;
		}
	}
}
