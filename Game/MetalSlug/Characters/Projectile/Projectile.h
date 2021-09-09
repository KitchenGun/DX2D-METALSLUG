#pragma once

class Projectile : public AnimationRect
{
public:
	Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir,PROJECTILETYPE BT);
	~Projectile();
public:
	virtual void Update() override;
	virtual void Render() override;
	void ProjectileCollisionCheck();

	DAMAGE GetDamage() { return Damage; }
	Vector3 GetStartPos() { return StartPos; }
	PROJECTILETYPE GetPT() { return pt; }
	float GetRotation() { return rotation; }
	void SetEM(EnemyManager* val) { EM = val; }
	bool GetIsNeedDestroy() { return isNeedDestroy; }
protected:
	DIRECTION Dir = DIRECTION::NONE;
	SPEED Speed = 0.0f;
	Vector3 StartPos;
	DAMAGE Damage = 0;
	PROJECTILETYPE pt = PROJECTILETYPE::NONE;
	EnemyManager* EM = nullptr;
	bool isNeedDestroy=false;
};