#pragma once

class Projectile : public AnimationRect
{
public:
	Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir,PROJECTILETYPE BT,bool isPPM=true);
	virtual ~Projectile();
public:
	virtual void Update() override;
	virtual void Render() override;
	void ProjectileCollisionCheck();

	DAMAGE GetDamage() { return Damage; }
	Vector3 GetStartPos() { return StartPos; }
	PROJECTILETYPE GetPT() { return pt; }
	float GetRotation() { return rotation; }
	void SetEM(EnemyManager* val) { EM = val; }
	void SetPM(PlayerManager* val) { PM = val; }
	bool GetIsNeedDestroy() { return isNeedDestroy; }
protected:
	const bool IsPPM = true;
	DIRECTION Dir = DIRECTION::NONE;
	SPEED Speed = 0.0f;
	Vector3 StartPos;
	Vector3 HitPos;
	DAMAGE Damage = 0;
	PROJECTILETYPE pt = PROJECTILETYPE::NONE;
	EnemyManager* EM = nullptr;
	PlayerManager* PM = nullptr;
	bool isNeedDestroy=false;
};