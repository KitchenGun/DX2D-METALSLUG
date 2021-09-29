#include "stdafx.h"
#include "ItemBox.h"
#include "Utilities/Animator.h"

ItemBox::ItemBox(Vector3 position, Vector3 size, float rotation, bool isRender, PROJECTILETYPE pt, ItemManager* IM)
	:Object(position,size,rotation,ObjectType::BOX,isRender)
{
	PT = pt;
	this->IM = IM;
	BOXSTATE BState = BOXSTATE::IDLE;
	
	BAni = new BoxAnimation(position+Vector3(-30,10,0), Vector3(46 * 4, 49 * 4, 1), 0,this);
	texture = new Texture2D(L"./_Textures/Object/Item/Box/BoxIdle.png");
	animClips.push_back(new AnimationClip(L"BoxIdle", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/Object/Item/Eat.png");
	animClips.push_back(new AnimationClip(L"Eat", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	animator->bLoop = false;
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animator->SetCurrentAnimClip(L"BoxIdle");
	ObjHP = 1;
}

ItemBox::~ItemBox()
{
	SAFE_DELETE(IM);
	SAFE_DELETE(BAni);
	Object::~Object();
}

void ItemBox::Update()
{
	HPCheck();
	Object::Update();
	BAni->Update();
}

void ItemBox::Render()
{
	//Object::Render();
	BAni->Render();
}

void ItemBox::HPCheck()
{
	if (ObjHP <= 0)
	{
		if (isAddItem == false)
		{
			isDestroy();
		}
		isAddItem = true;
	}
}

void ItemBox::isDestroy()
{
	BState = BOXSTATE::DESTROY;
	ColliderSizeChange(COLLIDER::NONE);
	switch (PT)
	{
	case PROJECTILETYPE::HEAVY:
		IM->AddItem(position + Vector3(50, 70, 0), PROJECTILETYPE::HEAVY);
		break;
	case PROJECTILETYPE::Grenade:
		//CreateItem = new Item(position + Vector3(50, 70, 0), Vector3(32 * 4, 30 * 4, 1), PROJECTILETYPE::Grenade, target);
		break;
	default:
		break;
	}
}

void ItemBox::isEat()
{
	texture = new Texture2D(L"./_Textures/Object/Item/Eat.png");
	animator->SetCurrentAnimClip(L"Eat");
}

void ItemBox::ColliderSizeChange(COLLIDER val)
{
	static Vector3 startpos;
	switch (val)
	{
	case COLLIDER::NONE:
		size = Vector3(0 * 4, 0 * 4, 1);
		break;
	case COLLIDER::SMALL:
		size = Vector3(59 * 4, 169 * 4, 1);
		position = startpos - Vector3(200 * 4, -30 * 4, 0);
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
