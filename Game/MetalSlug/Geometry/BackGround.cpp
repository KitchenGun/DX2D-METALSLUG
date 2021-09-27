#include "stdafx.h"
#include "BackGround.h"
#include "Utilities/Animator.h"

BackGround::BackGround(Vector3 position, Vector3 size, float rotation, BGTYPE bgt)
	:AnimationRect(position, size, 0)
{
	this->bgt = bgt;
	SetClip();
	animator->bLoop = true;
}

BackGround::~BackGround()
{
	AnimationRect::~AnimationRect();
}

void BackGround::Update()
{
	AnimationRect::Update();
}

void BackGround::Render()
{
	AnimationRect::Render();
}

void BackGround::SetClip()
{
	switch (bgt)
	{
	case BGTYPE::NONE:
		break;
	case BGTYPE::STAGE1BOAT:
		texture = new Texture2D(L"./_Textures/Map/MapBackGround1.png");
		animClips.push_back(new AnimationClip(L"MapBackGround1", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATERFALL:
		texture = new Texture2D(L"./_Textures/Map/MapBackGround2.png");
		animClips.push_back(new AnimationClip(L"MapBackGround2", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;	
	case BGTYPE::STAGE1GROUNDWATERFALL1:
		texture = new Texture2D(L"./_Textures/Map/MapObj7.png");
		animClips.push_back(new AnimationClip(L"MapObj7", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1GROUNDWATERFALL2:
		texture = new Texture2D(L"./_Textures/Map/MapObj8.png");
		animClips.push_back(new AnimationClip(L"MapObj8", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER0UP:
		texture = new Texture2D(L"./_Textures/Map/Map1.png");
		animClips.push_back(new AnimationClip(L"Map1", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER0DOWN:
		texture = new Texture2D(L"./_Textures/Map/Map1-1.png");
		animClips.push_back(new AnimationClip(L"Map1-1", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER1UP:
		texture = new Texture2D(L"./_Textures/Map/Map2-1.png");
		animClips.push_back(new AnimationClip(L"Map2-1", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER1DOWN:
		texture = new Texture2D(L"./_Textures/Map/Map3.png");
		animClips.push_back(new AnimationClip(L"Map3", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER2UP:
		texture = new Texture2D(L"./_Textures/Map/Map2-1.png");
		animClips.push_back(new AnimationClip(L"Map2-1", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1WATER2DOWN:
		texture = new Texture2D(L"./_Textures/Map/Map3.png");
		animClips.push_back(new AnimationClip(L"Map3", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case BGTYPE::STAGE1BOSSBOTTOM:
		texture = new Texture2D(L"./_Textures/Map/BossBtu.png");
		animClips.push_back(new AnimationClip(L"BossBtu", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	default:
		break;
	}
	animator = new Animator(animClips);
}
