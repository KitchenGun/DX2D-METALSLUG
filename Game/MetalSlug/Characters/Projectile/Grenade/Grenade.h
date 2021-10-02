#pragma once

class Grenade : public Projectile
{
public:
	Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE PT, bool bisPPM=true);
	~Grenade();
public:
	void Update() override;
	void Render() override;
	void Move();

	void Explosion();
	bool GetIsHit() { return isHit; }
	void SetIsHit(bool val) { isHit = val; }
private:
	float ThrowingTime = 0;//던지고 경과한 시간
	float MaxTime = 0;
	SPEED Speed = 800.0f;
	float Angle = 0;
	float Gravity = 2300.0f;
	float animationRate = 1 / 10.0f;
	Vector3 StartPos;
	bool isHit = false;
	//지면
	int GroundIntersectCount = 0;

};