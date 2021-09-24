#pragma once
enum class BOSSSTATE 
{
	NONE,
	IDLE,
	LASERTOARTY,
	ARTYTOLASER,
	ARTY,
	LASERCHARGE,
	LASER,
	DIE
};

class Boss : public Enemy
{
public:
	Boss(Vector3 position, Vector3 size, float rotation);
	~Boss();

	void Update() override;
	void Render() override;
	void SetAni();

	void LaserAtk();
	void ArtyAtk();

	//»ç¸Á&ÇÇ°Ý
	virtual void Die();
	void HPCheck();
	void Hit(DAMAGE val, Projectile* tempProjectile = nullptr) override;
	void ColliderSizeChange(COLLIDER val);
	//set get
	BOSSSTATE GetBossState() { return BossState; }
protected:
	vector<Projectile*> vecHitProjectile;

	bool isLaserATK = false;

	int phase = -1;
	BOSSSTATE prevState = BOSSSTATE::NONE;
	BOSSSTATE BossState = BOSSSTATE::NONE;
	BOSSSTATE nextState = BOSSSTATE::NONE;
	TextureRect* BossBody = nullptr;
	BossCannon* bossCannon = nullptr;
};