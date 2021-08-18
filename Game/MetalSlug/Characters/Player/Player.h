#pragma once
typedef int HP;
typedef float JUMPPOW;
typedef float MOVESPEED;
class ProjectileManager;

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
	CROUCHIDLE,
	CROUCHATK,
	CROUCHMOVE,
	CROUCHJUMP,
	CROUCHJUMPATK,
	UPSIDE,
	UPSIDEATK,
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

class Player : public PlayerAnimationRect
{
public://생성자 소멸자 update render
	Player(Vector3 position, Vector3 size, float rotation);
	~Player();
	void Update() override;
	void Render() override;
	void Input();
	void Move(Vector3 tempPos);
	void Jump();

	void SetUpperAni();
	void SetLowerAni();
public:
	//Vector3 GetPos() { return position; }
	float GetSize() { return size.x; }
	DIRECTION GetDir() { return dir; }
	bool GetisCrouch() { return isCrouch; }
	bool GetisMove() { return isMove; }
	bool GetisGround() { return isGround; }
	void SetisGround(bool val) { isGround = val; }
	void SetPM(ProjectileManager* val) { PM = val; }
	SOLDIERSTATE GetLowerState() { return soldierLowerState; }
	SOLDIERSTATE GetUpperState() { return soldierUpperState; }
protected:
	HP PlayerHP = 0;
	JUMPPOW PlayerJumpPow = 0;
	MOVESPEED PlayerSpeed = 150.0f;
	STATE PlayerState = STATE::NONE;
	SOLDIER PlayerCharacter = SOLDIER::NONE;

private:
	SoldierLower* lowerBody = nullptr;
	SoldierUpper* upperBody = nullptr;
	Animator* upperBodyAnimator = nullptr;


	bool isGround = false;//지상 판정
	bool isCrouch = false;//앉기 키를 누른경우
	bool isMove = false;//움직이는 경우
	bool isHandUp = false;//손을 위로 올린 경우
	bool isAtk = false;//공격 상태

	DIRECTION dir=DIRECTION::NONE;

	SOLDIERSTATE soldierUpperState = SOLDIERSTATE::NONE;
	SOLDIERSTATE soldierLowerState = SOLDIERSTATE::NONE;
	//점프 수치
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 3.5f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -2.5f;
	//사격 
	ProjectileManager* PM = nullptr;
};