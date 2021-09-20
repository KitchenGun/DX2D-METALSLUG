#pragma once

enum class ObjectType
{
	NONE = 0,
	ROCK,
	BOX,
	BUILDING,
	POW
};

class Object :public PlayerAnimationRect
{
public:
	Object(Vector3 position, Vector3 size, float rotation,ObjectType OT, bool isRender = true);
	virtual ~Object() override;

	virtual void Update() override;
	void Render() override;

	void PlayerBlock();
	void EnemyBlock();
	void SetTarget(PlayerManager* val) { target = val; }
	void SetTarget(EnemyManager* val) { EM = val; }
	void SetPPM(ProjectileManager* val) { PPM = val; }
	bool GetIsNeedDestroy() { return IsNeedDestroy; }
	ObjectType GetObjType() { return ot; }
	void Hit(DAMAGE val, Projectile* tempProjectile = nullptr);
protected:
	EnemyManager* EM;
	PlayerManager* target;
	ProjectileManager* PPM;
	Projectile* PrevTemp;
	ObjectType ot = ObjectType::NONE;

	HP ObjHP = 0;
	vector<Projectile*> vecHitProjectile;
	bool IsRender = true;
	bool IsNeedDestroy = false;
};