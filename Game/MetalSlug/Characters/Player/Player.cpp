#include "stdafx.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
{
	lowerBody = new SoldierLower(position, Vector3(21 * size.x, 16 * size.y, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8*size.y, 0), Vector3(30 * size.x, 30 * size.y, 1), 0);
}

Player::~Player()
{
}

void Player::Update()
{
	lowerBody->Update();
	upperBody->Update();
}

void Player::Render()
{
	lowerBody->Render();
	upperBody->Render();
}


