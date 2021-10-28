#include "stdafx.h"
#include "Start.h"

Start::Start()
{
	MissionStart = new TextureRect(Vector3(0, WinMaxHeight, 0), Vector3(177 * 3, 56 * 3, 1), 0);
	MissionStart->SetSRV(L"./_Textures/UI/MissionStart.png");
}

Start::~Start()
{
	SAFE_DELETE(MissionStart);
}

void Start::Update()
{
	if (bIsActive)
	{
		if (Camera::Get()->GetCamPos().x + WinMaxWidth / 2 > Pos.x)
		{
			if (DeltaTime > MaxTime)
			{
				count += 0.02f;
				Pos.x = Math::Lerpf(0, Camera::Get()->GetCamPos().x + WinMaxWidth / 2, count);
				Pos.y = Math::Lerpf(WinMaxHeight, Camera::Get()->GetCamPos().y + WinMaxHeight / 5 * 3, count);
				SetPos(Pos);
				DeltaTime = 0;
			}
			else
			{
				DeltaTime += Time::Delta();
			}
		}
		else
		{
			bInPos = true;
		}
		if (bInPos)
		{
			Pos.x = Camera::Get()->GetCamPos().x + WinMaxWidth / 2;
			Pos.y = Camera::Get()->GetCamPos().y + WinMaxHeight / 5 * 3;
			SetPos(Pos);
			Blink();
		}

		MissionStart->Update();
	}
}

void Start::Render()
{
	if (isRender)
	{
		MissionStart->Render();
	}
}

void Start::SetPos(Vector3 pos)
{
	MissionStart->Move(pos);
}

void Start::Blink()
{
	static float deltaTime = 0;
	static int temp = 0;
	if (isRender && deltaTime > 0.5f)
	{
		deltaTime = 0;
		isRender = false;
		if (temp > 1)
		{
			bIsActive = false;
		}
	}
	else if (!isRender && deltaTime > 0.2f)
	{
		temp++;
		deltaTime = 0;
		isRender = true;
	}
	else
		deltaTime += Time::Delta();
}
