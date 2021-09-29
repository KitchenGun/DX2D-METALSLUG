#include "stdafx.h"
#include "Timer.h"

Timer::Timer(PlayerManager* pm)
	:pm(pm)
{
	subUI = new TextureRect(Camera::Get()->GetCamPos(), Vector3(167 * 3, 16 * 3, 1), 0);
	subUI->SetSRV(L"./_Textures/UI/PushStart.png");
	timer0 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 4, 16 * 4, 1), 0);
	timer0->SetSRV(L"./_Textures/UI/Timer0.png");
	timer1 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 4, 16 * 4, 1), 0);
	timer1->SetSRV(L"./_Textures/UI/Timer0.png");
}

Timer::~Timer()
{
	SAFE_DELETE(pm);
	SAFE_DELETE(timer1);
	SAFE_DELETE(timer0);
	SAFE_DELETE(subUI);
}

void Timer::Update()
{
	SetPos(Camera::Get()->GetCamPos() + Vector3(400, WinMaxHeight - 50, 0));
	Blink();
	TimerChange();
}

void Timer::Render()
{
	if (isRender)
	{
		subUI->Render();
	}
	timer0->Render();
	timer1->Render();
}

void Timer::SetPos(Vector3 pos)
{
	subUI->Move(pos + Vector3(550, -5, 0));
	timer0->Move(pos + Vector3(180, -5, 0));
	timer1->Move(pos + Vector3(240, -5, 0));
}

void Timer::TimerChange()
{
	if (pm->GetPlayer()->GetUpperState() == SOLDIERSTATE::DIE)
	{
		timer = 60;
	}
	timer -= (Time::Delta()/2);
	switch ((int)timer/10)
	{
	case 0:
		timer0->SetSRV(L"./_Textures/UI/Timer0.png");
		break;
	case 1:
		timer0->SetSRV(L"./_Textures/UI/Timer1.png");
		break;
	case 2:
		timer0->SetSRV(L"./_Textures/UI/Timer2.png");
		break;
	case 3:
		timer0->SetSRV(L"./_Textures/UI/Timer3.png");
		break;
	case 4:
		timer0->SetSRV(L"./_Textures/UI/Timer4.png");
		break;
	case 5:
		timer0->SetSRV(L"./_Textures/UI/Timer5.png");
		break;
	case 6:
		timer0->SetSRV(L"./_Textures/UI/Timer6.png");
		break;
	case 7:
		timer0->SetSRV(L"./_Textures/UI/Timer7.png");
		break;
	case 8:
		timer0->SetSRV(L"./_Textures/UI/Timer8.png");
		break;
	case 9:
		timer0->SetSRV(L"./_Textures/UI/Timer9.png");
	default:
		break;
	}
	switch ((int)timer % 10)
	{
	case 0:
		timer1->SetSRV(L"./_Textures/UI/Timer0.png");
		break;
	case 1:
		timer1->SetSRV(L"./_Textures/UI/Timer1.png");
		break;
	case 2:
		timer1->SetSRV(L"./_Textures/UI/Timer2.png");
		break;
	case 3:
		timer1->SetSRV(L"./_Textures/UI/Timer3.png");
		break;
	case 4:
		timer1->SetSRV(L"./_Textures/UI/Timer4.png");
		break;
	case 5:
		timer1->SetSRV(L"./_Textures/UI/Timer5.png");
		break;
	case 6:
		timer1->SetSRV(L"./_Textures/UI/Timer6.png");
		break;
	case 7:
		timer1->SetSRV(L"./_Textures/UI/Timer7.png");
		break;
	case 8:
		timer1->SetSRV(L"./_Textures/UI/Timer8.png");
		break;
	case 9:
		timer1->SetSRV(L"./_Textures/UI/Timer9.png");
	default:
		break;
	}
}

void Timer::Blink()
{
	static float deltaTime = 0;
	if (isRender && deltaTime > 1.0f)
	{
		deltaTime = 0;
		isRender = false;
	}
	else if (!isRender && deltaTime > 0.5f)
	{
		deltaTime = 0;
		isRender = true;
	}
	else
		deltaTime += Time::Delta();
}
