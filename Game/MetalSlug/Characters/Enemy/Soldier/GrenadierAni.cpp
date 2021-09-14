#include "stdafx.h"
#include "GrenadierAni.h"
#include "Utilities/Animator.h"

GrenadierAni::GrenadierAni(Vector3 position, Vector3 size, float rotation,EnemySoldier* enemy)
	:PlayerAnimationRect(position,size,rotation)
{
	this->enemy = enemy;
	SetClip();
	animator->bLoop = true;
	animator->SetCurrentAnimClip(L"LIdle");
	SetAnimation();
}

GrenadierAni::~GrenadierAni()
{
	SAFE_DELETE(enemy);
	PlayerAnimationRect::~PlayerAnimationRect();
}

void GrenadierAni::Update()
{
	ValueUpdate();
	PivotUpdate();
	PlayerAnimationRect::Update();
}

void GrenadierAni::Render()
{
	if (enemy->GetState() != ENEMYSOLDIERSTATE::NONE)
	{
		PlayerAnimationRect::Render();
	}
}

void GrenadierAni::SetClip()
{
	//IDLE
	texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
	animClips.push_back(new AnimationClip(L"LIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/RIdle.png");
	animClips.push_back(new AnimationClip(L"RIdle", texture, 4, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//Surprise
	texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LSurprise.png");
	animClips.push_back(new AnimationClip(L"LSurprise", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/RSurprise.png");
	animClips.push_back(new AnimationClip(L"RSurprise", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//walk
	texture = new Texture2D(L"./_Textures/EnemySoldier/Move/LWalk.png");
	animClips.push_back(new AnimationClip(L"LWalk", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Move/RWalk.png");
	animClips.push_back(new AnimationClip(L"RWalk", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//run
	texture = new Texture2D(L"./_Textures/EnemySoldier/Move/LRun.png");
	animClips.push_back(new AnimationClip(L"LRun", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Move/RRun.png");
	animClips.push_back(new AnimationClip(L"RRun", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//Jump
	texture = new Texture2D(L"./_Textures/EnemySoldier/Jump/LJump.png");
	animClips.push_back(new AnimationClip(L"LJump", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Jump/RJump.png");
	animClips.push_back(new AnimationClip(L"RJump", texture, 7, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//ATK
	texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/LThrow.png");//¼ö·ùÅº ÅõÃ´
	animClips.push_back(new AnimationClip(L"LThrow", texture, 17, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/RThrow.png");
	animClips.push_back(new AnimationClip(L"RThrow", texture, 17, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/LKnife.png");//Ä® Á¦ÀÚ¸® °ø°Ý
	animClips.push_back(new AnimationClip(L"LKnife", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/RKnife.png");
	animClips.push_back(new AnimationClip(L"RKnife", texture, 12, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));

	//»ç¸Á
	texture = new Texture2D(L"./_Textures/EnemySoldier/Die/LDie.png");
	animClips.push_back(new AnimationClip(L"LDie", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	texture = new Texture2D(L"./_Textures/EnemySoldier/Die/RDie.png");
	animClips.push_back(new AnimationClip(L"RDie", texture, 11, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }, true));
	animator = new Animator(animClips);
}

void GrenadierAni::PivotUpdate()
{
	switch (enemy->GetState())
	{
	case ENEMYSOLDIERSTATE::IDLE:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::SURPRISE:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::WALK:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::RUN:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::JUMP:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::KNIFE:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::THROW:
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	case ENEMYSOLDIERSTATE::DIE:
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		else if (dir == DIRECTION::LEFT)
		{
			SetPos(position + Vector3(0 * IMGsize, 0 * IMGsize, 0));
		}
		break;
	default:
		break;
	}
}

void GrenadierAni::ValueUpdate()
{
	this->position = enemy->GetPosition();
	dir = enemy->GetDir();//dir
	SetAnimation();
}

void GrenadierAni::SetAnimation()
{
	switch (enemy->GetState())
	{
	case ENEMYSOLDIERSTATE::IDLE:
		SetSize(Vector3(27 * IMGsize, 44 * IMGsize, 1));
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
			animator->SetCurrentAnimClip(L"RIdle");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LIdle.png");
			animator->SetCurrentAnimClip(L"LIdle");
		}
		break;
	case ENEMYSOLDIERSTATE::SURPRISE:
		SetSize(Vector3(43 * IMGsize, 43 * IMGsize, 1));
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/RSurprise.png");
			animator->SetCurrentAnimClip(L"RSurprise");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Idle/LSurprise.png");
			animator->SetCurrentAnimClip(L"LSurprise");
		}
		break;
	case ENEMYSOLDIERSTATE::WALK:
		SetSize(Vector3(26 * IMGsize, 41 * IMGsize, 1));
		animator->bLoop = true;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Move/RWalk.png");
			animator->SetCurrentAnimClip(L"RWalk");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Move/LWalk.png");
			animator->SetCurrentAnimClip(L"LWalk");
		}
		break;
	case ENEMYSOLDIERSTATE::RUN:
		SetSize(Vector3(34 * IMGsize, 39 * IMGsize, 1));
		animator->bLoop = true;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Move/RRun.png");
			animator->SetCurrentAnimClip(L"RRun");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Move/LRun.png");
			animator->SetCurrentAnimClip(L"LRun");
		}
		break;
	case ENEMYSOLDIERSTATE::JUMP:
		SetSize(Vector3(30 * IMGsize, 44 * IMGsize, 1));
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Jump/RJump.png");
			animator->SetCurrentAnimClip(L"RJump");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Jump/LJump.png");
			animator->SetCurrentAnimClip(L"LJump");
		}
		break;
	case ENEMYSOLDIERSTATE::KNIFE:
		SetSize(Vector3(51 * IMGsize, 37 * IMGsize, 1));
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/RKnife.png");
			animator->SetCurrentAnimClip(L"RKnife");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/LKnife.png");
			animator->SetCurrentAnimClip(L"LKnife");
		}
		break;
	case ENEMYSOLDIERSTATE::THROW:
		SetSize(Vector3(43 * IMGsize, 42 * IMGsize, 1));
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/RThrow.png");
			animator->SetCurrentAnimClip(L"RThrow");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/ATK/LThrow.png");
			animator->SetCurrentAnimClip(L"LThrow");
		}
		break;
	case ENEMYSOLDIERSTATE::DIE:
		SetSize(Vector3(28 * IMGsize, 37 * IMGsize, 1));
		animator->bLoop = false;
		if (dir == DIRECTION::RIGHT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Die/RDie.png");
			animator->SetCurrentAnimClip(L"RDie");
		}
		else if (dir == DIRECTION::LEFT)
		{
			texture = new Texture2D(L"./_Textures/EnemySoldier/Die/LDie.png");
			animator->SetCurrentAnimClip(L"LDie");
		}
		break;
	default:
		break;
	}
}

void GrenadierAni::SetSize(Vector3 tempSize)
{
	this->size = tempSize;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void GrenadierAni::SetPos(Vector3 tempPos)
{
	this->position = tempPos;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}
