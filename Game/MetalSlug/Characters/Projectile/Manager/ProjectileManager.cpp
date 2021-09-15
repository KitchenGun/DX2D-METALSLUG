#include"stdafx.h"
#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(bool isPM)
	:bIsPM(isPM)
{
}

ProjectileManager::~ProjectileManager()
{
	SAFE_DELETE(EM);
	for (Projectile* tempProjectile : projectileList)
	{
		SAFE_DELETE(tempProjectile);
	}
}

void ProjectileManager::Update()
{
	for (Projectile* tempProjectile : projectileList)
	{
		if (tempProjectile != nullptr)
		{
			tempProjectile->Update();
			if (Math::Distance(tempProjectile->GetStartPos(), tempProjectile->GetPosition()) > 1500.0f)//���� �Ÿ� �̻��� ��� ����
			{
				RemoveProjectile(tempProjectile);
				break;//������ ������Ʈ ����Ʈ�� ����Ǽ� break�ɰ� �ٽ� ��������
			}
			if (tempProjectile->GetIsNeedDestroy())
			{
				RemoveProjectile(tempProjectile);
				break;//������ ������Ʈ ����Ʈ�� ����Ǽ� break�ɰ� �ٽ� ��������
			}
		}
	}
}

void ProjectileManager::Render()
{
	for (Projectile* tempProjectile : projectileList)
	{
		if (tempProjectile != nullptr)
		{
			tempProjectile->Render();
		}
	}
}


void ProjectileManager::AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	Bullet* tempBullet=nullptr;
	if (bIsPM)
	{
		tempBullet	= new Bullet(position, size, rotation, dir, BT);
		tempBullet->SetEM(EM);
	}
	else
	{
		tempBullet = new Bullet(position, size, rotation, dir, BT,false);
		tempBullet->SetPM(PM);
	}
	projectileList.push_back(tempBullet);
}

void ProjectileManager::AddGrenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT)
{
	Grenade* tempGrenade = nullptr;
	if (bIsPM)
	{
		tempGrenade = new Grenade(position, size, rotation, dir, BT);
		tempGrenade->SetGroundList(GroundList);
		tempGrenade->SetEM(EM);
	}
	else
	{
		tempGrenade = new Grenade(position, size, rotation, dir, BT, false);
		tempGrenade->SetGroundList(GroundList);
		tempGrenade->SetPM(PM);
	}
	projectileList.push_back(tempGrenade);
}


void ProjectileManager::RemoveProjectile(Projectile* Target)
{
	for (iter=projectileList.begin();iter!=projectileList.end();++iter)
	{
		if (*iter == Target)
		{
			iter=projectileList.erase(iter);
			break;
		}
	}
}
