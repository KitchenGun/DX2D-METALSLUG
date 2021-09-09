#include "stdafx.h"
#include "SoldierUpper.h"
#include "Utilities/Animator.h"

SoldierUpper::SoldierUpper(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
	texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
	animator->SetCurrentAnimClip(L"RIdle");
	animator->bLoop = true;
}

SoldierUpper::~SoldierUpper()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void SoldierUpper::Update()
{
	PlayerAnimationRect::Update();
	PivotUpdate();
	
}

void SoldierUpper::Render()
{
	PlayerAnimationRect::Render();
}


void SoldierUpper::SetClip(string name,bool isRestart)
{
	if (isPistol)
	{
		if (name == "Idle")
		{
			isRestart = false;
			SetSize(Vector3(30 * player->GetSize(), 30 * player->GetSize(), 1));
			animator->bLoop = true;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-10 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
				name = "RIdle";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Idle/LUpper.png");
				name = "LIdle";
			}
		}
		else if (name == "Jump")
		{
			isRestart = false;
			SetSize(Vector3(33 * player->GetSize(), 26 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 20 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandUpper.png");
				name = "RJumpHandUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 20 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandUpper.png");
				name = "LJumpHandUpper";
			}
		}
		else if (name == "JumpMove")
		{
			isRestart = false;
			SetSize(Vector3(29 * player->GetSize(), 35 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandRunUpper.png");
				name = "RJumpHandRunUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandRunUpper.png");
				name = "LJumpHandRunUpper";
			}
		}
		else if (name == "CrouchJump")
		{
			isRestart = false;
			SetSize(Vector3(20 * player->GetSize(), 35 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpHandUpper.png");
				name = "RCrouchJumpHandUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpHandUpper.png");
				name = "LCrouchJumpHandUpper";
			}
		}
		else if (name == "CrouchIdle")
		{
			isRestart = false;
			animator->bLoop = true;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetSize(Vector3(34 * player->GetSize(), 24 * player->GetSize(), 1));
				SetPos(player->GetPosition());
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchIdle.png");
				name = "RCrouchIdle";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetSize(Vector3(34 * player->GetSize(), 24 * player->GetSize(), 1));
				SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 0, 0));
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchIdle.png");
				name = "LCrouchIdle";
			}
		}
		else if (name == "CrouchMove")
		{
			isRestart = false;
			SetSize(Vector3(37 * player->GetSize(), 24 * player->GetSize(), 1));
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition());
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMove.png");
				name = "RCrouchMove";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-15 * player->GetSize(), 0, 0));
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMove.png");
				name = "LCrouchMove";
			}
		}
		else if (name == "Upside")
		{
			isRestart = false;
			SetSize(Vector3(30 * player->GetSize(), 27 * player->GetSize(), 1));
			animator->bLoop = true;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 14 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideUpper.png");
				name = "RUpsideUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 14 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideUpper.png");
				name = "LUpsideUpper";
			}
		}
		if (name == "ATK")
		{
			SetSize(Vector3(53 * player->GetSize(), 29 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RFire.png");
				name = "RFire";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LFire.png");
				name = "LFire";
			}
		}
		else if (name == "UpsideATK")
		{
			SetSize(Vector3(28 * player->GetSize(), 66 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 15 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 15 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-4 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RFireUpside.png");
				name = "RFireUpside";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LFireUpside.png");
				name = "LFireUpside";
			}
		}
		else if (name == "CrouchJumpATK")
		{
			SetSize(Vector3(23 * player->GetSize(), 54 * player->GetSize(), 1));
			animator->bLoop = false;

			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/RFireCrouchJump.png");
				name = "RFireCrouchJump";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/LFireCrouchJump.png");
				name = "LFireCrouchJump";
			}
		}
		else if (name == "CrouchATK")
		{
			SetSize(Vector3(52 * player->GetSize(), 29 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/RFireCrouch.png");
				name = "RFireCrouch";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/LFireCrouch.png");
				name = "LFireCrouch";
			}
		}
		else if (name == "KnifeATK")
		{
			SetSize(Vector3(48 * player->GetSize(), 33 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RKnife.png");
				name = "RKnife";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LKnife.png");
				name = "LKnife";
			}
		}
		else if (name == "CrouchKnifeATK")
		{
			SetSize(Vector3(48 * player->GetSize(), 33 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RKnifeCrouch.png");
				name = "RKnifeCrouch";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LKnifeCrouch.png");
				name = "LKnifeCrouch";
			}
		}
	}
	else
	{
		if (name == "Idle")
		{
			isRestart = false;
			SetSize(Vector3(40 * player->GetSize(), 30 * player->GetSize(), 1));
			animator->bLoop = true;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-20 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}

			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Idle/RUpperMachine.png");
				name = "RMachineIdle";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Idle/LUpperMachine.png");
				name = "LMachineIdle";
			}
		}
		else if (name == "Jump")
		{
			isRestart = false;
			SetSize(Vector3(40 * player->GetSize(), 28 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 20 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpMachineUpper.png");
				name = "RJumpMachineUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-15 * player->GetSize(), 20 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpMachineUpper.png");
				name = "LJumpMachineUpper";
			}
		}
		else if (name == "JumpMove")
		{
			isRestart = false;
			SetSize(Vector3(40 * player->GetSize(), 28 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpMachineRunUpper.png");
				name = "RJumpMachineRunUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpMachineRunUpper.png");
				name = "LJumpMachineRunUpper";
			}
		}
		else if (name == "CrouchJump")
		{
			isRestart = false;
			SetSize(Vector3(34 * player->GetSize(), 41 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpMachineUpper.png");
				name = "RCrouchJumpMachineUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpMachineUpper.png");
				name = "LCrouchJumpMachineUpper";
			}
		}
		else if (name == "CrouchJumpStart")
		{
			isRestart = false;
			SetSize(Vector3(34 * player->GetSize(), 41 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpMachineUpperStart.png");
				name = "RCrouchJumpMachineUpperStart";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpMachineUpperStart.png");
				name = "LCrouchJumpMachineUpperStart";
			}
		}
		else if (name == "CrouchIdle")
		{
			isRestart = false;
			animator->bLoop = true;
			SetSize(Vector3(44 * player->GetSize(), 24 * player->GetSize(), 1));
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition());
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMachineIdle.png");
				name = "RCrouchMachineIdle";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 0, 0));
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMachineIdle.png");
				name = "LCrouchMachineIdle";
			}
		}
		else if (name == "CrouchMove")
		{
			isRestart = false;
			SetSize(Vector3(44 * player->GetSize(), 24 * player->GetSize(), 1));
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition());
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMachineMove.png");
				name = "RCrouchMachineMove";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-15 * player->GetSize(), 0, 0));
				animator->bLoop = true;
				texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMachineMove.png");
				name = "LCrouchMachineMove";
			}
		}
		else if (name == "Upside")
		{
			isRestart = false;
			SetSize(Vector3(33 * player->GetSize(), 37 * player->GetSize(), 1));
			animator->bLoop = true;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-10 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-9 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideMachineUpper.png");
				name = "RUpsideMachineUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideMachineUpper.png");
				name = "LUpsideMachineUpper";
			}
		}
		else if (name == "UpsideStart")
		{
			isRestart = false;
			SetSize(Vector3(41 * player->GetSize(), 34 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 9 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 9 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideMachineUpperStart.png");
				name = "RUpsideMachineUpperStart";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideMachineUpperStart.png");
				name = "LUpsideMachineUpperStart";
			}
		}
		if (name == "ATK")
		{
			animator->bLoop = false;
			SetSize(Vector3(63 * player->GetSize(), 28 * player->GetSize(), 1));
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFire.png");
				name = "RMachineFire";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFire.png");
				name = "LMachineFire";
			}
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-42 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-38 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			//사격 동안 애니메이션 텍스쳐만 교체되고 애니메이션 클립이 교체 안되는 문제가 있어서 바로 뒤에 배치
			animator->SetCurrentAnimClip(String::ToWString(name), isRestart);
			return;
		}
		else if (name == "UpsideATK")
		{
			SetSize(Vector3(34 * player->GetSize(), 72 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-13 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-13 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 18 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 18 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireUpside.png");
				name = "RMachineFireUpside";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireUpside.png");
				name = "LMachineFireUpside";
			}
		}
		else if (name == "UpsideATKStart")
		{
			SetSize(Vector3(58 * player->GetSize(), 61 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-33 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-35 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-35 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireUpsideStart.png");
				name = "RMachineFireUpsideStart";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireUpsideStart.png");
				name = "LMachineFireUpsideStart";
			}
		}
		else if (name == "CrouchJumpATK")
		{
			SetSize(Vector3(37 * player->GetSize(), 63 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouchJump.png");
				name = "RMachineFireCrouchJump";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouchJump.png");
				name = "LMachineFireCrouchJump";
			}
		}
		else if (name == "CrouchJumpATKStart")
		{
			SetSize(Vector3(55 * player->GetSize(), 59 * player->GetSize(), 1));
			animator->bLoop = false;
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), -12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), -12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), -15 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), -15 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouchJumpStart.png");
				name = "RMachineFireCrouchJumpStart";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouchJumpStart.png");
				name = "LMachineFireCrouchJumpStart";
			}
		}
		else if (name == "CrouchATK")
		{
			SetSize(Vector3(72 * player->GetSize(), 28 * player->GetSize(), 1));
			animator->bLoop = false;
	
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouch.png");
				name = "RMachineFireCrouch";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-40 * player->GetSize(), 0 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouch.png");
				name = "LMachineFireCrouch";
			}
		}
		else if (name == "KnifeATK")
		{
		SetSize(Vector3(55 * player->GetSize(), 42 * player->GetSize(), 1));
		animator->bLoop = false;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/Character/Fire/RMachineKnife.png");
			name = "RMachineKnife";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/Character/Fire/LMachineKnife.png");
			name = "LMachineKnife";
		}
		}
		else if (name == "CrouchKnifeATK")
		{
		SetSize(Vector3(61 * player->GetSize(), 33 * player->GetSize(), 1));
		animator->bLoop = false;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/Character/Fire/RMachineKnifeCrouch.png");
			name = "RMachineKnifeCrouch";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/Character/Fire/LMachineKnifeCrouch.png");
			name = "LMachineKnifeCrouch";
		}
		}
	}
	animator->SetCurrentAnimClip(String::ToWString(name), isRestart);
}

void SoldierUpper::PivotUpdate()
{
	if (isPistol)
	{
		if (player->GetUpperState() == SOLDIERSTATE::IDLE)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-10 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::JUMPMOVE)
		{
			SetPos(player->GetPosition() + Vector3(0, 5 * player->GetSize(), 0));
		}
		else if (player->GetUpperState() == SOLDIERSTATE::JUMP)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 21 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-6 * player->GetSize(), 22 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDE)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMP)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 3 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::ATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::KNIFEATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-28 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-26 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-28 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDEATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 15 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 15 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-4 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHATK)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 0 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 0 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHKNIFEATK)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(2*player->GetSize(), 0 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 0 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMPATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), -12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), -12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), -15 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -15 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (player->GetUpperState() == SOLDIERSTATE::IDLE)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-20 * player->GetSize(), 8 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(3 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::JUMPMOVE)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 16 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 15 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::JUMP)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-3 * player->GetSize(), 18 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-16 * player->GetSize(), 18 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDE)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-9 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDESTART)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 9 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 9 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-18 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMP)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -5 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -5 * player->GetSize(), 0));
				}
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMPSTART)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-5 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -5 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -5 * player->GetSize(), 0));
				}
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::ATK)
		{
		switch (player->GetLowerState())
		{
		case SOLDIERSTATE::IDLE:
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 12 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-40 * player->GetSize(), 12 * player->GetSize(), 0));
			}
			break;
		case SOLDIERSTATE::MOVE:
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 12 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-40 * player->GetSize(), 12 * player->GetSize(), 0));
			}
			break;
		case SOLDIERSTATE::JUMP:
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-4 * player->GetSize(), 18 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-40 * player->GetSize(), 18 * player->GetSize(), 0));
			}
			break;
		case SOLDIERSTATE::JUMPMOVE:
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(4 * player->GetSize(), 16 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-38 * player->GetSize(), 16 * player->GetSize(), 0));
			}
			break;
		default:
			break;
		}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::KNIFEATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-7 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-26 * player->GetSize(), 0 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-7 * player->GetSize(), 2 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-26 * player->GetSize(), 2 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-28 * player->GetSize(), 10 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), 12 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDEATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::IDLE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-13 * player->GetSize(), 14 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::MOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(2 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 16 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-13 * player->GetSize(), 20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 18 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), 18 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::UPSIDEATKSTART)
		{
			switch (player->GetLowerState())
			{
				case SOLDIERSTATE::IDLE:
					if (player->GetDir() == DIRECTION::RIGHT)
					{
						SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), 14 * player->GetSize(), 0));
					}
					else if (player->GetDir() == DIRECTION::LEFT)
					{
						SetPos(player->GetPosition() + Vector3(-33 * player->GetSize(), 14 * player->GetSize(), 0));
					}
					break;
				case SOLDIERSTATE::JUMP:
					if (player->GetDir() == DIRECTION::RIGHT)
					{
						SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), 20 * player->GetSize(), 0));
					}
					else if (player->GetDir() == DIRECTION::LEFT)
					{
						SetPos(player->GetPosition() + Vector3(-35 * player->GetSize(), 20 * player->GetSize(), 0));
					}
					break;
				case SOLDIERSTATE::JUMPMOVE:
					if (player->GetDir() == DIRECTION::RIGHT)
					{
						SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), 16 * player->GetSize(), 0));
					}
					else if (player->GetDir() == DIRECTION::LEFT)
					{
						SetPos(player->GetPosition() + Vector3(-35 * player->GetSize(), 16 * player->GetSize(), 0));
					}
					break;
				default:
					break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHATK)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(0, 0 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-40 * player->GetSize(), 0 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHKNIFEATK)
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPosition() + Vector3(-12 * player->GetSize(), 0 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPosition() + Vector3(-16.5f * player->GetSize(), 0 * player->GetSize(), 0));
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMPATK)
		{
			switch (player->GetLowerState())
			{
			case SOLDIERSTATE::JUMP:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(-6 * player->GetSize(), -20 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-8 * player->GetSize(), -20 * player->GetSize(), 0));
				}
				break;
			case SOLDIERSTATE::JUMPMOVE:
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPosition() + Vector3(0 * player->GetSize(), -26 * player->GetSize(), 0));
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPosition() + Vector3(-4 * player->GetSize(), -26 * player->GetSize(), 0));
				}
				break;
			default:
				break;
			}
		}
		else if (player->GetUpperState() == SOLDIERSTATE::CROUCHJUMPATKSTART)
		{
			switch (player->GetLowerState())
			{
				case SOLDIERSTATE::JUMP:
					if (player->GetDir() == DIRECTION::RIGHT)
					{
						SetPos(player->GetPosition() + Vector3(-2 * player->GetSize(), -12 * player->GetSize(), 0));
					}
					else if (player->GetDir() == DIRECTION::LEFT)
					{
						SetPos(player->GetPosition() + Vector3(-32 * player->GetSize(), -12 * player->GetSize(), 0));
					}
					break;
				case SOLDIERSTATE::JUMPMOVE:
					if (player->GetDir() == DIRECTION::RIGHT)
					{
						SetPos(player->GetPosition() + Vector3(8 * player->GetSize(), -15 * player->GetSize(), 0));
					}
					else if (player->GetDir() == DIRECTION::LEFT)
					{
						SetPos(player->GetPosition() + Vector3(-30 * player->GetSize(), -15 * player->GetSize(), 0));
					}
					break;
				default:
					break;
			}
		}
	}
}

void SoldierUpper::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	//idle
	texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
	animClips.push_back(new AnimationClip(L"RIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Idle/LUpper.png");
	animClips.push_back(new AnimationClip(L"LIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//idle machine Gun
	texture = new Texture2D(L"./_Textures/Character/Idle/RUpperMachine.png");
	animClips.push_back(new AnimationClip(L"RMachineIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Idle/LUpperMachine.png");
	animClips.push_back(new AnimationClip(L"LMachineIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//atk
	texture = new Texture2D(L"./_Textures/Character/Fire/RFire.png");
	animClips.push_back(new AnimationClip(L"RFire", texture, 10, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LFire.png");
	animClips.push_back(new AnimationClip(L"LFire", texture, 10, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RFireCrouch.png");
	animClips.push_back(new AnimationClip(L"RFireCrouch", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LFireCrouch.png");
	animClips.push_back(new AnimationClip(L"LFireCrouch", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RFireCrouchJump.png");
	animClips.push_back(new AnimationClip(L"RFireCrouchJump", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LFireCrouchJump.png");
	animClips.push_back(new AnimationClip(L"LFireCrouchJump", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RFireUpside.png");
	animClips.push_back(new AnimationClip(L"RFireUpside", texture, 10, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LFireUpside.png");
	animClips.push_back(new AnimationClip(L"LFireUpside", texture, 10, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RKnife.png");
	animClips.push_back(new AnimationClip(L"RKnife", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LKnife.png");
	animClips.push_back(new AnimationClip(L"LKnife", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RKnifeCrouch.png");
	animClips.push_back(new AnimationClip(L"RKnifeCrouch", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LKnifeCrouch.png");
	animClips.push_back(new AnimationClip(L"LKnifeCrouch", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//Machine Gun atk
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFire.png");
	animClips.push_back(new AnimationClip(L"RMachineFire", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFire.png");
	animClips.push_back(new AnimationClip(L"LMachineFire", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireUpside.png");
	animClips.push_back(new AnimationClip(L"RMachineFireUpside", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireUpside.png");
	animClips.push_back(new AnimationClip(L"LMachineFireUpside", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireUpsideStart.png");
	animClips.push_back(new AnimationClip(L"RMachineFireUpsideStart", texture, 3, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireUpsideStart.png");
	animClips.push_back(new AnimationClip(L"LMachineFireUpsideStart", texture, 3, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouch.png");
	animClips.push_back(new AnimationClip(L"RMachineFireCrouch", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouch.png");
	animClips.push_back(new AnimationClip(L"LMachineFireCrouch", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouchJumpStart.png");
	animClips.push_back(new AnimationClip(L"RMachineFireCrouchJumpStart", texture, 3, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouchJumpStart.png");
	animClips.push_back(new AnimationClip(L"LMachineFireCrouchJumpStart", texture, 3, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineFireCrouchJump.png");
	animClips.push_back(new AnimationClip(L"RMachineFireCrouchJump", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineFireCrouchJump.png");
	animClips.push_back(new AnimationClip(L"LMachineFireCrouchJump", texture, 4, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineKnife.png");
	animClips.push_back(new AnimationClip(L"RMachineKnife", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineKnife.png");
	animClips.push_back(new AnimationClip(L"LMachineKnife", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Fire/RMachineKnifeCrouch.png");
	animClips.push_back(new AnimationClip(L"RMachineKnifeCrouch", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Fire/LMachineKnifeCrouch.png");
	animClips.push_back(new AnimationClip(L"LMachineKnifeCrouch", texture, 6, { 0,0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//crouch
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchIdle.png");
	animClips.push_back(new AnimationClip(L"RCrouchIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchIdle.png");
	animClips.push_back(new AnimationClip(L"LCrouchIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMove.png");
	animClips.push_back(new AnimationClip(L"RCrouchMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMove.png");
	animClips.push_back(new AnimationClip(L"LCrouchMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//Machine Gun crouch
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMachineIdle.png");
	animClips.push_back(new AnimationClip(L"RCrouchMachineIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMachineIdle.png");
	animClips.push_back(new AnimationClip(L"LCrouchMachineIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMachineMove.png");
	animClips.push_back(new AnimationClip(L"RCrouchMachineMove", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMachineMove.png");
	animClips.push_back(new AnimationClip(L"LCrouchMachineMove", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//Jump
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandUpper.png");
	animClips.push_back(new AnimationClip(L"LJumpHandUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight()},true));//Jumpstatic
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandUpper.png");
	animClips.push_back(new AnimationClip(L"RJumpHandUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight()}));

	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandRunUpper.png");
	animClips.push_back(new AnimationClip(L"LJumpHandRunUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight()},true));//Jumpmove
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandRunUpper.png");
	animClips.push_back(new AnimationClip(L"RJumpHandRunUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpHandUpper.png");						
	animClips.push_back(new AnimationClip(L"LCrouchJumpHandUpper", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));//crouchjump
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpHandUpper.png");
	animClips.push_back(new AnimationClip(L"RCrouchJumpHandUpper", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	//Machine Gun Jump
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpMachineUpper.png");
	animClips.push_back(new AnimationClip(L"LJumpMachineUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));//Jumpstatic
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpMachineUpper.png");
	animClips.push_back(new AnimationClip(L"RJumpMachineUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpMachineRunUpper.png");
	animClips.push_back(new AnimationClip(L"LJumpMachineRunUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));//Jumpmove
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpMachineRunUpper.png");
	animClips.push_back(new AnimationClip(L"RJumpMachineRunUpper", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpMachineUpper.png");
	animClips.push_back(new AnimationClip(L"LCrouchJumpMachineUpper", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));//crouchjump
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpMachineUpper.png");
	animClips.push_back(new AnimationClip(L"RCrouchJumpMachineUpper", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));

	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpMachineUpperStart.png");
	animClips.push_back(new AnimationClip(L"LCrouchJumpMachineUpperStart", texture, 2, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));//crouchjumpstart
	texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpMachineUpperStart.png");
	animClips.push_back(new AnimationClip(L"RCrouchJumpMachineUpperStart", texture, 2, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	//handUp
	texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideUpper.png");
	animClips.push_back(new AnimationClip(L"LUpsideUpper", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideUpper.png");
	animClips.push_back(new AnimationClip(L"RUpsideUpper", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	//Machine Gun handUp
	texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideMachineUpper.png");
	animClips.push_back(new AnimationClip(L"LUpsideMachineUpper", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideMachineUpper.png");
	animClips.push_back(new AnimationClip(L"RUpsideMachineUpper", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideMachineUpperStart.png");
	animClips.push_back(new AnimationClip(L"LUpsideMachineUpperStart", texture, 2, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));
	texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideMachineUpperStart.png");
	animClips.push_back(new AnimationClip(L"RUpsideMachineUpperStart", texture, 2, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	
	animator = new Animator(animClips);
}

void SoldierUpper::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}

void SoldierUpper::SetPos(Vector3 tempPos)
{
	this->position = tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}
