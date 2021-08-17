#pragma once

class Projectile : public AnimationRect
{
public:
	Projectile(Vector3 position, Vector3 size, float rotation,DIRECTION Dir);
	~Projectile();
public:
	virtual void Update() override;
	virtual void Render() override;

protected:
	DIRECTION Dir = DIRECTION::NONE;
	float fSpeed = 0.0f;
};