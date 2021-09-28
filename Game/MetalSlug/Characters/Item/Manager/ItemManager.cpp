#include "stdafx.h"
#include "ItemManager.h"
#include "Utilities/Animator.h"

ItemManager::ItemManager(PlayerManager* pm)
	:pm(pm)
{
}

ItemManager::~ItemManager()
{
	SAFE_DELETE(pm);
	for (Item* temp : itemList)
	{
		SAFE_DELETE(temp);
	}
}

void ItemManager::Update()
{
	for (Item* temp : itemList)
	{
		if (temp != nullptr)
		{
			temp->Update();
			if (temp->GetisTake())
			{
				RemoveItem(temp);
				break;
			}
		}
	}
}

void ItemManager::Render()
{
	for (Item* temp : itemList)
	{
		if (temp != nullptr)
		{
			temp->Render();
		}
	}
}

void ItemManager::AddItem(Vector3 position,PROJECTILETYPE pt)
{
	Item* temp = nullptr;
	if (pt == PROJECTILETYPE::HEAVY)
	{
		temp = new Item(position, Vector3(22 * 3, 20 * 3, 1), pt, pm);
	}
	itemList.push_back(temp);
}

void ItemManager::RemoveItem(Item* tempItem)
{
	for (iter = itemList.begin(); iter != itemList.end(); ++iter)
	{
		if (*iter == tempItem)
		{
			iter = itemList.erase(iter);
			break;
		}
	}
}
