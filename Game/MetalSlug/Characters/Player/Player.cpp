#include "stdafx.h"
#include "Player.h"
#include "Utilities/Animator.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	:
	PlayerAnimationRect(position,size,rotation)
{
	this->position = position;
	this->size = size;
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
	if (!isEnd)
	{
		/*임시*/
		if (Keyboard::Get()->Down('1'))
		{
			PlayerProjectileType = PROJECTILETYPE::HEAVY;
			upperBody->SetisPistol(false);
			Ammo = 200;
		}
		AmmoCheck();
		if (!isDie)
		{
			Input();
			//체력 체크
			HPCheck();

		}
		else
		{
			static float DeltaTime = 0;

			if (DeltaTime > 2.0f)
			{
				DeltaTime = 0;
				isDestroy = true;
			}
			else
				DeltaTime += Time::Delta();
		}
		//jump
		Jump();
		if (isGround || isObject)
		{
			isGround = true;
			isJumpEnd = false;
			nJumpCount = 0;
		}
		else
		{
			Move({ 0,GravatiyPower,0 });
		}
	}
	//ani세팅
	SetLowerAni();
	SetUpperAni();
	lowerBody->Update();
	upperBody->Update();


}

void Player::Render()
{
	//PlayerAnimationRect::Render();
	lowerBody->Render();
	upperBody->Render();
}

void Player::Input()
{
	static bool isFirstHandUp = false;
	static bool isFirstCrouchJump = false;
	//공격
	if (isAtk)
	{
		if (upperBody->GetisPistol())
		{
			if (Keyboard::Get()->Down(VK_DOWN))
			{
				isAtk = false;
				isKnife = false;
				for (Projectile* temp : PM->GetList())
				{
					if (temp->GetPT() == PROJECTILETYPE::KNIFE)
					{
						PM->RemoveProjectile(temp);
					}
				}
			}
			else if (Keyboard::Get()->Down(VK_UP))
			{
				isAtk = false;
				isKnife = false;
				for (Projectile* temp : PM->GetList())
				{
					if (temp->GetPT() == PROJECTILETYPE::KNIFE)
					{
						PM->RemoveProjectile(temp);
					}
				}
			}
		}
		else
		{
			if (Keyboard::Get()->Down(VK_DOWN))
			{
				isKnife = false;
				for (Projectile* temp : PM->GetList())
				{
					if (temp->GetPT() == PROJECTILETYPE::KNIFE)
					{
						PM->RemoveProjectile(temp);
					}
				}
			}
			else if (Keyboard::Get()->Down(VK_UP))
			{
				isKnife = false;
				for (Projectile* temp : PM->GetList())
				{
					if (temp->GetPT() == PROJECTILETYPE::KNIFE)
					{
						PM->RemoveProjectile(temp);
					}
				}
			}
		}
		if (Keyboard::Get()->Down(VK_RIGHT))//우측 입력
		{
			isAtk = false;
			isKnife = false;
			for (Projectile* temp : PM->GetList())
			{
				if (temp->GetPT() == PROJECTILETYPE::KNIFE)
				{
					PM->RemoveProjectile(temp);
				}
			}
		}
		else if (Keyboard::Get()->Down(VK_LEFT))//우측 입력
		{
			isAtk = false;
			isKnife = false;
			for (Projectile* temp : PM->GetList())
			{
				if (temp->GetPT() == PROJECTILETYPE::KNIFE)
				{
					PM->RemoveProjectile(temp);
				}
			}
		}
		else if (!upperBodyAnimator->isFirstPlay)
		{
			if (soldierUpperState != SOLDIERSTATE::CROUCHJUMP)
			{
				isAtk = false;
				isKnife = false;
				for (Projectile* temp : PM->GetList())
				{
					if (temp->GetPT() == PROJECTILETYPE::KNIFE)
					{
						PM->RemoveProjectile(temp);
					}
				}
			}
		}
	}
	static float fireDeltaTime = 0.0f;
	static float ThrowDeltaTime = 0.0f;
	if (Keyboard::Get()->Down('A'))
	{
		if(fireDeltaTime > fireRate)//일정 시간 마다 실행하여 
		{
			//칼질
			if (!isKnife)
			{
				Knife();
			}
			//사격
			if (!isKnife)
			{
				Fire(isFirstHandUp, isFirstCrouchJump);
				switch (soldierUpperState)
				{
				case SOLDIERSTATE::ATK:
					upperBody->SetClip("ATK");
					break;
				case SOLDIERSTATE::CROUCHATK:
					upperBody->SetClip("CrouchATK");
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
				fireDeltaTime = 0;
			}
		}
	}
	else//작동환경과 상관없이 일정하게 맞춰준다
		fireDeltaTime += Time::Delta();

	
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
	if (isThrow)
	{
		if (!upperBodyAnimator->isFirstPlay)
		{
			isThrow = false;
		}
		if (isAtk)
		{
			isThrow = false;
		}
	}
	else if (Keyboard::Get()->Down('D'))
	{
		if (!isAtk)
		{
			if (ThrowDeltaTime > ThrowRate)//일정 시간 마다 실행하여 //fireRate를 사용해서 연속 던지기 구현
			{
				ThrowCount++;
				Grenade();
			}
		}
	}
	else
		ThrowDeltaTime += Time::Delta();

	//상하
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

	if (Keyboard::Get()->Press(VK_DOWN))//아래키 입력
	{
		isCrouch = true;
		//collider 크기 조절
		if (!isGround)
		{
			ColliderSizeChange(COLLIDER::BIG);
		}
		else
		{
			ColliderSizeChange(COLLIDER::SMALL);
		}
		if (!upperBody->GetisPistol())
		{
			DownPressTime += Time::Delta();
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
		DownPressTime = 0;
	}
	else if (Keyboard::Get()->Press(VK_UP))
	{
		isHandUp = true;
		if (!upperBody->GetisPistol())
		{
			UpPressTime += Time::Delta();
		}
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
		UpPressTime = 0;
	}
	else
	{
		isCrouch = false;
		ColliderSizeChange(COLLIDER::BIG);
	}

	//firepos세팅
	MoveFirePos(isFirstHandUp, isFirstCrouchJump);
	HeavyFire();


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
	else if (isCrouch && isThrow)
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
				
				if (isKnife)
				{
					soldierUpperState = SOLDIERSTATE::KNIFEATK;
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
			if (isKnife)
			{
				soldierUpperState = SOLDIERSTATE::CROUCHKNIFEATK;
			}
			else
			{
				soldierUpperState = SOLDIERSTATE::CROUCHATK;
			}
		}
		else if (isThrow)
		{//앉아서 움직이는 상태
			soldierUpperState = SOLDIERSTATE::CROUCHTHROW;
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
	{//idle 상태
		if (isAtk)
		{
			if (isKnife)
			{
				soldierUpperState = SOLDIERSTATE::KNIFEATK;
			}
			else
			{
				soldierUpperState = SOLDIERSTATE::ATK;
			}
		}
		else
		{
			soldierUpperState = SOLDIERSTATE::IDLE;
		}
	}
	if (isThrow)
	{
		if (isCrouch)
		{
			if (!isGround)
			{
				upperBody->SetClip("Throw");
				soldierUpperState = SOLDIERSTATE::THROW;
			}
			else
			{
				upperBody->SetClip("CrouchThrow");
				soldierUpperState = SOLDIERSTATE::CROUCHTHROW;
			}
		}
		else
		{
			upperBody->SetClip("Throw");
			soldierUpperState = SOLDIERSTATE::THROW;
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

void Player::Knife()
{
	if (dir == DIRECTION::RIGHT)
	{
		for (Enemy* temp : EM->GetEnemyList())
		{
			if (temp->GetTransformedCoord().Point.x > r.Point.x)
			{
				if (Math::Distance(temp->GetTransformedCoord().Point, this->r.Point) <= KnifeRange)
				{
					if (temp->GetET() == ENEMYTYPE::Grenadier)
					{
						if (dynamic_cast<EnemySoldier*>(temp)->GetState()!=ENEMYSOLDIERSTATE::DIE)
						{
							firePos.Rotation = 0;
							isKnife = true;
							isAtk = true;
							if (isCrouch)
							{
								PM->AddBullet(r.Point + Vector3(KnifeRange / 2, 0, 0), Vector3(KnifeRange, 5 * IMGsize, 1), firePos.Rotation, dir, PROJECTILETYPE::KNIFE);
								upperBody->SetClip("CrouchKnifeATK");
								soldierUpperState = SOLDIERSTATE::CROUCHKNIFEATK;
							}
							else
							{
								PM->AddBullet(r.Point + Vector3(KnifeRange / 2, 0, 0), Vector3(KnifeRange, 5 * IMGsize, 1), firePos.Rotation, dir, PROJECTILETYPE::KNIFE);
								upperBody->SetClip("KnifeATK");
								soldierUpperState = SOLDIERSTATE::KNIFEATK;
							}
						}
					}
				}
			}
		}
	}
	else if(dir == DIRECTION::LEFT)
	{
		for (Enemy* temp : EM->GetEnemyList())
		{
			if (temp->GetTransformedCoord().Point.x < r.Point.x)
			{
				if (Math::Distance(temp->GetTransformedCoord().Point, this->r.Point) < KnifeRange)
				{
					firePos.Rotation = 0;
					isKnife = true;
					isAtk = true;
					if (isCrouch)
					{
						PM->AddBullet(r.Point - Vector3(KnifeRange / 2, 0, 0), Vector3(KnifeRange, 5 * IMGsize, 1), firePos.Rotation, dir, PROJECTILETYPE::KNIFE);
						upperBody->SetClip("CrouchKnifeATK");
						soldierUpperState = SOLDIERSTATE::CROUCHKNIFEATK;
					}
					else
					{
						PM->AddBullet(r.Point - Vector3(KnifeRange / 2, 0, 0), Vector3(KnifeRange, 5 * IMGsize, 1), firePos.Rotation, dir, PROJECTILETYPE::KNIFE);
						upperBody->SetClip("KnifeATK");
						soldierUpperState = SOLDIERSTATE::KNIFEATK;
					}
				}

			}
		}
	}
}

void Player::Fire(bool isFirstHandUp,bool isFirstCrouchJump)
{
	isAtk = true;
	if (upperBody->GetisPistol())
	{
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
	}
	else
	{
		if (isHandUp)
		{	
			if (isFirstHandUp)
			{
				upperBody->SetClip("UpsideATKStart", true);
				soldierUpperState = SOLDIERSTATE::UPSIDEATKSTART;
			}
			else
			{
				upperBody->SetClip("UpsideATK", true);
				soldierUpperState = SOLDIERSTATE::UPSIDEATK;
			}
		}
		else if (isCrouch)
		{
			if (!isGround)
			{
				if (isFirstCrouchJump)
				{
					upperBody->SetClip("CrouchJumpATKStart", true);
					soldierUpperState = SOLDIERSTATE::CROUCHJUMPATKSTART;
				}
				else 
				{
					upperBody->SetClip("CrouchJumpATK", true);
					soldierUpperState = SOLDIERSTATE::CROUCHJUMPATK;
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
	}
	MoveFirePos(isFirstHandUp,isFirstCrouchJump);
	switch (PlayerProjectileType)
	{
	case PROJECTILETYPE::PISTOL:
	//pistol
		PM->AddBullet(firePos.Pos, Vector3(17, 3*IMGsize, 1), firePos.Rotation, dir, PlayerProjectileType);
		break;
	case PROJECTILETYPE::HEAVY:
	//Heavy
		isHeavyFire = true;
		HeavyFireCount = 6;
		break;
	default:
		break;
	}
}

void Player::Grenade()
{
	isThrow = true;
	if (upperBody->GetisPistol())
	{
		if (isCrouch)
		{
			if (!isGround)
			{
				upperBody->SetClip("Throw", true);
				soldierUpperState = SOLDIERSTATE::THROW;
			}
			else
			{
				upperBody->SetClip("CrouchThrow", true);
				soldierUpperState = SOLDIERSTATE::CROUCHTHROW;
			}
		}
		else
		{
			upperBody->SetClip("Throw", true);
			soldierUpperState = SOLDIERSTATE::THROW;
		}
	}
	else
	{
		if (isCrouch)
		{
			if (!isGround)
			{
				upperBody->SetClip("Throw", true);
				soldierUpperState = SOLDIERSTATE::THROW;
			}
			else
			{
				upperBody->SetClip("CrouchThrow", true);
				soldierUpperState = SOLDIERSTATE::CROUCHTHROW;
			}
		}
		else
		{
			upperBody->SetClip("Throw", true);
			soldierUpperState = SOLDIERSTATE::THROW;
		}
		
	}

	if (Bomb > 0)
	{
		--Bomb;
		PM->AddGrenade(firePos.Pos, Vector3(19 * IMGsize, 19 * IMGsize, 1), firePos.Rotation, dir, PROJECTILETYPE::Grenade);
	}
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

void Player::MoveFirePos(bool isFirstHandUp, bool isFirstCrouchJump)
{
	if (upperBody->GetisPistol())
	{
		if (isHandUp)
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(11 * IMGsize, 55 * IMGsize, 0);
				firePos.Rotation = 90.0f;
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(12 * IMGsize, 55 * IMGsize, 0);
				firePos.Rotation = 90.0f;
			}
		}
		else if (isCrouch)
		{
			if (!isGround)
			{
				if (dir == DIRECTION::LEFT)
				{
					firePos.Pos = position + Vector3(10 * IMGsize, 6 * IMGsize, 0);
					firePos.Rotation = -90.0f;
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Pos = position + Vector3(12 * IMGsize, 6 * IMGsize, 0);
					firePos.Rotation = -90.0f;
				}
			}
			else
			{
				if (dir == DIRECTION::LEFT)
				{
					firePos.Rotation = 180.0f;
					firePos.Pos = position + Vector3(-10 * IMGsize, 17 * IMGsize, 0);
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Rotation = 0.0f;
					firePos.Pos = position + Vector3(37 * IMGsize, 17 * IMGsize, 0);
				}
			}
		}
		else
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180.0f;
				firePos.Pos = position + Vector3(-10 * IMGsize, 27 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = 0.0f;
				firePos.Pos = position + Vector3(37 * IMGsize, 27 * IMGsize, 0);
			}
		}
	}
	else
	{
		//투척 관련
		if (isHandUp)
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(11 * IMGsize, 55 * IMGsize, 0);
				firePos.Rotation = 90.0f;
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(12 * IMGsize, 55 * IMGsize, 0);
				firePos.Rotation = 90.0f;
			}
		}
		else if (isCrouch)
		{
			if (!isGround)
			{
				if (dir == DIRECTION::LEFT)
				{
					firePos.Pos = position + Vector3(10 * IMGsize, 6 * IMGsize, 0);
					firePos.Rotation = -90.0f;
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Pos = position + Vector3(12 * IMGsize, 6 * IMGsize, 0);
					firePos.Rotation = -90.0f;
				}
			}
			else
			{
				if (dir == DIRECTION::LEFT)
				{
					firePos.Rotation = 180.0f;
					firePos.Pos = position + Vector3(-10 * IMGsize, 17 * IMGsize, 0);
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Rotation = 0.0f;
					firePos.Pos = position + Vector3(37 * IMGsize, 17 * IMGsize, 0);
				}
			}
		}
		else
		{
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180.0f;
				firePos.Pos = position + Vector3(-10 * IMGsize, 27 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = 0.0f;
				firePos.Pos = position + Vector3(37 * IMGsize, 27 * IMGsize, 0);
			}
		}
		//사격 관련
		switch (soldierUpperState)
		{
		case SOLDIERSTATE::UPSIDEATKSTART:
			firePos.Rotation = Math::Lerpf(0, 90, UpPressTime * 10);
			if (firePos.Rotation >= 90)
			{
				firePos.Rotation = 90; 
				if (dir == DIRECTION::LEFT)
				{
					firePos.Pos = position + Vector3(9 * IMGsize, 60 * IMGsize, 0);
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Pos = position + Vector3(9 * IMGsize, 60 * IMGsize, 0);
				}
				break;
			}
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180 - firePos.Rotation;
				firePos.Pos = r.Point;
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = r.Point;
			}
			break;
		case SOLDIERSTATE::UPSIDEATK:
			firePos.Rotation = 90.0f;
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(9 * IMGsize, 60 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(9 * IMGsize, 60 * IMGsize, 0);
			}
			break;
		case SOLDIERSTATE::CROUCHJUMPATKSTART:
			firePos.Rotation = Math::Lerpf(0, 90, DownPressTime * 10);
			if (firePos.Rotation >= 90)
			{
				firePos.Rotation = -90;
				if (dir == DIRECTION::LEFT)
				{
					firePos.Pos = position + Vector3(18 * IMGsize, 0 * IMGsize, 0);
				}
				else if (dir == DIRECTION::RIGHT)
				{
					firePos.Pos = position + Vector3(6 * IMGsize, 0 * IMGsize, 0);
				}
				break;
			}
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = -(180 - firePos.Rotation);
				firePos.Pos = r.Point + Vector3(0, 10, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = - firePos.Rotation;
				firePos.Pos = r.Point + Vector3(0, 10, 0);
			}
			break;
		case SOLDIERSTATE::CROUCHJUMPATK:
			firePos.Rotation = -90.0f;
			if (dir == DIRECTION::LEFT)
			{
				firePos.Pos = position + Vector3(18 * IMGsize, 0 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Pos = position + Vector3(6 * IMGsize, 0 * IMGsize, 0);
			}
			break;
		case SOLDIERSTATE::CROUCHATK:
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180.0f;
				firePos.Pos = position + Vector3(-15 * IMGsize, 17 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = 0.0f;
				firePos.Pos = position + Vector3(45 * IMGsize, 17 * IMGsize, 0);
			}
			break;
		case SOLDIERSTATE::ATK:
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180.0f;
				firePos.Pos = position + Vector3(-15 * IMGsize, 19 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = 0.0f;
				firePos.Pos = position + Vector3(38 * IMGsize, 19 * IMGsize, 0);
			}
			break;
		case SOLDIERSTATE::IDLE:
			if (dir == DIRECTION::LEFT)
			{
				firePos.Rotation = 180.0f;
				firePos.Pos = position + Vector3(-15 * IMGsize, 19 * IMGsize, 0);
			}
			else if (dir == DIRECTION::RIGHT)
			{
				firePos.Rotation = 0.0f;
				firePos.Pos = position + Vector3(38 * IMGsize, 19 * IMGsize, 0);
			}
			break;
		default:
			break;
		}
	}
}

void Player::ColliderSizeChange(COLLIDER val)
{
	if (val==COLLIDER::SMALL)
	{
		this->size = Vector3(90, 25 * 3, 1);
	}
	else if(val == COLLIDER::BIG)
	{
		this->size = Vector3(90, 40 * 3, 1);
	}
	else if (val == COLLIDER::NONE)
	{
		this->size = Vector3(0,0,0);
	}

	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void Player::HeavyFire()
{
	if (isHeavyFire)
	{
		static float deltaTime = 0.0f;
		if (deltaTime > HeavyfireRate&&HeavyFireCount>0)
		{
			PM->AddBullet(firePos.Pos+Vector3(0,(HeavyFireCount%3)*2*IMGsize,0), Vector3(24 * IMGsize, 4 * IMGsize, 1), firePos.Rotation, dir, PlayerProjectileType);
			--Ammo;
			deltaTime = 0.0f;
			HeavyFireCount--;
			if (HeavyFireCount == 0)
			{
				isHeavyFire = false;
			}
		}
		else
			deltaTime += Time::Delta();
	}
}

void Player::Hit(DAMAGE val, Projectile* tempProjectile)
{
	static Projectile* PrevTemp;
	Projectile* NowTemp;
	NowTemp = tempProjectile;
	HitBy = NowTemp->GetPT();
	if (tempProjectile == nullptr)
	{
		PlayerHP -= val;
		return;
	}

	if (NowTemp != PrevTemp)
	{
		PlayerHP -= val;
	}
	PrevTemp = NowTemp;

}

void Player::HPCheck()
{
	if (PlayerHP <= 0)
	{
		Die();
	}
}

void Player::Die()
{
	isDie = true;
	ColliderSizeChange(COLLIDER::NONE);
	soldierUpperState = SOLDIERSTATE::DIE;
	soldierLowerState = SOLDIERSTATE::NONE;
}

void Player::Win()
{
	isEnd = true;
	soldierUpperState = SOLDIERSTATE::WIN;
}

void Player::AmmoCheck()
{
	if (Ammo <= 0)
	{
		PlayerProjectileType = PROJECTILETYPE::PISTOL;
		upperBody->SetisPistol(true);
		Ammo = 0;
	}
	else if(PlayerProjectileType == PROJECTILETYPE::HEAVY)
	{
		upperBody->SetisPistol(false);
	}
}

void Player::ItemTake(PROJECTILETYPE ItemInfo)
{
	switch (ItemInfo)
	{
	case PROJECTILETYPE::HEAVY:
		if (PlayerProjectileType == PROJECTILETYPE::HEAVY)
		{
			Ammo += 200;
		}
		else
		{
			Ammo = 200;
		}
		PlayerProjectileType = PROJECTILETYPE::HEAVY;
		upperBody->SetisPistol(false);
		break;
	case PROJECTILETYPE::Grenade:
		PlayerProjectileType = PROJECTILETYPE::Grenade;
		Bomb += 10;
		break;
	
	default:
		break;
	}
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
		case SOLDIERSTATE::KNIFEATK:
			upperBody->SetClip("KnifeATK");
			break;
		case SOLDIERSTATE::THROW:
			upperBody->SetClip("Throw");
			break;
		case SOLDIERSTATE::CROUCHIDLE:
			upperBody->SetClip("CrouchIdle");
			break;
		case SOLDIERSTATE::CROUCHATK:
			upperBody->SetClip("CrouchATK");
			break;
		case SOLDIERSTATE::CROUCHKNIFEATK:
			upperBody->SetClip("CrouchKnifeATK");
			break;
		case SOLDIERSTATE::CROUCHTHROW:
			upperBody->SetClip("CrouchThrow");
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
		case SOLDIERSTATE::DIE:
			if (HitBy == PROJECTILETYPE::KNIFE)
			{
				upperBody->SetClip("KnifeDie");
			}
			else
			{
				upperBody->SetClip("Die");
			}
			break;
		case SOLDIERSTATE::WIN:
			upperBody->SetClip("Win");
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