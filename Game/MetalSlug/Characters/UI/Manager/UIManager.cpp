#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager(PlayerManager* pm,GameManager* gm)
	:gm(gm),
	pm(pm)
{
	ammoUI = new AmmoUI(pm);
	scoreUI = new ScoreUI(gm);
	timer = new Timer(pm);
}

UIManager::~UIManager()
{
	SAFE_DELETE(gm);
	SAFE_DELETE(pm);
	SAFE_DELETE(timer);
	SAFE_DELETE(scoreUI);
	SAFE_DELETE(ammoUI);
}

void UIManager::Update()
{
	ammoUI->Update();
	scoreUI->Update();
	if (!gm->GetisWin())
	{
		timer->Update();
	}
}

void UIManager::Render()
{
	ammoUI->Render();
	scoreUI->Render();
	timer->Render();
}
