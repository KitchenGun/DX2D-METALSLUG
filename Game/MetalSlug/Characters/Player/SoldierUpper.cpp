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
	if (upperState == UPPERSTATE::JUMPRUN)
	{
		SetPos(player->GetPos() + Vector3(0, 5 * player->GetSize(), 0));
	}
	else if (upperState == UPPERSTATE::LJUMP)
	{
		SetPos(player->GetPos() + Vector3(-5 * player->GetSize(), 20 * player->GetSize(), 0));
	}
	else if (upperState == UPPERSTATE::RJUMP)
	{
		SetPos(player->GetPos() + Vector3(-8 * player->GetSize(), 20 * player->GetSize(), 0));
	}
	else if (upperState == UPPERSTATE::HandUp)
	{
		switch (lowerAnimRect->GetlowerState())
		{
		case LOWERSTATE::IDLE:
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPos() + Vector3(-2 * player->GetSize(), 14 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPos() + Vector3(-8 * player->GetSize(), 14 * player->GetSize(), 0));
			}
			break;
		}
		case LOWERSTATE::MOVE:
		{
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPos() + Vector3(-2 * player->GetSize(), 16 * player->GetSize(), 0));
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPos() + Vector3(-10 * player->GetSize(), 16 * player->GetSize(), 0));
			}
			break;
		}
		default:
			break;
		}
	}
}

void SoldierUpper::Render()
{
	PlayerAnimationRect::Render();

}


void SoldierUpper::SetClip(string name)
{
	if (name == "Idle")
	{
		upperState=UPPERSTATE::IDLE;
		SetSize(Vector3(30 * player->GetSize(), 30 * player->GetSize(), 1));
		animator->bLoop = true;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			SetPos(player->GetPos() + Vector3(0, 8 * player->GetSize(), 0));
			texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
			name = "RIdle";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			SetPos(player->GetPos() + Vector3(-10 * player->GetSize(), 8 * player->GetSize(), 0));
			texture = new Texture2D(L"./_Textures/Character/Idle/LUpper.png");
			name = "LIdle";
		}
	}
	if (name == "CrouchIdle")
	{
		upperState = UPPERSTATE::CROUCH;
		animator->bLoop = true;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			SetSize(Vector3(34 * player->GetSize(), 24 * player->GetSize(), 1));
			SetPos(player->GetPos());
			animator->bLoop = true;
			texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchIdle.png");
			name == "RCrouchIdle";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			SetSize(Vector3(34 * player->GetSize(), 24 * player->GetSize(), 1));
			SetPos(player->GetPos()+Vector3(-12*player->GetSize(),0,0));
			animator->bLoop = true;
			texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchIdle.png");
			name == "LCrouchIdle";
		}
	}
	if (name == "RCrouchMove")
	{
		upperState = UPPERSTATE::CROUCH;
		SetSize(Vector3(37 * player->GetSize(), 24 * player->GetSize(), 1));
		SetPos(player->GetPos());
		animator->bLoop = true;
		texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMove.png");
	}
	if (name == "LCrouchMove")
	{
		upperState = UPPERSTATE::CROUCH;
		SetSize(Vector3(37 * player->GetSize(), 24 * player->GetSize(), 1));
		SetPos(player->GetPos() + Vector3(-15 * player->GetSize(), 0, 0));
		animator->bLoop = true;
		texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchMove.png");
	}
	if (name == "Upside")
	{
		upperState = UPPERSTATE::HandUp;
		SetSize(Vector3(30 * player->GetSize(), 27 * player->GetSize(), 1)); 
		animator->bLoop = true;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			SetPos(player->GetPos() + Vector3(-2*player->GetSize(), 14 * player->GetSize(), 0));
			texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideUpper.png");
			name = "RUpsideUpper";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			SetPos(player->GetPos() + Vector3(-8 * player->GetSize(), 14 * player->GetSize(), 0));
			texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideUpper.png");
			name = "LUpsideUpper";
		}
	}
	else if (name == "Jump")
	{
		
		if (player->GetisCrouch())
		{
			SetSize(Vector3(20 * player->GetSize(), 35 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				SetPos(player->GetPos() + Vector3(0, 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RCrouchJumpHandUpper.png");
				name = "RCrouchJumpHandUpper";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				SetPos(player->GetPos() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
				texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LCrouchJumpHandUpper.png");
				name = "LCrouchJumpHandUpper";
			}
		}
		else
		{
			if (player->GetisMove())
			{
				upperState = UPPERSTATE::JUMPRUN;
				SetSize(Vector3(29 * player->GetSize(), 35 * player->GetSize(), 1));
				animator->bLoop = false;
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					SetPos(player->GetPos() + Vector3(0, 5 * player->GetSize(), 0));
					texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandRunUpper.png");
					name = "RJumpHandRunUpper";
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					SetPos(player->GetPos() + Vector3(0 * player->GetSize(), 5 * player->GetSize(), 0));
					texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandRunUpper.png");
					name = "LJumpHandRunUpper";
				}
			}
			else
			{
				SetSize(Vector3(33 * player->GetSize(), 26 * player->GetSize(), 1));
				animator->bLoop = false;
				if (player->GetDir() == DIRECTION::RIGHT)
				{
					upperState = UPPERSTATE::RJUMP;
					SetPos(player->GetPos() + Vector3(-8 * player->GetSize(), 20 * player->GetSize(), 0));
					texture = new Texture2D(L"./_Textures/Character/Jump/Upper/RJumpHandUpper.png");
					name = "RJumpHandUpper";
				}
				else if (player->GetDir() == DIRECTION::LEFT)
				{
					upperState = UPPERSTATE::LJUMP;
					SetPos(player->GetPos() + Vector3(-5 * player->GetSize(), 20 * player->GetSize(), 0));
					texture = new Texture2D(L"./_Textures/Character/Jump/Upper/LJumpHandUpper.png");
					name = "LJumpHandUpper";
				}
			}
		}
	}
	animator->SetCurrentAnimClip(String::ToWString(name));
}

void SoldierUpper::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	//idle
	texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
	animClips.push_back(new AnimationClip(L"RIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Idle/LUpper.png");
	animClips.push_back(new AnimationClip(L"LIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//crouch
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchIdle.png");
	animClips.push_back(new AnimationClip(L"RCrouchIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchIdle.png");
	animClips.push_back(new AnimationClip(L"LCrouchIdle", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/RCrouchMove.png");
	animClips.push_back(new AnimationClip(L"RCrouchMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Crouch/LCrouchIdle.png");
	animClips.push_back(new AnimationClip(L"LCrouchMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
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
	//handUp
	texture = new Texture2D(L"./_Textures/Character/Upside/LUpsideUpper.png");
	animClips.push_back(new AnimationClip(L"LUpsideUpper", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));//crouchjump
	texture = new Texture2D(L"./_Textures/Character/Upside/RUpsideUpper.png");
	animClips.push_back(new AnimationClip(L"RUpsideUpper", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
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
