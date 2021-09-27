#include "stdafx.h"
#include "BossCannon.h"
#include "Utilities/Animator.h"

BossCannon::BossCannon(Vector3 Position, Vector3 Size,Boss* boss)
	:PlayerAnimationRect(Position+Vector3(180,-250,0),Size,0)
{
	this->boss = boss;
	SetClip();
	animator->bLoop = true; 
	texture = new Texture2D(L"./_Textures/Boss/CannonIdle.png");
	animator->SetCurrentAnimClip(L"CannonIdle");
	SetAnimation();
}

BossCannon::~BossCannon()
{
	SAFE_DELETE(boss);
	PlayerAnimationRect::~PlayerAnimationRect();
}

void BossCannon::Update()
{
	SetAnimation();
	PivotUpdate();
	PlayerAnimationRect::Update();
}

void BossCannon::Render()
{
	PlayerAnimationRect::Render();
}

void BossCannon::SetClip()
{
	//IDLE
	texture = new Texture2D(L"./_Textures/Boss/CannonIdle.png");
	animClips.push_back(new AnimationClip(L"CannonIdle", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	//ModChange
	texture = new Texture2D(L"./_Textures/Boss/CannonHighModChange.png");
	animClips.push_back(new AnimationClip(L"LaserToCannon", texture, 9, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() },true));
	texture = new Texture2D(L"./_Textures/Boss/CannonHighModChange.png");
	animClips.push_back(new AnimationClip(L"CannonToLaser", texture, 9, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	//Fire
	texture = new Texture2D(L"./_Textures/Boss/CannonHighLaserCharge.png");
	animClips.push_back(new AnimationClip(L"CannonHighLaserCharge", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Boss/CannonHighLaserFire.png");
	animClips.push_back(new AnimationClip(L"CannonHighLaserFire", texture, 10, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Boss/CannonHighArtyFire.png");
	animClips.push_back(new AnimationClip(L"CannonHighArtyFire", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	//die
	texture = new Texture2D(L"./_Textures/Boss/CannonDie.png");
	animClips.push_back(new AnimationClip(L"CannonDie", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->playRate = 1.0f / 8;
}

void BossCannon::SetAnimation()
{
	switch (boss->GetBossState())
	{
	case BOSSSTATE::IDLE:
		SetSize(Vector3(53 * 3, 79 * 3, 1));
		texture = new Texture2D(L"./_Textures/Boss/CannonIdle.png");
		animator->SetCurrentAnimClip(L"CannonIdle");
		break;
	case BOSSSTATE::LASERTOARTY:
		animator->playRate = 1.0f / 8;
		animator->bLoop = false;
		SetSize(Vector3(53 * 3, 79 * 3, 1));
		texture = new Texture2D(L"./_Textures/Boss/CannonHighModChange.png");
		animator->SetCurrentAnimClip(L"CannonToLaser");
		break;
	case BOSSSTATE::ARTYTOLASER:
		SetSize(Vector3(53 * 3, 79 * 3, 1));
		texture = new Texture2D(L"./_Textures/Boss/CannonHighModChange.png");
		animator->SetCurrentAnimClip(L"LaserToCannon");
		break; 
	case BOSSSTATE::LASERCHARGE:
		SetSize(Vector3(75 * 3, 79 * 3, 1));
		animator->playRate = 1.0f / 1;
		animator->bLoop = true;
		cout << "LASERCHARGE" << endl;
		texture = new Texture2D(L"./_Textures/Boss/CannonHighLaserCharge.png");
		animator->SetCurrentAnimClip(L"CannonHighLaserCharge");
		break;
	case BOSSSTATE::LASER:
		SetSize(Vector3(76 * 3, 46 * 3, 1));
		animator->bLoop = false;
		animator->playRate = 1.0f / 3;
		texture = new Texture2D(L"./_Textures/Boss/CannonHighLaserFire.png");
		animator->SetCurrentAnimClip(L"CannonHighLaserFire");
		break;
	case BOSSSTATE::ARTY:
		SetSize(Vector3(53 * 3, 79 * 3, 1));
		texture = new Texture2D(L"./_Textures/Boss/CannonHighArtyFire.png");
		animator->SetCurrentAnimClip(L"CannonHighArtyFire");
		break;
	case BOSSSTATE::DIE:
		SetSize(Vector3(53 * 3, 79 * 3, 1));
		texture = new Texture2D(L"./_Textures/Boss/CannonDie.png");
		animator->SetCurrentAnimClip(L"CannonDie");
		break;
	default:
		break;
	}
}

void BossCannon::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void BossCannon::SetPos(Vector3 tempPos)
{
	D3DXMatrixTranslation(&T, tempPos.x, tempPos.y, tempPos.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void BossCannon::PivotUpdate()
{
	switch (boss->GetBossState())
	{
	case BOSSSTATE::IDLE:
		SetPos(position);
		break;
	case BOSSSTATE::LASERTOARTY:
		SetPos(position + Vector3(0, 20*3, 0));
		break;
	case BOSSSTATE::ARTYTOLASER:
		SetPos(position + Vector3(0, 20 * 3, 0));
		break;
	case BOSSSTATE::LASER:
		SetPos(position-Vector3(70, -30 * 3, 0));
		break;
	case BOSSSTATE::LASERCHARGE:
		SetPos(position + Vector3(-70, -5 * 3, 0));
		break;
	case BOSSSTATE::ARTY:
		SetPos(position + Vector3(0, 20 * 3, 0));
		break;
	case BOSSSTATE::DIE:
	{
		SetPos(position + Vector3(0, 0 * 3, 0));
	}
	default:
		break;
	}
}
