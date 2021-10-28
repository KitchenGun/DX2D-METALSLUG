#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager(PlayerManager* pm,GameManager* gm)
	:gm(gm),
	pm(pm)
{
	ammoUI = new AmmoUI(pm);
	scoreUI = new ScoreUI(gm);
	timer = new Timer(pm);
	start = new Start();
}

UIManager::~UIManager()
{
	SAFE_DELETE(gm);
	SAFE_DELETE(start);
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
	start->Update();
}

void UIManager::Render()
{
	ammoUI->Render();
	scoreUI->Render();
	timer->Render();
	start->Render();
}
