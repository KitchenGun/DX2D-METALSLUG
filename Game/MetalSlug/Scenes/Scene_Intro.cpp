#include "stdafx.h"
#include "Scene_Intro.h"

Intro::Intro()
{
	BGM = new SoundSystem();
	BGM->CreateBGSound("_Sounds/GM/Intro.mp3");
	BGM->Play();
	OK = new SoundSystem();
	OK->CreateBGSound("_Sounds/Item/OK.wav");
}

Intro::~Intro()
{
}

void Intro::Init()
{
	Main = new TextureRect(Camera::Get()->GetCamPos() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(1280, 720, 0), 0);
	Main->SetSRV(L"_Textures/UI/Main.png");
}


void Intro::Update()
{
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		OK->Play();
		IsStart = true;
	}
	if(IsStart)
	{
		static float DeltaTime = 0.0f;
		if (DeltaTime > 1.0f)
		{
			BGM->Stop();
			OK->Stop();
			index = 1;
			IsStart = false;
		}
		else
		{
			DeltaTime += Time::Delta();
		}
	}


}

void Intro::PreRender()
{

}

void Intro::Render()
{
	Main->Render();
}

void Intro::PostRender()
{
}
