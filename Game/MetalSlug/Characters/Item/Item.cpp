#include "stdafx.h"
#include "Item.h"
#include "Utilities/Animator.h"

Item::Item(Vector3 position, Vector3 size, PROJECTILETYPE pt, PlayerManager* pm)
	:AnimationRect(position,size,0)
{
	this->pm = pm;
	this->pt = pt;
	
	switch (pt)
	{
	case PROJECTILETYPE::HEAVY:
		texture = new Texture2D(L"./_Textures/Object/Item/H.png");
		animClips.push_back(new AnimationClip(L"Idle", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	case PROJECTILETYPE::Grenade:
		texture = new Texture2D(L"./_Textures/Object/Item/B.png");
		animClips.push_back(new AnimationClip(L"Idle", texture, 6, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		break;
	default:
		break;
	}

	animator = new Animator(animClips);
	switch (pt)
	{
	case PROJECTILETYPE::HEAVY:
		texture = new Texture2D(L"./_Textures/Object/Item/H.png");
		break;
	case PROJECTILETYPE::Grenade:
		texture = new Texture2D(L"./_Textures/Object/Item/B.png");
		break;
	default:
		break;
	}
	animator->SetCurrentAnimClip(L"Idle");
}

Item::~Item()
{
	SAFE_DELETE(pm);
}

void Item::Update()
{
	if (Math::Intersect(pm->GetPlayer(), this))
	{
		Take();
	}
	AnimationRect::Update();
}

void Item::Render()
{
	if (!isTake)
	{
		AnimationRect::Render();
	}
}

void Item::Take()
{
	isTake = true;
	pm->GetPlayer()->ItemTake(pt);
}


