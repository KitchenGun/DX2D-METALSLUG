#pragma once
class Projectile;

enum class ENEMYTYPE
{
	NONE = 0,
	Grenadier
};
class Enemy : public PlayerAnimationRect
{
public:
	Enemy(Vector3 position, Vector3 size, float rotation,ENEMYTYPE enemyType);
	~Enemy();
	
	virtual void Update() override;
	virtual void Render() override;
	//이동
	void Move(Vector3 tempPos) override;
	void ObbGroundMove(Vector3 tempPos);
	void Jump();
	//사망&피격
	virtual void Die();
	void Hit(DAMAGE val, Projectile* tempProjectile=nullptr);
	//Get&Set
	void SetisGround(bool val) { isGround = val; }
	bool GetisGround() { return isGround; }
	Vector3 GetRootPos() { return RootPos; }
	OBBInfo* GetObbInfo() { return obbInfo; }
protected:
	bool isGround = false;//지상 판정
	Vector3 RootPos;

	//점프 수치
	JUMPPOW PlayerJumpPow = 0;
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 10.0f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -5;
	
	//Obb충돌에 필요한 정보
	OBBInfo* obbInfo;
	HP EnemyHP = 0;
	ENEMYTYPE enemyType = ENEMYTYPE::NONE;
};