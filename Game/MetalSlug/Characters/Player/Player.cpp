#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
{
	pos = position;
	this->size = size.x;
	dir = DIRECTION::RIGHT;
	lowerBody = new SoldierLower(position, Vector3(21* this->size, 16 * this->size, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8 * this->size, 0), Vector3(30 * this->size, 30 * this->size, 1), 0);
	lowerBody->SetPlayer(this);
	upperBody->SetPlayer(this);
}

Player::~Player()
{
}

void Player::Update()
{
	Input();
	lowerBody->Update();
	upperBody->Update();
}

void Player::Render()
{
	lowerBody->Render();
	upperBody->Render();
}

void Player::Input()
{
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		dir = DIRECTION::RIGHT;
		lowerBody->SetClip("RMove");
		upperBody->SetClip("Idle");
	}
	else if(Keyboard::Get()->Press(VK_LEFT))
	{
		dir = DIRECTION::LEFT;
		lowerBody->SetClip("LMove");
		upperBody->SetClip("Idle");
	}
	else
	{
		lowerBody->SetClip("Idle");
	}


}


