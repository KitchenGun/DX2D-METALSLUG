#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager(PlayerManager* pm,GameManager* gm)
{
	ammoUI = new AmmoUI(pm);
	scoreUI = new ScoreUI(gm);
}

UIManager::~UIManager()
{
	SAFE_DELETE(gm);
	SAFE_DELETE(pm);
	SAFE_DELETE(scoreUI);
	SAFE_DELETE(ammoUI);
}

void UIManager::Update()
{
	ammoUI->Update();
	scoreUI->Update();
}

void UIManager::Render()
{
	ammoUI->Render();
	scoreUI->Render();
}
