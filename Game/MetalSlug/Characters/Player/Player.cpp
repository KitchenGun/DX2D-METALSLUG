#include "stdafx.h"
#include "Player.h"
#include "Utilities/Animator.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	:
	PlayerAnimationRect(position,size,rotation)
{
	this->position = position;
	this->IMGsize = 3;
	this->size = size;
	dir = DIRECTION::RIGHT;
	lowerBody = new SoldierLower(position, Vector3(21* IMGsize, 16 * IMGsize, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8 * IMGsize, 0), Vector3(30 * IMGsize, 30 * IMGsize, 1), 0);
	lowerBody->SetPlayer(this);
	upperBody->SetPlayer(this);
	//���� ���� ����
	upperBody->SetisPistol(true);
	upperBodyAnimator = upperBody->GetAnimator();
	//obb
	obbInfo = new OBBInfo;
	//test
	texture = new Texture2D(L"./_Textures/TestBox.png");

	TransformVertices();
}

Player::~Player()
{
	SAFE_DELETE(PM);
	SAFE_DELETE(obbInfo);
	PlayerAnimationRect::~PlayerAnimationRect();
}

void Player::Update()
{
	/*�ӽ�*/
	if (Keyboard::Get()->Down('1'))
	{
		upperBody->SetisPistol(false);
	}

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
	PlayerAnimationRect::Render();
	lowerBody->Render();
	upperBody->Render();
}

void Player::Input()
{
	static bool isFirstHandUp = false;
	static bool isFirstCrouchJump = false;
	//����
	if (Keyboard::Get()->Down('A'))
	{
		Fire(isFirstHandUp, isFirstCrouchJump);
	}

	if (isAtk)
	{
		if (upperBody->GetisPistol())
		{
			if (Keyboard::Get()->Down(VK_DOWN))
			{
				isAtk = false;
			}
			else if (Keyboard::Get()->Down(VK_UP))
			{
				isAtk = false;
			}
		}
		if (Keyboard::Get()->Down(VK_RIGHT))//���� �Է�
		{
			isAtk = false;
		}
		else if (Keyboard::Get()->Down(VK_LEFT))//���� �Է�
		{
			isAtk = false;
		}
		if (!upperBodyAnimator->isFirstPlay)
		{
			if (soldierUpperState != SOLDIERSTATE::CROUCHJUMP)
			{
				isAtk = false;
			}
		}
	}
	//����
	if (isGround)
	{
		if (Keyboard::Get()->Down('S'))
		{
			isJump = true;
			isGround = false;
		}
	}
	//����ź


	//����
	if (isFirstHandUp)
	{
		if (!upperBodyAnimator->isFirstPlay)
		{
			isFirstHandUp = false;
		}
	}
	if (isFirstCrouchJump)
	{
		if (!upperBodyAnimator->isFirstPlay)
		{
			isFirstCrouchJump = false;
		}
	}

	if (Keyboard::Get()->Press(VK_DOWN))//�Ʒ�Ű �Է�
	{
		isCrouch = true;
		//collider ũ�� ����
		if (!isGround)
		{
			ColliderSizeChange(false);
		}
		else
		{
			ColliderSizeChange(true);
		}
	}
	else if (Keyboard::Get()->Down(VK_DOWN))
	{
		isCrouch = true;
		isFirstCrouchJump = true;
	}
	else if (Keyboard::Get()->Up(VK_DOWN))
	{
		isCrouch = false;
		isFirstCrouchJump = false;
	}
	else if (Keyboard::Get()->Press(VK_UP))
	{
		isHandUp = true;
	}
	else if(Keyboard::Get()->Down(VK_UP))
	{
		isHandUp = true;
		isFirstHandUp = true;
	}
	else if (Keyboard::Get()->Up(VK_UP))
	{
		isHandUp = false;
		isFirstHandUp = false;
	}
	else
	{
		isCrouch = false;
		ColliderSizeChange(false);
	}


	//�¿�
	if (isCrouch && isAtk)
	{
		//�ɾƼ� �����ϴ� ��Ȳ������ �̵��� ó�����ϱ� ���ؼ� �����
		if (!isGround)
		{
			if (Keyboard::Get()->Press(VK_RIGHT))//���� �Է�
			{
				if (BlockDir != DIRECTION::RIGHT)
				{
					//Move(Vector3(PlayerSpeed, 0, 0));
				}
				if (isGround)
				{
					dir = DIRECTION::RIGHT;
					isMove = true;
				}
			}
			else if (Keyboard::Get()->Press(VK_LEFT))//���� �Է�
			{
				if (BlockDir != DIRECTION::LEFT)
				{
					//Move(Vector3(-PlayerSpeed, 0, 0));
				}
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
	}
	else
	{
		if (Keyboard::Get()->Press(VK_RIGHT))//���� �Է�
		{
			if (BlockDir != DIRECTION::RIGHT)
			{
				//Move(Vector3(PlayerSpeed, 0, 0));
			}
			if (isGround)
			{
				dir = DIRECTION::RIGHT;
				isMove = true;
			}
		}
		else if (Keyboard::Get()->Press(VK_LEFT))//���� �Է�
		{
			if (BlockDir != DIRECTION::LEFT)
			{
				//Move(Vector3(-PlayerSpeed, 0, 0));
			}
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
				if (!upperBody->GetisPistol())
				{
					if (isFirstCrouchJump)
					{
						soldierUpperState = SOLDIERSTATE::CROUCHJUMPATKSTART;
					}
					else
					{
						soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
					}
				}
				else
				{
					soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
				}
			}
			else
			{
				if (!upperBody->GetisPistol())
				{
					if (isFirstCrouchJump)
					{
						soldierUpperState = SOLDIERSTATE::CROUCHJUMPSTART;
					}
					else
					{
						soldierUpperState = SOLDIERSTATE::CROUCHJUMP;
					}
				}
				else
				{
					soldierUpperState = SOLDIERSTATE::CROUCHJUMP;
				}
			}
		}
		else
		{
			if (isAtk)
			{
				if (isHandUp)
				{
					if (!upperBody->GetisPistol())
					{
						if (isFirstHandUp)
						{
							soldierUpperState = SOLDIERSTATE::UPSIDEATKSTART;
						}
						else
						{
							soldierUpperState = SOLDIERSTATE::UPSIDEATK;
						}
					}
					else
					{
						soldierUpperState = SOLDIERSTATE::UPSIDEATK;
					}
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
		if (isMove)
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
			if (upperBody->GetisPistol())
			{
				if (isFirstHandUp)
				{
					soldierUpperState = SOLDIERSTATE::UPSIDEATKSTART;
				}
				else
				{
					soldierUpperState = SOLDIERSTATE::UPSIDEATK;
				}
			}
			soldierUpperState = SOLDIERSTATE::UPSIDEATK;
		}
		else
		{
			if (!upperBody->GetisPistol())
			{
				if (isFirstHandUp)
				{
					soldierUpperState = SOLDIERSTATE::UPSIDESTART;
				}
				else
				{
					soldierUpperState = SOLDIERSTATE::UPSIDE;
				}
			}
			else
			{
				soldierUpperState = SOLDIERSTATE::UPSIDE;
			}
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
	tempPos.y *= Time::Delta();
	if (isCrouch && isGround)
	{
		tempPos.x /= 3;
	}
	if (obbInfo->isObb&&!isJump)
	{
		tempPos.x /= sqrtf(2);
		ObbGroundMove(tempPos);
	}
	else
	{
		this->position += tempPos;
		D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

		world = S * R * T;
		WB->SetWorld(world);
		RootPos = position + Vector3(size.x / 2, 0, 0);
		TransformVertices();
	}
}

void Player::ObbGroundMove(Vector3 tempPos)
{
	Vector3 pos = Vector3(position.x + tempPos.x, 0, 0);
	pos = Vector3(pos.x, (obbInfo->Gradient * pos.x) + obbInfo->alphaVal, 0);
	this->position = pos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);

	RootPos = position + Vector3(size.x / 2, 0, 0);
	TransformVertices();
}

void Player::Fire(bool isFirstHandUp,bool isFirstCrouchJump)
{
	isAtk = true;

	if (isHandUp)
	{
		if (upperBody->GetisPistol())
		{
			upperBody->SetClip("UpsideATK", true);
			soldierUpperState = SOLDIERSTATE::UPSIDEATK;
		}
		else
		{
			if (isFirstHandUp)
			{
				upperBody->SetClip("UpsideATKStart", true);
				soldierUpperState = SOLDIERSTATE::UPSIDEATKSTART;
			}
		}
	}
	else if (isCrouch)
	{
		if (!isGround)
		{
			if (upperBody->GetisPistol())
			{
				upperBody->SetClip("CrouchJumpATK", true);
				soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
			}
			else
			{
				if (isFirstCrouchJump)
				{
					upperBody->SetClip("CrouchJumpATK", true);
					soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
				}
			}
		}
		else
		{
			upperBody->SetClip("CrouchATK", true);
			soldierUpperState = SOLDIERSTATE::CROUCHATK;
		}
	}
	else
	{
		upperBody->SetClip("ATK", true);
		soldierUpperState = SOLDIERSTATE::ATK;
	}
	MoveFirePos();
	//pistol
	PM->AddBullet(firePos.Pos, Vector3(17, 8, 1), firePos.Rotation, dir, BULLETTYPE::PISTOL);
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


		if (fJumpTime >= 0.8f)
		{
			isJump = false;
		}
		if (fJumpTime >= 1)
		{
			fJumpPower = 0;
			isJumpEnd = true;
		}
		fJumpTime += Time::Delta();
	}
	else
	{
		if (isJumpEnd == true)
		{
			GravatiyPower *= (fJumpTime);
		}
		else
		{
			fJumpTime = 0;
			GravatiyPower = -600;
		}
	}
}

void Player::MoveFirePos()
{
	if (isHandUp)
	{
		if (dir == DIRECTION::LEFT)
		{
			firePos.Pos = position + Vector3(11 * IMGsize, 43 * IMGsize, 0);
			firePos.Rotation = 90.0f;
		}
		else if (dir == DIRECTION::RIGHT)
		{
			firePos.Pos = position + Vector3(12 * IMGsize, 43 * IMGsize, 0);
			firePos.Rotation = 90.0f;
		}
	}
	else if (isCrouch)
	{
		if (!isGround)
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(10 * IMGsize, 20 * IMGsize, 0);
				firePos.Rotation = -90.0f;
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(12 * IMGsize, 19 * IMGsize, 0);
				firePos.Rotation = -90.0f;
			}
		}
		else
		{
			firePos.Rotation = 0.0f;
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(16 * IMGsize, 17 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(16 * IMGsize, 17 * IMGsize, 0);
			}
		}
	}
	else
	{
		firePos.Rotation = 0.0f;
		if (dir == DIRECTION::LEFT)
		{
			firePos.Pos = position + Vector3(16 * IMGsize, 28 * IMGsize, 0);
		}
		else if (dir == DIRECTION::RIGHT)
		{
			firePos.Pos = position + Vector3(16 * IMGsize, 28 * IMGsize, 0);
		}
	}

}

void Player::ColliderSizeChange(bool isSmall)
{
	if (isSmall)
	{
		this->size = Vector3(90, 25 * 3, 1);
	}
	else
	{
		this->size = Vector3(90, 40 * 3, 1);
	}

	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}


void Player::SetUpperAni()
{
	switch (soldierUpperState)
	{
		case SOLDIERSTATE::IDLE:
			upperBody->SetClip("Idle");
			break;
		case SOLDIERSTATE::JUMP:
			upperBody->SetClip("Jump");
			break;
		case SOLDIERSTATE::JUMPMOVE:
			upperBody->SetClip("JumpMove");
			break;
		case SOLDIERSTATE::ATK:
			upperBody->SetClip("ATK");
			break;
		case SOLDIERSTATE::CROUCHIDLE:
			upperBody->SetClip("CrouchIdle");
			break;
		case SOLDIERSTATE::CROUCHATK:
			upperBody->SetClip("CrouchATK");
			break;
		case SOLDIERSTATE::CROUCHJUMP:
			upperBody->SetClip("CrouchJump");
			break;
		case SOLDIERSTATE::CROUCHJUMPSTART:
			if (isAtk)
				upperBody->SetClip("CrouchJumpATKStart");
			else
				upperBody->SetClip("CrouchJumpStart");
			break;
		case SOLDIERSTATE::CROUCHJUMPATK:
			upperBody->SetClip("CrouchJumpATK");
			break;
		case SOLDIERSTATE::CROUCHJUMPATKSTART:
			upperBody->SetClip("CrouchJumpATKStart");
			break;
		case SOLDIERSTATE::CROUCHMOVE:
			upperBody->SetClip("CrouchMove");
			break;
		case SOLDIERSTATE::UPSIDE:
			upperBody->SetClip("Upside");
			break;
		case SOLDIERSTATE::UPSIDESTART:
			if (isAtk)
				upperBody->SetClip("UpsideATKStart");
			else
				upperBody->SetClip("UpsideStart");
			break;
		case SOLDIERSTATE::UPSIDEATK:
			upperBody->SetClip("UpsideATK");
			break;
		case SOLDIERSTATE::UPSIDEATKSTART:
			upperBody->SetClip("UpsideATKStart");
			break;
		default:
			break;
	}
}

void Player::SetLowerAni()
{
	switch (soldierLowerState)
	{
		case SOLDIERSTATE::NONE://��¾���
			break;
		case SOLDIERSTATE::IDLE:
			lowerBody->SetClip("Idle");
			break;
		case SOLDIERSTATE::MOVE:
			lowerBody->SetClip("Move");
			break;
		case SOLDIERSTATE::JUMP:
			lowerBody->SetClip("Jump");
			break;
		case SOLDIERSTATE::JUMPMOVE:
			lowerBody->SetClip("JumpMove");
			break;
		default:
			break;
	}

}





