#include "stdafx.h"
#include "AmmoUI.h"

AmmoUI::AmmoUI(PlayerManager* pm)
	:pm(pm)
{
	MainUI = new TextureRect(Camera::Get()->GetCamPos() + Vector3(500, WinMaxHeight-50, 0), Vector3(62 * 4, 17 * 4, 1), 0);
	MainUI->SetSRV(L"./_Textures/UI/AmmoUI.png");
	ammo0 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(8 * 2, 16 * 1.5f, 1), 0);
	ammo0->SetSRV(L"./_Textures/UI/Ammo0.png");
	ammo1 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(8 * 2, 16 * 1.5f, 1), 0);
	ammo1->SetSRV(L"./_Textures/UI/Ammo0.png");
	ammo2 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(8 * 2, 16 * 1.5f, 1), 0);
	ammo2->SetSRV(L"./_Textures/UI/Ammo0.png");
	bomb0 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(8 * 2, 16 * 1.5f, 1), 0);
	bomb0->SetSRV(L"./_Textures/UI/Ammo0.png");
	bomb1 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(8 * 2, 16 * 1.5f, 1), 0);
	bomb1->SetSRV(L"./_Textures/UI/Ammo0.png");
}

AmmoUI::~AmmoUI()
{
	SAFE_DELETE(MainUI);
}

void AmmoUI::Update()
{
	SetPos(Camera::Get()->GetCamPos() + Vector3(400, WinMaxHeight - 50, 0));
	AmmoNumChange();
	BombNumChange();
}

void AmmoUI::Render()
{
	MainUI->Render();
	ammo0->Render();
	ammo1->Render();
	ammo2->Render();
	bomb0->Render();
	bomb1->Render();
}

void AmmoUI::SetPos(Vector3 pos)
{
	MainUI->Move(pos);
	ammo0->Move(pos + Vector3(-70, -15, 0));
	ammo1->Move(pos + Vector3(-50, -15, 0));
	ammo2->Move(pos + Vector3(-30, -15, 0));
	bomb0->Move(pos + Vector3(50, -15, 0));
	bomb1->Move(pos + Vector3(70, -15, 0));

}

void AmmoUI::AmmoNumChange()
{
	//총알
	if (pm->GetPlayer()->GetAmmo() <= 0)
	{
		ammo0->SetIsRender(false);
		ammo1->SetSRV(L"./_Textures/UI/AmmoInf.png");
		ammo1->SetSize(Vector3(17*3,8*2.0f , 1));
		ammo2->SetIsRender(false);
	}
	else
	{
		ammo0->SetIsRender(true);
		ammo1->SetIsRender(true);
		ammo1->SetSize(Vector3(8 * 2, 16 * 1.5f, 1));
		ammo2->SetIsRender(true);
		//srv 설정
		switch (pm->GetPlayer()->GetAmmo()/100)
		{
		case 0:
			ammo0->SetSRV(L"./_Textures/UI/Ammo0.png");
			break;
		case 1:
			ammo0->SetSRV(L"./_Textures/UI/Ammo1.png");
			break;
		case 2:
			ammo0->SetSRV(L"./_Textures/UI/Ammo2.png");
			break;
		case 3:
			ammo0->SetSRV(L"./_Textures/UI/Ammo3.png");
			break;
		case 4:
			ammo0->SetSRV(L"./_Textures/UI/Ammo4.png");
			break;
		case 5:
			ammo0->SetSRV(L"./_Textures/UI/Ammo5.png");
			break;
		case 6:
			ammo0->SetSRV(L"./_Textures/UI/Ammo6.png");
			break;
		case 7:
			ammo0->SetSRV(L"./_Textures/UI/Ammo7.png");
			break;
		case 8:
			ammo0->SetSRV(L"./_Textures/UI/Ammo8.png");
			break;
		case 9:
			ammo0->SetSRV(L"./_Textures/UI/Ammo9.png");
		default:
			break;
		}

		switch ((pm->GetPlayer()->GetAmmo() % 100)/10)
		{
		case 0:
			ammo1->SetSRV(L"./_Textures/UI/Ammo0.png");
			break;
		case 1:
			ammo1->SetSRV(L"./_Textures/UI/Ammo1.png");
			break;
		case 2:
			ammo1->SetSRV(L"./_Textures/UI/Ammo2.png");
			break;
		case 3:
			ammo1->SetSRV(L"./_Textures/UI/Ammo3.png");
			break;
		case 4:
			ammo1->SetSRV(L"./_Textures/UI/Ammo4.png");
			break;
		case 5:
			ammo1->SetSRV(L"./_Textures/UI/Ammo5.png");
			break;
		case 6:
			ammo1->SetSRV(L"./_Textures/UI/Ammo6.png");
			break;
		case 7:
			ammo1->SetSRV(L"./_Textures/UI/Ammo7.png");
			break;
		case 8:
			ammo1->SetSRV(L"./_Textures/UI/Ammo8.png");
			break;
		case 9:
			ammo1->SetSRV(L"./_Textures/UI/Ammo9.png");
			break;
		default:
			break;
		}
		switch (pm->GetPlayer()->GetAmmo()%10)
		{
		case 0:
			ammo2->SetSRV(L"./_Textures/UI/Ammo0.png");
			break;
		case 1:
			ammo2->SetSRV(L"./_Textures/UI/Ammo1.png");
			break;
		case 2:
			ammo2->SetSRV(L"./_Textures/UI/Ammo2.png");
			break;
		case 3:
			ammo2->SetSRV(L"./_Textures/UI/Ammo3.png");
			break;
		case 4:
			ammo2->SetSRV(L"./_Textures/UI/Ammo4.png");
			break;
		case 5:
			ammo2->SetSRV(L"./_Textures/UI/Ammo5.png");
			break;
		case 6:
			ammo2->SetSRV(L"./_Textures/UI/Ammo6.png");
			break;
		case 7:
			ammo2->SetSRV(L"./_Textures/UI/Ammo7.png");
			break;
		case 8:
			ammo2->SetSRV(L"./_Textures/UI/Ammo8.png");
			break;
		case 9:
			ammo2->SetSRV(L"./_Textures/UI/Ammo9.png");
			break;
		default:
			break;
		}
	}
}

void AmmoUI::BombNumChange()
{
	//srv 설정
	switch (pm->GetPlayer()->GetBomb() / 10)
	{
	case 0:
		bomb0->SetSRV(L"./_Textures/UI/Ammo0.png");
		break;
	case 1:
		bomb0->SetSRV(L"./_Textures/UI/Ammo1.png");
		break;
	case 2:
		bomb0->SetSRV(L"./_Textures/UI/Ammo2.png");
		break;
	case 3:
		bomb0->SetSRV(L"./_Textures/UI/Ammo3.png");
		break;
	case 4:
		bomb0->SetSRV(L"./_Textures/UI/Ammo4.png");
		break;
	case 5:
		bomb0->SetSRV(L"./_Textures/UI/Ammo5.png");
		break;
	case 6:
		bomb0->SetSRV(L"./_Textures/UI/Ammo6.png");
		break;
	case 7:
		bomb0->SetSRV(L"./_Textures/UI/Ammo7.png");
		break;
	case 8:
		bomb0->SetSRV(L"./_Textures/UI/Ammo8.png");
		break;
	case 9:
		bomb0->SetSRV(L"./_Textures/UI/Ammo9.png");
		break;
	default:
		break;
	}
	switch (pm->GetPlayer()->GetBomb() % 10)
	{
	case 0:
		bomb1->SetSRV(L"./_Textures/UI/Ammo0.png");
		break;
	case 1:
		bomb1->SetSRV(L"./_Textures/UI/Ammo1.png");
		break;
	case 2:
		bomb1->SetSRV(L"./_Textures/UI/Ammo2.png");
		break;
	case 3:
		bomb1->SetSRV(L"./_Textures/UI/Ammo3.png");
		break;
	case 4:
		bomb1->SetSRV(L"./_Textures/UI/Ammo4.png");
		break;
	case 5:
		bomb1->SetSRV(L"./_Textures/UI/Ammo5.png");
		break;
	case 6:
		bomb1->SetSRV(L"./_Textures/UI/Ammo6.png");
		break;
	case 7:
		bomb1->SetSRV(L"./_Textures/UI/Ammo7.png");
		break;
	case 8:
		bomb1->SetSRV(L"./_Textures/UI/Ammo8.png");
		break;
	case 9:
		bomb1->SetSRV(L"./_Textures/UI/Ammo9.png");
		break;
	default:
		break;
	}
}
