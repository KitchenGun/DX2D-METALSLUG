#include "stdafx.h"
#include "SoldierUpper.h"
#include "Utilities/Animator.h"

SoldierUpper::SoldierUpper(Vector3 position, Vector3 size, float rotation)
	:PlayerAnimationRect(position, size, rotation)
{
	SetAnimation();
	animator->SetCurrentAnimClip(L"Idle");
	animator->bLoop = true;
}

SoldierUpper::~SoldierUpper()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}

void SoldierUpper::Update()
{
	PlayerAnimationRect::Update();
}

void SoldierUpper::Render()
{
	PlayerAnimationRect::Render();
}

void SoldierUpper::SetClip(string name)
{
	if (name == "Idle")
	{
		SetSize(Vector3(30 * player->GetSize(), 30 * player->GetSize(), 1));
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
	animator->SetCurrentAnimClip(String::ToWString(name));
}

void SoldierUpper::SetAnimation()
{//텍스쳐 주소 입력하여서 텍스쳐 자원 제작
	texture = new Texture2D(L"./_Textures/Character/Idle/RUpper.png");
	//idle
	animClips.push_back(new AnimationClip(L"RIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
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
