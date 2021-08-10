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
	if (Keyboard::Get()->Down('S'))
	{
		soldierState = SOLDIERSTATE::JUMP;
		lowerBody->SetClip("Jump");
		upperBody->SetClip("Jump");
	}

	if (Keyboard::Get()->Press(VK_DOWN))//아래키 입력
	{
		isCrouch = true;
		soldierState = SOLDIERSTATE::CROUCH;
		upperBody->SetClip("CrouchIdle");
	}
	else if (Keyboard::Get()->Up(VK_DOWN))
	{
		isCrouch = false;
		soldierState = SOLDIERSTATE::IDLE;
		lowerBody->SetClip("Idle");
		upperBody->SetClip("Idle");
	}

	if (Keyboard::Get()->Press(VK_RIGHT))//우측 입력
	{
		dir = DIRECTION::RIGHT;
		if (isCrouch)
		{
			soldierState = SOLDIERSTATE::CROUCHMOVE;
			upperBody->SetClip("RCrouchMove");
		}
		else
		{
			soldierState = SOLDIERSTATE::MOVE;
			lowerBody->SetClip("RMove");
			upperBody->SetClip("Idle");
		}
	}
	else if (Keyboard::Get()->Press(VK_LEFT))//좌측 입력
	{
		dir = DIRECTION::LEFT;
		if (isCrouch)
		{
			soldierState = SOLDIERSTATE::CROUCHMOVE;
			upperBody->SetClip("LCrouchMove");
		}
		else
		{
			soldierState = SOLDIERSTATE::MOVE;
			lowerBody->SetClip("LMove");
			upperBody->SetClip("Idle");
		}
	}
	else if (Keyboard::Get()->Up(VK_RIGHT) || Keyboard::Get()->Up(VK_LEFT))//좌우측 입력 종료
	{
		if (isCrouch)
		{
			soldierState = SOLDIERSTATE::CROUCH;
			upperBody->SetClip("CrouchIdle");
		}
		else
		{
			soldierState = SOLDIERSTATE::IDLE;
			lowerBody->SetClip("Idle");
			upperBody->SetClip("Idle");
		}
	}
}





