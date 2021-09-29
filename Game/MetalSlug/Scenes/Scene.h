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
#include "Geometry/BackGround.h"

//플레이어
#include "Characters/Player/SoldierLower.h"
#include "Characters/Player/SoldierUpper.h"
#include "Characters/Player/Player.h"
#include "Characters/Player/Manager/PlayerManager.h"

//적
#include "Characters/Enemy/Enemy.h"
#include "Characters/Enemy/Soldier/GrenadierAni.h"
#include "Characters/Enemy/Soldier/EnemySoldier.h"
#include "Characters/Enemy/Boss/BossCannon.h"
#include "Characters/Enemy/Boss/Boss.h"
#include "Characters/Enemy/Manager/EnemyManager.h"

//투사체
#include "Characters/Projectile/Projectile.h"
#include "Characters/Projectile/Bullet/Bullet.h"
#include "Characters/Projectile/Grenade/Grenade.h"

//object
#include "Characters/Object/Object.h"
#include "Characters/Object/Rock/Rock1.h"
#include "Characters/Object/Building/Building.h"
#include "Characters/Object/BoxAnimation.h"
#include "Characters/Item/Item.h"
#include "Characters/Object/ItemBox.h"
#include "Characters/Item/Manager/ItemManager.h"
#include "Characters/Object/ObjectManager.h"


//Manager
#include "Characters/Projectile/Manager/ProjectileManager.h"
#include "Characters/GameManager.h"
//UI
#include "Characters/UI/Ammo/AmmoUI.h"
#include "Characters/UI/Score/ScoreUI.h"
#include "Characters/UI/Timer/Timer.h"
#include "Characters/UI/Manager/UIManager.h"

class Scene
{//순수 가상함수가 들어간 인터페이스 제작
public:
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};