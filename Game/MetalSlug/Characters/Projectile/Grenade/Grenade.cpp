#include "stdafx.h"
#include "Grenade.h"
#include "Utilities/Animator.h"

Grenade::Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE PT, bool bisPPM)
	:Projectile(position,size,0,dir,PT,bisPPM)
{
	if (pt == PROJECTILETYPE::Grenade)
	{
		Damage = 10;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/RGrenade.png");
		animClips.push_back(new AnimationClip(L"RGrenade", texture, 16, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		texture = new Texture2D(L"./_Textures/SFX/Weapon/LGrenade.png");
		animClips.push_back(new AnimationClip(L"LGrenade", texture, 16, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		texture = new Texture2D(L"./_Textures/SFX/Explosion/GrenadeExplosion.png");
		animClips.push_back(new AnimationClip(L"GrenadeExplosion", texture, 27, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	}
	else if (pt == PROJECTILETYPE::EnemyGrenade)
	{
		Damage = 1;
		texture = new Texture2D(L"./_Textures/SFX/Weapon/REnemyGrenade.png");
		animClips.push_back(new AnimationClip(L"REnemyGrenade", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		texture = new Texture2D(L"./_Textures/SFX/Weapon/LEnemyGrenade.png");
		animClips.push_back(new AnimationClip(L"LEnemyGrenade", texture, 8, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
		texture = new Texture2D(L"./_Textures/SFX/Explosion/GrenadeExplosion.png");
		animClips.push_back(new AnimationClip(L"GrenadeExplosion", texture, 27, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	}
	animator = new Animator(animClips);
	StartPos = position;
	if (pt == PROJECTILETYPE::Grenade)
	{
		if (Dir == DIRECTION::RIGHT)
		{
			Angle = (float)D3DXToRadian(45);
			texture = new Texture2D(L"./_Textures/SFX/Weapon/RGrenade.png");
			animator->SetCurrentAnimClip(L"RGrenade",false);
		}
		else if (Dir == DIRECTION::LEFT)
		{
			Angle = (float)D3DXToRadian(135);
			texture = new Texture2D(L"./_Textures/SFX/Weapon/LGrenade.png");
			animator->SetCurrentAnimClip(L"LGrenade", false);
		}
	}
	else if (pt == PROJECTILETYPE::EnemyGrenade)
	{
		if (Dir == DIRECTION::RIGHT)
		{
			Angle = (float)D3DXToRadian(45);
			texture = new Texture2D(L"./_Textures/SFX/Weapon/REnemyGrenade.png");
			animator->SetCurrentAnimClip(L"REnemyGrenade", false);
		}
		else if (Dir == DIRECTION::LEFT)
		{
			Angle = (float)D3DXToRadian(135);
			texture = new Texture2D(L"./_Textures/SFX/Weapon/LEnemyGrenade.png");
			animator->SetCurrentAnimClip(L"LEnemyGrenade", false);
		}
	}
}

Grenade::~Grenade()
{
	Projectile::~Projectile();
}

void Grenade::Update()
{
	if (pt == PROJECTILETYPE::Grenade)
	{
		if (!isHit)
		{
			ThrowingTime += Time::Delta();
			Move();
			if (GroundList.size() > 0)
			{
				if (ThrowingTime > 0.1f)
				{
					if (Math::GroundIntersect(this, GroundList))
					{
						GroundIntersectCount++;
						StartPos = position;
						Speed -= 60;
						ThrowingTime = 0;
						if (GroundIntersectCount == 2)
						{
							isHit = true;
							HitPos = this->position;
						}
					}
				}
			}
		}
		else
		{
			Explosion();
			if (!animator->isFirstPlay)
			{
				isNeedDestroy = true;
			}
		}
	}
	else if(pt == PROJECTILETYPE::EnemyGrenade)
	{
		if (!isHit)
		{
			ThrowingTime += Time::Delta();
			Move();
			if (GroundList.size() > 0)
			{
				if (ThrowingTime > 0.1f)
				{
					if (Math::GroundIntersect(this, GroundList))
					{
						GroundIntersectCount++;
						StartPos = position;
						Speed -= 60;
						ThrowingTime = 0;
						if (GroundIntersectCount == 2)
						{
							isHit = true;
							HitPos = this->position;
						}
					}
				}
			}
		}
		else
		{
			Explosion();
			if (!animator->isFirstPlay)
			{
				isNeedDestroy = true;
			}
		}
	}
	Projectile::Update();
}

void Grenade::Render()
{
	Projectile::Render();
}

void Grenade::Move()
{
	this->position = StartPos+
		Vector3((Speed * cosf(Angle) * ThrowingTime), ((Speed * sinf(Angle) * ThrowingTime) - (0.5f * Gravity * powf(ThrowingTime,2))), 0);
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void Grenade::Explosion()
{
	if (pt == PROJECTILETYPE::Grenade)
	{
		this->size = Vector3(50 * 3, 107 * 3, 1);
		D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);
		this->position = HitPos + Vector3(0, 47 * 3, 0);
		D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
		world = S * R * T;
		WB->SetWorld(world);
		TransformVertices();
		animator->bLoop = false;
		texture = new Texture2D(L"./_Textures/SFX/Explosion/GrenadeExplosion.png");
		animator->SetCurrentAnimClip(L"GrenadeExplosion", false);
	}
}
