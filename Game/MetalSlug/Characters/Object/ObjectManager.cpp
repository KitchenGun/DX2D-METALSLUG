#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(PlayerManager* pm, EnemyManager* em, ProjectileManager* ppm)
	:PM(pm),
	EM(em),
	PPM(ppm)
{

}

ObjectManager::~ObjectManager()
{
	SAFE_DELETE(Stage1Texture);
	SAFE_DELETE(PPM);
	SAFE_DELETE(EM);
	SAFE_DELETE(PM);
	for (Object* tempo : objectList)
	{
		SAFE_DELETE(tempo);
	}
}

void ObjectManager::Update()
{
	for (Object* tempo : objectList)
	{
		if (tempo != nullptr)
		{
			tempo->Update();
			if (tempo->GetIsNeedDestroy())
			{
				RemoveObject(tempo);
				break;
			}
		}
	}
	PlayerBlock();
	EnemyBlock();
}

void ObjectManager::Render()
{
	for (Object* tempo : objectList)
	{
		if (tempo != nullptr)
		{
			tempo->Render();
		}
	}
}

void ObjectManager::PlayerBlock()
{
	if (PM->GetPlayer() != nullptr)
	{
		bool isCollision = false;
		for (Object* tempo : objectList)
		{
			if (Math::Intersect(PM->GetPlayer(), tempo))
			{
				isCollision = true;
				tempo->PlayerBlock();
			}
		}
		if (isCollision == false)
		{
			PM->GetPlayer()->SetBlockDir(DIRECTION::NONE);
			PM->GetPlayer()->SetisObject(false);
		}
	}
}

void ObjectManager::EnemyBlock()
{
	for (Enemy* tempE : EM->GetEnemyList())
	{
		if (tempE != nullptr)
		{
			bool isCollision = false;
			for (Object* tempo : objectList)
			{
				if (tempo != nullptr)
				{
					if (Math::Intersect(tempE, tempo))
					{
						isCollision = true;
						tempo->EnemyBlock();
					}
				}
			}
			if (isCollision == false)
			{
				tempE->SetBlockDir(DIRECTION::NONE);
				//tempE->SetisObject(false);
			}
		}
	}
}

void ObjectManager::AddObject(Vector3 position, Vector3 size, ObjectType objectType, bool isRender)
{
	Object* tempO = nullptr;
	switch (objectType)
	{
	case ObjectType::ROCK:
		tempO = new Rock1(position, size, 0, isRender);
		tempO->SetTarget(EM);
		tempO->SetTarget(PM);
		tempO->SetPPM(PPM);
		break;
	}
	objectList.push_back(tempO);
}

void ObjectManager::AddObject(Vector3 position, ObjectType objectType, bool isRender)
{
	Object* tempO = nullptr;
	switch (objectType)
	{
	case ObjectType::ROCK:
		tempO = new Rock1(position, Vector3(64 * 4, 45 * 4, 1), 0, isRender);
		tempO->SetTarget(EM);
		tempO->SetTarget(PM);
		tempO->SetPPM(PPM);
		break; 
	}
	objectList.push_back(tempO);
}

void ObjectManager::AddBuilding(Vector3 position, Vector3 size, int buildIndex, bool isRender)
{
	Object* tempO = nullptr;
	tempO = new Building(position, size, 0, buildIndex,isRender, Stage1Texture);
	tempO->SetTarget(EM);
	tempO->SetTarget(PM);
	tempO->SetPPM(PPM);
	objectList.push_back(tempO);
}

void ObjectManager::RemoveObject(Object* tempO)
{
	for (iter = objectList.begin(); iter != objectList.end(); ++iter)
	{
		if (*iter == tempO)
		{
			iter = objectList.erase(iter);
			break;
		}
	}
}
