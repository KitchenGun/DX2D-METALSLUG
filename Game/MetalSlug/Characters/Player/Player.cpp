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
	//jump
	Jump();
	if (isGround)
	{
		isJumpEnd = false;
		nJumpCount = 0;
	}
	else
	{
		Move({ 0,GravatiyPower,0 });
	}
	

}

void Player::Render()
{
	lowerBody->Render();
	upperBody->Render();
}

void Player::Input()
{
	//����
	if (Keyboard::Get()->Down('A'))
	{
		isAtk = true;
	}
	if (Keyboard::Get()->Up('A'))
	{
		isAtk = false;
	}
	//����
	if (isGround)
	{
		if (Keyboard::Get()->Down('S'))
		{
			isJump = true;
		}
	}
	//����ź


	//����
	if (Keyboard::Get()->Press(VK_DOWN))//�Ʒ�Ű �Է�
	{
		isCrouch = true;
	}
	else if (Keyboard::Get()->Up(VK_DOWN))
	{
		isCrouch = false;
	}
	else if (Keyboard::Get()->Press(VK_UP))
	{
		isHandUp = true;
	}
	else if (Keyboard::Get()->Up(VK_UP))
	{
		isHandUp = false;
	}
	//�¿�
	if (isCrouch && isAtk)
	{
		//�ɾƼ� �����ϴ� ��Ȳ������ �̵��� ó�����ϱ� ���ؼ� �����
	}
	else
	{
		if (Keyboard::Get()->Press(VK_RIGHT))//���� �Է�
		{
			Move(Vector3(PlayerSpeed, 0, 0));
			if (isGround)
			{
				dir = DIRECTION::RIGHT;
				isMove = true;
			}
		}
		else if (Keyboard::Get()->Press(VK_LEFT))//���� �Է�
		{
			Move(Vector3(-PlayerSpeed, 0, 0));
			if (isGround)
			{
				dir = DIRECTION::LEFT;
				isMove = true;
			}
		}
		else
		{
			isMove = false;
		}
	}

	//��ݽ� ���� ����
	if (!isGround)
	{
		if (isCrouch)
		{//�ϴܻ���ڼ� ����
			if (isAtk)
			{
				
				soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
			}
			else
			{
				soldierUpperState = SOLDIERSTATE::CROUCHJUMP;
			}
		}
		else
		{
			if (isAtk)
			{
				if (isHandUp)
				{
					soldierUpperState = SOLDIERSTATE::UPSIDEATK;
				}
				else
				{
					soldierUpperState = SOLDIERSTATE::ATK;
				}
			}
			else if (isMove)
			{//���� �̵� ����
				soldierUpperState = SOLDIERSTATE::JUMPMOVE;
			}
			else
			{//�⺻ ���� ����
				soldierUpperState = SOLDIERSTATE::JUMP;
			}
		}
	}
	else if (isCrouch)
	{
		if (isAtk)
		{
			soldierUpperState = SOLDIERSTATE::CROUCHATK;
		}
		else if (isMove)
		{//�ɾƼ� �����̴� ����
			soldierUpperState = SOLDIERSTATE::CROUCHMOVE;
		}
		else
		{//�ɾƸ� �ִ� ����
			soldierUpperState = SOLDIERSTATE::CROUCHIDLE;
		}
	}
	else if (isHandUp)
	{//��� ����ڼ� ����
		if (isAtk)
		{
			soldierUpperState = SOLDIERSTATE::UPSIDEATK;
		}
		else
		{
			soldierUpperState = SOLDIERSTATE::UPSIDE;
		}
	}
	else
	{//idle ����
		if (isAtk)
		{
			soldierUpperState = SOLDIERSTATE::ATK;
		}
		else
		{
			soldierUpperState = SOLDIERSTATE::IDLE;
		}
	}


	//�Ϲݽ� ���� ����
	if (!isGround)
	{
		if (isMove)
		{//���� �̵� ����
			soldierLowerState = SOLDIERSTATE::JUMPMOVE;
		}
		else
		{//�⺻ ���� ����
			soldierLowerState = SOLDIERSTATE::JUMP;
		}
	}
	else if (isCrouch)
	{
		soldierLowerState = SOLDIERSTATE::NONE;
	}
	else if (isMove)
	{
		soldierLowerState = SOLDIERSTATE::MOVE;
	}
	else
	{
		soldierLowerState = SOLDIERSTATE::IDLE;
	}

	//ani����
	SetLowerAni();
	SetUpperAni();
}

void Player::Move(Vector3 tempPos)
{
	tempPos.x *= Time::Delta();
	if (isCrouch&&isGround)
	{
		tempPos.x /= 3;
	}

	this->position += tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);
}

void Player::Jump()
{
	static float fJumpTime = 0;
	if (isJump)
	{
		//��� ��Ȳ ����
		if (fJumpPower <= fMaxJumpSpeed)
		{
			fJumpPower = fMaxJumpSpeed - Math::Lerpf(0, fMaxJumpSpeed, fJumpTime);
			Move({ 0,fJumpPower,0 });
		}


		if (fJumpTime >= 1)
		{
			fJumpPower = 0;
			isJump = false;
			isJumpEnd = true;
		}
		fJumpTime += Time::Delta();
	}
	else
	{
		if (isJumpEnd == true)
		{
			GravatiyPower *= fJumpTime;
		}
		else
		{
			fJumpTime = 0;
			GravatiyPower = -1.0f;
		}
	}
}

void Player::SetUpperAni()
{
	switch (soldierUpperState)
	{
		case SOLDIERSTATE::IDLE:
		{
			upperBody->SetClip("Idle");
			break;
		}
		case SOLDIERSTATE::JUMP:
		{
			upperBody->SetClip("Jump");
			break;
		}
		case SOLDIERSTATE::JUMPMOVE:
		{
			upperBody->SetClip("JumpMove");
			break;
		}
		case SOLDIERSTATE::ATK:
		{
			upperBody->SetClip("ATK");
			break;
		}
		case SOLDIERSTATE::CROUCHIDLE:
		{
			upperBody->SetClip("CrouchIdle");
			break;
		}
		case SOLDIERSTATE::CROUCHATK:
		{
			upperBody->SetClip("CrouchATK");
			break;
		}
		case SOLDIERSTATE::CROUCHJUMP:
		{
			upperBody->SetClip("CrouchJump");
			break;
		}
		case SOLDIERSTATE::CROUCHJUMPATK:
		{
			upperBody->SetClip("CrouchJumpATK");
			break;
		}
		case SOLDIERSTATE::CROUCHMOVE:
		{
			upperBody->SetClip("CrouchMove");
			break;
		}
		case SOLDIERSTATE::UPSIDE:
		{
			upperBody->SetClip("Upside");
			break;
		}
		case SOLDIERSTATE::UPSIDEATK:
		{
			upperBody->SetClip("UpsideATK");
			break;
		}
		default:
			break;
	}
}

void Player::SetLowerAni()
{
	switch (soldierLowerState)
	{
		case SOLDIERSTATE::NONE:
		{//��¾���
			break;
		}
		case SOLDIERSTATE::IDLE:
		{
			lowerBody->SetClip("Idle");
			break;
		}
		case SOLDIERSTATE::MOVE:
		{
			lowerBody->SetClip("Move");
			break;
		}
		case SOLDIERSTATE::JUMP:
		{
			lowerBody->SetClip("Jump");
			break;
		}
		case SOLDIERSTATE::JUMPMOVE:
		{
			lowerBody->SetClip("JumpMove");
			break;
		}
		default:
			break;
	}

}





