#include "stdafx.h"
#include "Blade.h"
#include "Utilities/Animator.h"

Blade::Blade(Vector3 position, Vector3 size, float rotation, Helicopter* heli)
	:AnimationRect(position, size, rotation),
	Heli(heli)
{
	SetClip();
	animator->bLoop = true;
	animator->SetCurrentAnimClip(L"Idle");
}

Blade::~Blade()
{
	SAFE_DELETE(Heli);
	AnimationRect::~AnimationRect();
}

void Blade::Update()
{
	switch (Heli->GetState())
	{
	case HELISTATE::RIGHTMOVE:
		SetPos(Vector3(160, 150, 0));
		break;
	default:
		break;
	}
	AnimationRect::Update();
}

void Blade::Render()
{
	AnimationRect::Render();
}

void Blade::SetClip()
{
	texture = new Texture2D(L"./_Textures/EnemyHelicopter/Blade.png");
	animClips.push_back(new AnimationClip(L"Idle", texture, 5, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
}

void Blade::SetSize(Vector3 tempSize)
{

}

void Blade::SetPos(Vector3 tempPos)
{
	Vector3 temp= position + tempPos;
	D3DXMatrixTranslation(&T, temp.x, temp.y,temp.z);
	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}
