#pragma once

class Projectile : public AnimationRect
{
public:
	Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir);
	~Projectile();
public:
	virtual void Update() override;
	virtual void Render() override;

	DAMAGE GetDamage() { return Damage; }
	Vector3 GetStartPos() { return StartPos; }
protected:
	DIRECTION Dir = DIRECTION::NONE;
	SPEED Speed = 0.0f;
	Vector3 StartPos;
	DAMAGE Damage = 0;
};