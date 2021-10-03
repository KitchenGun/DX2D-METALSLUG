#include "stdafx.h"
#include "Blade.h"
#include "Helicopter.h"
#include "Utilities/Animator.h"

Helicopter::Helicopter(Vector3 position, Vector3 size, float altitude)
	:Enemy(position,size,0,ENEMYTYPE::Helicopter),
	Altitude(altitude)
{
	HeliState = HELISTATE::RIGHTMOVE; 
	EnemyHP = 75;
	blade = new Blade(position, Vector3(80 * 3, 20 * 3, 0), 0,this);
	SetClip();
	animator->bLoop = false;
	animator->SetCurrentAnimClip(L"RFlyF");
	TransformVertices();
}

Helicopter::~Helicopter()
{
	SAFE_DELETE(blade);
	Enemy::~Enemy();
}

void Helicopter::Update()
{
	if (!isAtk)
	{
		DropBomb();
	}
	else
	{
		AddBomb();
	}
	PlayerPosTracking();
	AltitudeHold();
	blade->Update();
	Enemy::Update();
}

void Helicopter::Render()
{
	Enemy::Render();
	blade->Render();
}

void Helicopter::DropBomb()
{
	static float DeltaTime = 0;
	if (DeltaTime > AtkRate)
	{
		DeltaTime = 0;
		isAtk = true;
	}
	else
		DeltaTime += Time::Delta();
}

void Helicopter::AddBomb()
{
	static int DropCount = 0;
	static float DeltaTime = 0;
	if (DeltaTime > DropRate)
	{
		DeltaTime = 0;
		DropCount++;
		epm->AddHeliBomb(this->r.Point+Vector3(0,-80,0), Vector3(14 * 3, 26 * 3, 1));
	}
	else
		DeltaTime += Time::Delta();
	if (DropCount == 3)
	{
		DropCount = 0;
		isAtk = false;
	}
}

void Helicopter::AltitudeHold()
{
	if (this->position.y - pm->GetPlayer()->GetPosition().y > Altitude)
	{
		this->position += Vector3(0, -75, 0) * Time::Delta();
		D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

		world = S * R * T;
		WB->SetWorld(world);

		RootPos = position + Vector3(size.x / 2, 0, 0);
		TransformVertices();
		isEngage = true;
	}
	else
	{
		isEngage = false;
	}
}

void Helicopter::PlayerPosTracking()
{
	Vector3 tempPos = Vector3(0, 0, 0);
	float thisXPos = this->r.Point.x;
	float playerXPos = pm->GetPlayer()->GetPointPos().x;

	if (thisXPos-10 > playerXPos)//player보다 앞에 있는 경우
	{
		HeliState = HELISTATE::LEFTMOVE;
		animator->SetCurrentAnimClip(L"RFlyB");
		tempPos = Vector3(-200, 0, 0);
		SetPos(tempPos);
	}
	else if (playerXPos>thisXPos+10)//player가 앞에 있는 경우
	{
		HeliState=HELISTATE::RIGHTMOVE;
		animator->SetCurrentAnimClip(L"RFlyF");
		tempPos = Vector3(200, 0, 0);
		SetPos(tempPos);
	}
}

void Helicopter::SetPos(Vector3 tempPos)
{
	this->position += tempPos * Time::Delta();
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);

	RootPos = position + Vector3(size.x / 2, 0, 0);
	TransformVertices();
}

void Helicopter::SetClip()
{
	//Move
	texture = //new Texture2D(L"./_Textures/TestBox.png");
	new Texture2D(L"./_Textures/EnemyHelicopter/LFly.png");
	animClips.push_back(new AnimationClip(L"LFlyF", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animClips.push_back(new AnimationClip(L"LFlyB", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));
	texture = //new Texture2D(L"./_Textures/TestBox.png");
	new Texture2D(L"./_Textures/EnemyHelicopter/RFly.png");
	animClips.push_back(new AnimationClip(L"RFlyF", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	animClips.push_back(new AnimationClip(L"RFlyB", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
}
