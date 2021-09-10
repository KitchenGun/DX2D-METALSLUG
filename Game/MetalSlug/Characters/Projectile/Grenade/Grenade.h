#pragma once

class Grenade : public Projectile
{
public:
	Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, EnemyManager* EnemyM);
	~Grenade();
public:
	void Update() override;
	void Render() override;
	void Move();
private:
	float ThrowingTime = 0;//던지고 경과한 시간
	float MaxTime = 0;
	SPEED Speed = 800.0f;
	float Angle = 0;
	float Gravity = 2300.0f;
	float animationRate = 1 / 1.2f;
	Vector3 StartPos;
};