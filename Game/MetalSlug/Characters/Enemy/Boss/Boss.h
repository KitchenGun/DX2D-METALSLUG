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
	void ArtyAtk(float Angle);
	int ArtyAngle();
	//»ç¸Á&ÇÇ°Ý
	virtual void Die();
	void HPCheck();
	void Hit(DAMAGE val, Projectile* tempProjectile = nullptr) override;
	//set get
	BOSSSTATE GetBossState() { return BossState; }
protected:
	vector<Projectile*> vecHitProjectile;
	bool isHit = false;
	float HitDeltaTime = 0.0f;
	bool isLaserATK = false;
	bool isArtyATK = false;
	int fireCount = 0;
	int phase = -1;
	BOSSSTATE prevState = BOSSSTATE::NONE;
	BOSSSTATE BossState = BOSSSTATE::NONE;
	BOSSSTATE nextState = BOSSSTATE::NONE;
	TextureRect* BossBody = nullptr;
	BossCannon* bossCannon = nullptr;
};