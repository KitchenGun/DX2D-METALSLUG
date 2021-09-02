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
	cout << String::ToString(size) << endl;
	dir = DIRECTION::RIGHT;
	lowerBody = new SoldierLower(position, Vector3(21* IMGsize, 16 * IMGsize, 1), 0);
	upperBody = new SoldierUpper(position + Vector3(0, 8 * IMGsize, 0), Vector3(30 * IMGsize, 30 * IMGsize, 1), 0);
	lowerBody->SetPlayer(this);
	upperBody->SetPlayer(this);
	//권총 상태 지정
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
	/*임시*/
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
	//공격
	if (Keyboard::Get()->Down('A'))
	{
		Fire();
	}
	if (isAtk)
	{
		if (Keyboard::Get()->Down(VK_DOWN))
		{
			isAtk = false;
		}
		else if (Keyboard::Get()->Down(VK_UP))
		{
			isAtk = false;
		}
		else if (Keyboard::Get()->Down(VK_RIGHT))//우측 입력
		{
			isAtk = false;
		}
		else if (Keyboard::Get()->Down(VK_LEFT))//우측 입력
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

	//점프
	if (isGround)
	{
		if (Keyboard::Get()->Down('S'))
		{
			isJump = true;
			isGround = false;
		}
	}
	//수류탄


	//상하
	if (Keyboard::Get()->Press(VK_DOWN))//아래키 입력
	{
		isCrouch = true;
		//collider 크기 조절
		if (!isGround)
		{
			ColliderSizeChange(false);
		}
		else
		{
			ColliderSizeChange(true);
		}
	}
	else if (Keyboard::Get()->Press(VK_UP))
	{
		isHandUp = true;
	}
	else if (Keyboard::Get()->Up(VK_UP))
	{
		isHandUp = false;
	}
	else
	{
		isCrouch = false;
		ColliderSizeChange(false);
	}



	//좌우
	if (isCrouch && isAtk)
	{
		//앉아서 공격하는 상황에서는 이동을 처리안하기 위해서 사용함
		if (!isGround)
		{
			if (Keyboard::Get()->Press(VK_RIGHT))//우측 입력
			{
				if (BlockDir != DIRECTION::RIGHT)
				{
					Move(Vector3(PlayerSpeed, 0, 0));
				}
				if (isGround)
				{
					dir = DIRECTION::RIGHT;
					isMove = true;
				}
			}
			else if (Keyboard::Get()->Press(VK_LEFT))//좌측 입력
			{
				if (BlockDir != DIRECTION::LEFT)
				{
					Move(Vector3(-PlayerSpeed, 0, 0));
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
		if (Keyboard::Get()->Press(VK_RIGHT))//우측 입력
		{
			if (BlockDir != DIRECTION::RIGHT)
			{
				Move(Vector3(PlayerSpeed, 0, 0));
			}
			if (isGround)
			{
				dir = DIRECTION::RIGHT;
				isMove = true;
			}
		}
		else if (Keyboard::Get()->Press(VK_LEFT))//좌측 입력
		{
			if (BlockDir != DIRECTION::LEFT)
			{
				Move(Vector3(-PlayerSpeed, 0, 0));
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

	//상반신 상태 지정
	if (!isGround)
	{
		if (isCrouch)
		{//하단사격자세 상태
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
			{//점프 이동 상태
				soldierUpperState = SOLDIERSTATE::JUMPMOVE;
			}
			else
			{//기본 점프 상태
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
		{//앉아서 움직이는 상태
			soldierUpperState = SOLDIERSTATE::CROUCHMOVE;
		}
		else
		{//앉아만 있는 상태
			soldierUpperState = SOLDIERSTATE::CROUCHIDLE;
		}
	}
	else if (isHandUp)
	{//상단 사격자세 상태
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
	{//idle 상태
		if (isAtk)
		{
			soldierUpperState = SOLDIERSTATE::ATK;
		}
		else
		{
			soldierUpperState = SOLDIERSTATE::IDLE;
		}
	}


	//하반신 상태 지정
	if (!isGround)
	{
		if (isMove)
		{//점프 이동 상태
			soldierLowerState = SOLDIERSTATE::JUMPMOVE;
		}
		else
		{//기본 점프 상태
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

	//ani세팅
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

void Player::Fire()
{
	isAtk = true;

	if (isHandUp)
	{
		upperBody->SetClip("UpsideATK", true);
		soldierUpperState = SOLDIERSTATE::UPSIDEATK;
	}
	else if (isCrouch)
	{
		if (!isGround)
		{
			upperBody->SetClip("CrouchJumpATK", true);
			soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
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
		//상승 상황 점프
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
	static float Radius = 12 * IMGsize;
	if (isHandUp)
	{
		if (dir == DIRECTION::LEFT)
		{
			firePos.Pos = upperBody->GetPosition() + Vector3(15 * IMGsize, 37 * IMGsize, 0);
			firePos.Rotation = 90.0f;
		}
		else if (dir == DIRECTION::RIGHT)
		{
			firePos.Pos = upperBody->GetPosition() + Vector3(12 * IMGsize, 37 * IMGsize, 0);
			firePos.Rotation = 90.0f;
		}
	}
	else if (isCrouch)
	{
		if (!isGround)
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = upperBody->GetPosition() + Vector3(15 * IMGsize, -10 * IMGsize, 0);
				firePos.Rotation = -90.0f;
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = upperBody->GetPosition() + Vector3(12 * IMGsize, -0 * IMGsize, 0);
				firePos.Rotation = -90.0f;
			}
		}
		else
		{
			firePos.Rotation = 0.0f;
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = upperBody->GetPosition() + Vector3(19 * IMGsize, 17 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = upperBody->GetPosition() + Vector3(38 * IMGsize, 17 * IMGsize, 0);
			}
		}
	}
	else
	{
		firePos.Rotation = 0.0f;
		if (dir == DIRECTION::LEFT)
		{
			firePos.Pos = upperBody->GetPosition() + Vector3(19 * IMGsize, 17 * IMGsize, 0);
		}
		else if (dir == DIRECTION::RIGHT)
		{
			firePos.Pos = upperBody->GetPosition() + Vector3(38 * IMGsize, 17 * IMGsize, 0);
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
		case SOLDIERSTATE::CROUCHJUMPATK:
			upperBody->SetClip("CrouchJumpATK");
			break;
		case SOLDIERSTATE::CROUCHMOVE:
			upperBody->SetClip("CrouchMove");
			break;
		case SOLDIERSTATE::UPSIDE:
			upperBody->SetClip("Upside");
			break;
		case SOLDIERSTATE::UPSIDEATK:
			upperBody->SetClip("UpsideATK");
			break;
		default:
			break;
	}
}

void Player::SetLowerAni()
{
	switch (soldierLowerState)
	{
		case SOLDIERSTATE::NONE://출력안함
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





