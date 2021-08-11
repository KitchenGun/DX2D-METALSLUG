#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	:
	AnimationRect(position,size,rotation)
{
	this->position = position;
	this->size = size;
	dir = DIRECTION::RIGHT;
	lowerBody = new SoldierLower(position, Vector3(21* this->size.x, 16 * this->size.x, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8 * this->size.x, 0), Vector3(30 * this->size.x, 30 * this->size.x, 1), 0);
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
		isMove = true;
		dir = DIRECTION::RIGHT;
		Move(Vector3(PlayerSpeed, 0, 0));
		if (soldierState != SOLDIERSTATE::JUMP)
		{
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
	}
	else if (Keyboard::Get()->Press(VK_LEFT))//좌측 입력
	{
		isMove = true;
		dir = DIRECTION::LEFT;
		Move(Vector3(-PlayerSpeed, 0, 0));
		if (soldierState != SOLDIERSTATE::JUMP)
		{
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
	}
	else if (Keyboard::Get()->Up(VK_RIGHT) || Keyboard::Get()->Up(VK_LEFT))//좌우측 입력 종료
	{
		isMove = false;

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

void Player::Move(Vector3 tempPos)
{
	tempPos.x *= Time::Delta();
	if (isCrouch)
	{
		tempPos.x /= 3;
	}


	this->position += tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);
}





