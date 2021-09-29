#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager(PlayerManager* pm)
{
	ammoUI = new AmmoUI(pm);
}

UIManager::~UIManager()
{
	SAFE_DELETE(pm);
	SAFE_DELETE(ammoUI);
}

void UIManager::Update()
{
	ammoUI->Update();
}

void UIManager::Render()
{
	ammoUI->Render();
}
