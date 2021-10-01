#include "stdafx.h"
#include "Blade.h"
#include "Helicopter.h"
#include "Utilities/Animator.h"

Helicopter::Helicopter(Vector3 position, Vector3 size, float altitude)
	:Enemy(position,size,0,ENEMYTYPE::Helicopter)
{
	HeliState = HELISTATE::RIGHTMOVE; 
	EnemyHP = 75;
	blade = new Blade(position, Vector3(80 * 3, 20 * 3, 0), 0,this);
	SetClip();
	animator->bLoop = false;
	animator->SetCurrentAnimClip(L"LMove");
	TransformVertices();
}

Helicopter::~Helicopter()
{
	SAFE_DELETE(blade);
	Enemy::~Enemy();
}

void Helicopter::Update()
{
	blade->Update();
	Enemy::Update();
}

void Helicopter::Render()
{
	Enemy::Render();
	blade->Render();
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
