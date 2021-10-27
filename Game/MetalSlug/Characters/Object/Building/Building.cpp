#include "stdafx.h"
#include "Building.h"
#include "Utilities/Animator.h"

Building::Building(Vector3 position, Vector3 size, float rotation, int BuildIndex, bool isRender, TextureRect* Stage1Texture)
:Object(position, size, rotation, ObjectType::BUILDING, isRender)
{
	this->Stage1Texture = Stage1Texture;
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
			//보트랑 다리 
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-4.png");
			animClips.push_back(new AnimationClip(L"Building4", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
			break;
		default:
		break;
	}
	ObjHP = 100;
	ColliderSizeChange(COLLIDER::BIG);
	animator = new Animator(animClips);
	texture = new Texture2D//(L"./_Textures/TestBox.png");
	(L"./_Textures/Object/Building/Building1.png");
	switch (BuildIndex)
	{
	case 1:
		texture = new Texture2D//(L"./_Textures/TestBox.png");
		(L"./_Textures/Object/Building/Building1.png");
		animator->SetCurrentAnimClip(L"Building1");
		break;
	case 2:
		texture = new Texture2D(L"./_Textures/Object/Building/Building1-4.png");
		animator->SetCurrentAnimClip(L"Building4");
		break;
	default:
		break;
	}
	animator->bLoop = true;
	Stage1Texture->SetSRV(L"./_Textures/Map/MapObj6.png");
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



void Building::ColliderSizeChange(COLLIDER val)
{
	static Vector3 startpos;
	switch (val)
	{
	case COLLIDER::NONE:
		size = Vector3(0 * 4, 0 * 4, 1);
		break;
	case COLLIDER::SMALL:
		size = Vector3(59 * 4, 169 * 4, 1);
		position = startpos - Vector3(200*4, -30 * 4, 0);
		break;
	case COLLIDER::BIG://생성때 한번만 설정
		startpos = position;
		size = Vector3(150 * 4, 169 * 4, 1);
		break;
	default:
		break;
	}
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void Building::HPCheck()
{
	SB->SetHit(false);
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
			static bool isSmall = false;
			if (isSmall == false)
			{
				ColliderSizeChange(COLLIDER::SMALL);
				isSmall = true;
			}
			texture = new Texture2D(L"./_Textures/Object/Building/Building1-4.png");
			animator->SetCurrentAnimClip(L"Building4");
		}
		else
		{
			IsNeedDestroy = true;
		}
		break;
	case 2:
		if (ObjHP > 70)
		{
			Stage1Texture->SetSRV(L"./_Textures/Map/MapObj6.png");
		}
		else if (ObjHP > 40)
		{
			Stage1Texture->SetSRV(L"./_Textures/Map/MapObj6-1.png");
		}
		else if (ObjHP >= 0)
		{
			Stage1Texture->SetSRV(L"./_Textures/Map/MapObj6-2.png");
		}
		else
		{
			Stage1Texture->SetSRV(L"./_Textures/Map/MapObj6-3.png");
			IsNeedDestroy = true;
		}
		break;
	default:
		break;
	}
}




