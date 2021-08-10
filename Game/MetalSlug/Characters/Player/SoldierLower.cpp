#include "stdafx.h"
#include "SoldierLower.h"
#include "Utilities/Animator.h"

SoldierLower::SoldierLower(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
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
}

void SoldierLower::Render()
{
	if (!player->GetisCrouch())
	{
		PlayerAnimationRect::Render();
	}
}

void SoldierLower::SetClip(string name)
{
	if (name == "Idle")
	{
		SetSize(Vector3(21 * player->GetSize(), 16 * player->GetSize(), 1));
		SetPos(player->GetPos());
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
	else if (name == "RMove")
	{
		SetSize(Vector3(26 * player->GetSize(), 20 * player->GetSize(), 1));
		SetPos(player->GetPos() + Vector3(-4 * player->GetSize(), 0, 0));
		texture = new Texture2D(L"./_Textures/Character/Move/RMove.png");
	}
	else if (name == "LMove")
	{
		SetSize(Vector3(26 * player->GetSize(), 20 * player->GetSize(), 1));
		SetPos(player->GetPos() + Vector3(-4 * player->GetSize(), 0, 0));
		texture = new Texture2D(L"./_Textures/Character/Move/LMove.png");
	}
	animator->SetCurrentAnimClip(String::ToWString(name));
}

void SoldierLower::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	texture = new Texture2D(L"./_Textures/Character/Idle/RLower.png");
	//idle
	animClips.push_back(new AnimationClip(L"RIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight()}, true));
	//move
	animClips.push_back(new AnimationClip(L"RMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animClips.push_back(new AnimationClip(L"LMove", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
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
