#pragma once
class PlayerManager;
class ProjectileManager;
class EnemyManager;
class Projectile;

enum class PROJECTILETYPE
{
	NONE = 0,
	KNIFE,
	PISTOL,
	HEAVY,
	Grenade,
	EnemyGrenade,
	BOSSLASER,
	BOSSARTY,
	HELIBOMB
};

struct OBBInfo
{
	bool isObb = false;
	float Gradient = 0;
	float alphaVal = 0;
};

struct FirePos
{
	Vector3 Pos=Vector3(0,0,0);
	float Rotation = 0;
};

enum class STATE
{
	NONE=0,
	SOLDIER,
	SLUG
};

enum class SOLDIERSTATE
{
	//공통
	NONE = 0,
	IDLE,
	JUMP,
	JUMPMOVE,
	//상반신
	ATK,
	KNIFEATK,
	THROW,
	CROUCHIDLE,
	CROUCHATK,
	CROUCHKNIFEATK,
	CROUCHTHROW,
	CROUCHMOVE,
	CROUCHJUMP,
	CROUCHJUMPSTART,
	CROUCHJUMPATK,
	CROUCHJUMPATKSTART,
	UPSIDE,
	UPSIDESTART,
	UPSIDEATK,
	UPSIDEATKSTART,
	DIE,
	WIN,
	//하반신
	MOVE
};

enum class SOLDIER
{
	NONE=0,
	MARCO
};

enum class DIRECTION
{
	NONE=0,
	LEFT,
	RIGHT
};

enum class COLLIDER
{
	NONE = 0,
	SMALL,
	BIG
};

class Player : public PlayerAnimationRect
{
public://생성자 소멸자 update render
	Player(Vector3 position, Vector3 size, float rotation);
	~Player() override;
	void Update() override;
	void Render() override;
	void Input();
	void Move(Vector3 tempPos);
	void ObbGroundMove(Vector3 tempPos);
	
	void Knife();
	void Fire(bool isFirstHandUp, bool isFirstCrouchJump);
	void Grenade();
	void Jump();
	void MoveFirePos(bool isFirstHandUp, bool isFirstCrouchJump);
	void ColliderSizeChange(COLLIDER val);
	void HeavyFire();
	void Hit(DAMAGE val, Projectile* tempProjectile = nullptr);
	void HPCheck();
	void Die();
	void Win();
	void AmmoCheck();
	void ItemTake(PROJECTILETYPE ItemInfo);
public://Get&Set
	bool GetisDestroy() { return isDestroy; }
	void SetUpperAni();
	void SetLowerAni();
	float GetSize() { return IMGsize; }
	DIRECTION GetDir() { return dir; }
	DIRECTION GetBlockDir() { return BlockDir; }
	void SetBlockDir(DIRECTION val) { BlockDir = val; }
	bool GetisCrouch() { return isCrouch; }
	bool GetisMove() { return isMove; }
	bool GetisGround() { return isGround; }
	bool GetisJump() { return isJump; }
	Vector3 GetRootPos() { return RootPos; }
	void SetisGround(bool val) { isGround = val; }
	bool GetisObject() { return isObject; }
	void SetisObject(bool val) { isObject = val; }
	void SetPM(ProjectileManager* val) { PM = val; }
	void SetEM(EnemyManager* val) { EM = val; }
	OBBInfo* GetObbInfo() { return obbInfo; }
	SOLDIERSTATE GetLowerState() { return soldierLowerState; }
	SOLDIERSTATE GetUpperState() { return soldierUpperState; }
	PROJECTILETYPE GetProjectileType() { return PlayerProjectileType; }
	int GetAmmo() { return Ammo; }
	int GetBomb() { return Bomb; }
	bool GetDie() { return isDie; }
	void SetPlayerM(PlayerManager* val) { PlayerM = val; }
	bool GetisHeavy() { return isHeavyFire; }
protected:
	PROJECTILETYPE HitBy=PROJECTILETYPE::NONE;
	HP PlayerHP = 1;
	MOVESPEED PlayerSpeed = 350.0f;
	STATE PlayerState = STATE::NONE;
	SOLDIER PlayerCharacter = SOLDIER::NONE;

private:
	SoldierLower* lowerBody = nullptr;
	SoldierUpper* upperBody = nullptr;
	Animator* upperBodyAnimator = nullptr;

	float IMGsize = 3;
	bool isObject = false;
	bool isGround = false;//지상 판정
	bool isCrouch = false;//앉기 키를 누른경우
	bool isMove = false;//움직이는 경우
	bool isHandUp = false;//손을 위로 올린 경우
	bool isAtk = false;//공격 상태
	bool isDie = false;
	bool isEnd = false;
	bool isDestroy = false;
	
	DIRECTION dir=DIRECTION::NONE;
	DIRECTION BlockDir = DIRECTION::NONE;

	SOLDIERSTATE soldierUpperState = SOLDIERSTATE::NONE;
	SOLDIERSTATE soldierLowerState = SOLDIERSTATE::NONE;
	//점프 수치
	JUMPPOW PlayerJumpPow = 0;
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 1500.0f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -600;

	//root
	Vector3 RootPos;
	OBBInfo* obbInfo;
	//사격 
	PROJECTILETYPE PlayerProjectileType = PROJECTILETYPE::PISTOL;
	bool isHeavyFire = false;
	int Ammo = 0;
	int Bomb = 10;
	int HeavyFireCount = 0;
	ProjectileManager* PM = nullptr;
	FirePos firePos;
	float fireRate = 1 / 100.0f;
	float HeavyfireRate = 1 / 30.0f;
	float DownPressTime = 0;
	float UpPressTime = 0;
	//칼질
	EnemyManager* EM;
	const float KnifeRange = 45 * IMGsize;
	bool isKnife = false;
	//수류탄
	bool isThrow = false;
	int ThrowCount = 0;
	float ThrowRate = 1 / 10.0f;
	bool isCoolTime = false;

	PlayerManager* PlayerM = nullptr;;
};