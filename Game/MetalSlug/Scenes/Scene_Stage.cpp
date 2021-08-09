#include "stdafx.h"
#include "Scene_Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	player = new Player(Vector3(0, 100, 0), Vector3(3, 3, 1), 0);
}

void Stage::Update()
{
	player->Update();
	Camera::Get()->Move(Vector3(0, 0, 0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{
	player->Render();
}

void Stage::PostRender()
{
}


