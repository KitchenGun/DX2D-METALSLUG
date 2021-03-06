#pragma once
class ObjectManager;

class Projectile : public AnimationRect
{
public:
	Projectile(Vector3 position, Vector3 size, float rotation, DIRECTION dir,PROJECTILETYPE BT,SFXManager* sfxm,bool isPPM=true);
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
	void SetEPM(ProjectileManager* val) { EPM = val; }
	void SetPM(PlayerManager* val) { PM = val; }
	void SetOM(ObjectManager* val) { OM = val; }
	DIRECTION GetDir() { return Dir; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
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
	ObjectManager* OM = nullptr;
	ProjectileManager* EPM = nullptr;
	SFXManager* SFXM = nullptr;
	bool isNeedDestroy=false;
	vector<Ground*> GroundList;
};