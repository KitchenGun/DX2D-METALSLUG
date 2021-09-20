#include "stdafx.h"
#include "Building.h"
#include "Utilities/Animator.h"

Building::Building(Vector3 position, Vector3 size, float rotation, int BuildIndex)
:Object(position, size, rotation, ObjectType::BUILDING,true)
{
	this->BuildIndex = BuildIndex;
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
	texture = new Texture2D//(L"./_Textures/TestBox.png");
	(L"./_Textures/Object/Building/Building1.png");
	animator->SetCurrentAnimClip(L"Building1");
	animator->bLoop = true;
	TransformVertices();
}

Building::~Building()
{
	Object::~Object();
}

void Building::Update()
{
	HPCheck();
	Object::Update();
}

void Building::HPCheck()
{
	switch (BuildIndex)
	{
	case 1:
		if (ObjHP > 90)
		{
			texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
			animator->SetCurrentAnimClip(L"Building1");
		}
		else if (ObjHP > 70)
		{
			texture = new Texture2D(L"./_Textures/Object/Building/Building1.png");
			animator->SetCurrentAnimClip(L"Building1");
		}
		else if (ObjHP > 50)
		{
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-2.png");
			animator->SetCurrentAnimClip(L"Building2");
		}
		else if (ObjHP > 30)
		{
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-3.png");
			animator->SetCurrentAnimClip(L"Building3");
		}
		else if (ObjHP > 0)
		{
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-4.png");
			animator->SetCurrentAnimClip(L"Building4");
		}
		else
		{
			IsNeedDestroy = true;
		}
		break;
	default:
		break;
	}
}


