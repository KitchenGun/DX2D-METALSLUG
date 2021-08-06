#include "stdafx.h"
#include "Scene_Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	SAFE_DELETE(background);
	SAFE_DELETE(mapTex);
}

void Stage::Init()
{
	background = new TextureRect(Vector3(0, 0, 0), Vector3(269 *5, 2327 *5, 1), 0);
	//mapTex = new Texture2D(L"./_Textures/Map.png");
	//background->SetSRV(mapTex->GetSRV());
}

void Stage::Update()
{
	Camera::Get()->Move(Vector3(0,0,0) + Vector3(0, 200, 0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{
	background->Render();
	
}

void Stage::PostRender()
{
}


