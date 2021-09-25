#include "stdafx.h"
#include "Boss.h"
#include "Utilities/Animator.h"

Boss::Boss(Vector3 position, Vector3 size, float rotation)
	:Enemy(position + Vector3(300, -180, 0), Vector3(100, 300, 1),rotation,ENEMYTYPE::Boss)
{
	firePos.Pos = position + Vector3(180, 0, 0);
	BossState = BOSSSTATE::IDLE;
	BossBody = new TextureRect(position, size, 0);
	BossBody->SetSRV(L"./_Textures/Map/BossObj-0.png");
	bossCannon = new BossCannon(position, Vector3(53 * 3, 79 * 3, 0), this);
	EnemyHP = 400;
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"test", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);
	TransformVertices();
}

Boss::~Boss()
{
	SAFE_DELETE(bossCannon);
	SAFE_DELETE(BossBody);
	Enemy::~Enemy();
}

void Boss::Update()
{
	HPCheck();
	if (BossState != BOSSSTATE::DIE)
	{
		SetAni();
		if (nextState == BOSSSTATE::LASER)
		{
			if (isLaserATK)
			{
				LaserAtk();
			}
			else if (phase == 1)
			{
				isLaserATK = true;
			}
		}
		if (nextState == BOSSSTATE::ARTY)
		{
			static float DeltaTime = 0.0f;
			if (DeltaTime > 0.3f && fireCount < 3)
			{
				DeltaTime = 0;
				ArtyAtk(ArtyAngle()+fireCount*5);
				fireCount++;
			}
			else
			{
				DeltaTime += Time::Delta();
			}
		}
	}
	prevState = BossState;
	BossState = nextState;
	nextState = BOSSSTATE::NONE;
	Enemy::Update();
	bossCannon->Update();
}

void Boss::Render()
{
	BossBody->Render();
	//Enemy::Render();
	bossCannon->Render();
}

void Boss::SetAni()
{
	switch (BossState)
	{
	case BOSSSTATE::IDLE:
	{
		if (phase == -1)
		{
			nextState = BOSSSTATE::IDLE;
		}
		else if (phase == 0)
		{
			nextState = BOSSSTATE::LASERTOARTY;
		}
		break;
	}
	case BOSSSTATE::LASERTOARTY:
	{
		if (bossCannon->GetAnimator()->isFirstPlay)
		{
			nextState = BOSSSTATE::LASERTOARTY;
		}
		else
		{
			nextState = BOSSSTATE::ARTY;
		}
		break;
	}
	case BOSSSTATE::ARTY:
	{
		if (bossCannon->GetAnimator()->isFirstPlay)
		{
			nextState = BOSSSTATE::ARTY;
		}
		else
		{
			nextState = BOSSSTATE::ARTYTOLASER;
			isArtyATK = true;
			fireCount = 0;
		}
		break;
	}
	case BOSSSTATE::ARTYTOLASER:
	{
		if (bossCannon->GetAnimator()->isFirstPlay)
		{
			nextState = BOSSSTATE::ARTYTOLASER;
		}
		else
		{
			nextState = BOSSSTATE::LASERCHARGE;
		}
		break;
	}
	case BOSSSTATE::LASERCHARGE:
	{
		static float DeltaTime = 0;
		if (!isLaserATK && phase == 0)
		{
			nextState = BOSSSTATE::LASERTOARTY;
		}
		else if(DeltaTime>=3.0f)
		{
			DeltaTime = 0;
			nextState = BOSSSTATE::LASER;
		}
		else
		{
			nextState = BOSSSTATE::LASERCHARGE;
			DeltaTime += Time::Delta();
		}
		break;
	}
	case BOSSSTATE::LASER:
	{
		if (!isLaserATK&&phase==0)
		{
			nextState = BOSSSTATE::LASERTOARTY;
		}
		else if(!isLaserATK)
		{
			nextState = BOSSSTATE::LASERCHARGE;
		}
		else
		{
			nextState = BOSSSTATE::LASER;
		}
		break;
	}
	default:
		break;
	}
}

void Boss::LaserAtk()
{
	if (!bossCannon->GetAnimator()->isFirstPlay)
	{
		isLaserATK = false;
		nextState = BOSSSTATE::LASERTOARTY;
	}
}

void Boss::ArtyAtk(float Angle)
{
	cout << "throw" << endl;
	epm->AddArty(firePos.Pos, Vector3(10 * 4, 10 * 4, 0), Angle,PROJECTILETYPE::BOSSARTY);
}

int Boss::ArtyAngle()
{//근거리 90 135
	float fRange = Math::Distance(this->GetTransformedCoord().Point, ppm->GetPlayer()->GetTransformedCoord().Point);
	if (fRange > 900)
	{
		fRange = 1;
	}
	else if (fRange > 800)
	{
		fRange = 0.8f;
	}
	else if (fRange > 700)
	{
		fRange = 0.6f;
	}
	else if (fRange > 500)
	{
		fRange = 0.4f;
	}
	else if (fRange > 200)
	{
		fRange = 0.2f;
	}
	else
	{
		fRange = 0.0f;
	}
	return Math::Lerpf(90, 135, fRange);
}

void Boss::Die()
{
	BossState = BOSSSTATE::DIE;
	nextState = BOSSSTATE::DIE;
}

void Boss::HPCheck()
{
	if (ppm->GetPlayer() != nullptr)
	{
		if (Math::Distance(ppm->GetPlayer()->GetTransformedCoord().Point,this->GetTransformedCoord().Point)<800)
		{
			if (EnemyHP >= 100)
			{
				phase = 0;
			}
			else
			{
				phase = 1;
			}
		}
	}
	if (EnemyHP <= 100)
	{
		phase = 1;
	}

	if (EnemyHP >= 275)
	{
		BossBody->SetSRV(L"./_Textures/Map/BossObj-0.png");
	}
	else if (EnemyHP >= 150)
	{
		BossBody->SetSRV(L"./_Textures/Map/BossObj-1.png");
	}
	else if (EnemyHP >= 75)
	{
		BossBody->SetSRV(L"./_Textures/Map/BossObj-2.png");
	}
	else if (EnemyHP >= 0)
	{
		BossBody->SetSRV(L"./_Textures/Map/BossObj-3.png");
	}
	else if (EnemyHP <= 0)
	{
		BossBody->SetSRV(L"./_Textures/Map/BossObj-4.png");
	}

	if (EnemyHP <= 0)
	{
		Die();
	}
}

void Boss::Hit(DAMAGE val, Projectile* tempProjectile)
{
	cout <<"Enemy boss "<< EnemyHP << endl;
	Projectile* NowTemp;
	NowTemp = tempProjectile;

	bool TempSearchResult = false;

	for (Projectile* tempP : vecHitProjectile)
	{
		if (tempP == NowTemp)
		{
			TempSearchResult = true;
		}
	}
	//수류탄 중복 데미지 때문에 이렇게 처리
	if (TempSearchResult == false)
	{
		if (tempProjectile == nullptr)
		{
			EnemyHP -= val;
			return;
		}
		else if (NowTemp != PrevTemp)
		{
			EnemyHP -= val;
		}
		if (NowTemp->GetPT() == PROJECTILETYPE::Grenade)
		{
			PrevTemp = NowTemp;
			vecHitProjectile.push_back(PrevTemp);
		}
	}
}

void Boss::ColliderSizeChange(COLLIDER val)
{
}
