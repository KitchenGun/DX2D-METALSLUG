#pragma once
#include "Utilities/RenderTexture.h"
#include "Utilities/SoundSystem.h"

#include "Geometry/Line.h"
#include "Geometry/Square.h"
#include "Geometry/Circle.h"
#include "Geometry/FilledCircle.h"
#include "Geometry/TextureRect.h"
#include "Geometry/AnimationRect.h"
#include "Geometry/PlayerAnimationRect.h"
#include "Geometry/Ground.h"

//�÷��̾�
#include "Characters/Player/SoldierLower.h"
#include "Characters/Player/SoldierUpper.h"
#include "Characters/Player/Player.h"
//��
#include "Characters/Enemy/Enemy.h"
#include "Characters/Enemy/Soldier/EnemySoldier.h"
#include "Characters/Enemy/Manager/EnemyManager.h"

//����ü
#include "Characters/Projectile/Projectile.h"
#include "Characters/Projectile/Bullet/Bullet.h"
#include "Characters/Projectile/Grenade/Grenade.h"

//object
#include "Characters/Object/Object.h"
#include "Characters/Object/Rock/Rock1.h"

//Manager
#include "Characters/Projectile/Manager/ProjectileManager.h"


class Scene
{//���� �����Լ��� �� �������̽� ����
public:
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};