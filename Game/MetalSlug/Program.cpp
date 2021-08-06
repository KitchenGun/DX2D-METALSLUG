#include "stdafx.h"
#include "Program.h"
#include "Scenes/SceneList.h"

Program::Program()
{
	Camera::Create();
	
}

Program::~Program()
{
	Camera::Delete();
}

void Program::Init()
{
	sceneList.push_back(new Intro());
	sceneList.push_back(new Stage());
	currentScene = sceneList[0];
	currentScene->Init();
}


void Program::Update()
{

	Camera::Get()->Update();
	
	if (Keyboard::Get()->Down(VK_F1))
	{
		currentScene = sceneList[0];
		currentScene->Init();
	}
	
	currentScene->Update();
}




void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	Camera::Get()->Render();
	currentScene->Render();
}

void Program::PostRender()
{
	Gui::Get()->PrintFrame();
	currentScene->PostRender();
}
