#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
{
	lowerBody = new SoldierLower(position, Vector3(21*3, 16 * 3, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8*3, 0), Vector3(30 * 3, 30 * 3, 1), 0);
	lowerBody->SetPlayer(this);
	pos = position;
}

Player::~Player()
{
}

void Player::Update()
{
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		lowerBody->SetClip("RMove");
	}
	else
	{
		lowerBody->SetClip("RIdle");
	}
	lowerBody->Update();
	upperBody->Update();
}

void Player::Render()
{
	lowerBody->Render();
	upperBody->Render();
}


