#include "stdafx.h"
#include "Building.h"
#include "Utilities/Animator.h"

Building::Building(Vector3 position, Vector3 size, float rotation, int BuildIndex)
:Object(position, size, rotation, ObjectType::BUILDING,true)
{
	switch (BuildIndex)
	{
		case 0:
			texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
			animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case 1:
			texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
			animClips.push_back(new AnimationClip(L"Building1", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-2.png");
			animClips.push_back(new AnimationClip(L"Building2", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-3.png");
			animClips.push_back(new AnimationClip(L"Building3", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-4.png");
			animClips.push_back(new AnimationClip(L"Building4", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		case 2:
			texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
			animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		default:
		break;
	}
	ObjHP = 100;
	animator = new Animator(animClips);
	texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
	animator->SetCurrentAnimClip(L"Building1");
	animator->bLoop = true;
}

Building::~Building()
{
	Object::~Object();
}

void Building::Update()
{
	Object::Update();
}


