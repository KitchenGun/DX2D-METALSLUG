#include "stdafx.h"
#include "Scene_Intro.h"

Intro::Intro()
{
}

Intro::~Intro()
{
	SAFE_DELETE(background);
	SAFE_DELETE(mapTex);
}

void Intro::Init()
{
	background = new TextureRect(Vector3(0, 0, 0), Vector3(1280, 720, 1), 0);
	//mapTex = new Texture2D(L"./_Textures/IMG0.png");
	//background->SetSRV(mapTex->GetSRV());
}


void Intro::Update()
{
	background->Update();
}

void Intro::PreRender()
{

}

void Intro::Render()
{
	background->Render();
}

void Intro::PostRender()
{
}
