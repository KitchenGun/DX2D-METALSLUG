#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType)
	:PlayerAnimationRect(position, size, rotation)
{

}

Enemy::~Enemy()
{
	PlayerAnimationRect::~PlayerAnimationRect();
}
