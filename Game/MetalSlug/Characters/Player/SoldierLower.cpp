#include "stdafx.h"
#include "SoldierLower.h"
#include "Utilities/Animator.h"

SoldierLower::SoldierLower(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
	texture = new Texture2D(L"./_Textures/Character/Idle/RLower.png");
	animator->SetCurrentAnimClip(L"RIdle");
	animator->bLoop=true;
}

SoldierLower::~SoldierLower()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void SoldierLower::Update()
{
	PlayerAnimationRect::Update();
	SetPos(player->GetPosition());
}

void SoldierLower::Render()
{
	if (player->GetLowerState()!=SOLDIERSTATE::NONE)
	{
		PlayerAnimationRect::Render();
	}
}


void SoldierLower::SetClip(string name)
{
	if (name == "Idle")
	{
		SetSize(Vector3(21 * player->GetSize(), 16 * player->GetSize(), 1));
		animator->bLoop = true;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/Character/Idle/RLower.png");
			name = "RIdle";
		}
		else if(player->GetDir() == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/Character/Idle/LLower.png");
			name = "LIdle";
		}
	}
	else if (name == "Move")
	{
		SetSize(Vector3(26 * player->GetSize(), 20 * player->GetSize(), 1));
		animator->bLoop = true;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/Character/Move/RMove.png");
			name = "RMove";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{

			animator->bLoop = true;
			texture = new Texture2D(L"./_Textures/Character/Move/LMove.png");
			name = "LMove";
		}
	}
	else if (name == "Jump")
	{
			SetSize(Vector3(21 * player->GetSize(), 24 * player->GetSize(), 1));
			animator->bLoop = false;
			if (player->GetDir() == DIRECTION::RIGHT)
			{
				texture = new Texture2D(L"./_Textures/Character/Jump/Lower/RJumpLower.png");
				name = "RJumpLower";
			}
			else if (player->GetDir() == DIRECTION::LEFT)
			{
				texture = new Texture2D(L"./_Textures/Character/Jump/Lower/LJumpLower.png");
				name = "LJumpLower";
			}
	}
	else if (name == "JumpMove")
	{
		SetSize(Vector3(33 * player->GetSize(), 21 * player->GetSize(), 1));
		animator->bLoop = false;
		if (player->GetDir() == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/Character/Jump/Lower/RJumpMoveLower.png");
			name = "RJumpMoveLower";
		}
		else if (player->GetDir() == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/Character/Jump/Lower/LJumpMoveLower.png");
			name = "LJumpMoveLower";
		}
	}
	animator->SetCurrentAnimClip(String::ToWString(name));
}

void SoldierLower::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	//idle
	texture = new Texture2D(L"./_Textures/Character/Idle/RLower.png");
	animClips.push_back(new AnimationClip(L"RIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Idle/LLower.png");
	animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight()}, true));
	//move
	texture = new Texture2D(L"./_Textures/Character/Move/RMove.png");
	animClips.push_back(new AnimationClip(L"RMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Character/Move/LMove.png");
	animClips.push_back(new AnimationClip(L"LMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	//Jump
	texture = new Texture2D(L"./_Textures/Character/Jump/Lower/LJumpLower.png");
	animClips.push_back(new AnimationClip(L"LJumpLower", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));//Jump
	texture = new Texture2D(L"./_Textures/Character/Jump/Lower/RJumpLower.png");
	animClips.push_back(new AnimationClip(L"RJumpLower", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));

	texture = new Texture2D(L"./_Textures/Character/Jump/Lower/LJumpMoveLower.png");
	animClips.push_back(new AnimationClip(L"LJumpMoveLower", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));//Jump
	texture = new Texture2D(L"./_Textures/Character/Jump/Lower/RJumpMoveLower.png");
	animClips.push_back(new AnimationClip(L"RJumpMoveLower", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
}

void SoldierLower::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S*R*T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}

void SoldierLower::SetPos(Vector3 tempPos)
{
	this->position = tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}
