#pragma once
typedef int HP;
typedef float JUMPPOW;
typedef float MOVESPEED;

enum class STATE
{
	NONE=0,
	SOLDIER,
	SLUG
};

enum class SOLDIERSTATE
{
	NONE = 0,
	IDLE,
	MOVE,
	CROUCH,
	CROUCHMOVE,
	JUMP,
	CrouchJump
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

class Player : public AnimationRect
{
public://생성자 소멸자 update render
	Player(Vector3 position, Vector3 size, float rotation);
	~Player();
	void Update() override;
	void Render() override;
	void Input();
	void Move(Vector3 tempPos);
	void Jump();

public:
	//Vector3 GetPos() { return position; }
	float GetSize() { return size.x; }
	DIRECTION GetDir() { return dir; }
	bool GetisCrouch() { return isCrouch; }
	bool GetisMove() { return isMove; }
	bool GetisGround() { return isGround; }
	void SetisGround(bool val) { isGround = val; }
protected:
	HP PlayerHP = 0;
	JUMPPOW PlayerJumpPow = 0;
	MOVESPEED PlayerSpeed = 150.0f;
	STATE PlayerState = STATE::NONE;
	SOLDIER PlayerCharacter = SOLDIER::NONE;

private:
	SoldierLower* lowerBody = nullptr;
	SoldierUpper* upperBody = nullptr;

	bool isGround = false;//지상 판정
	bool isCrouch = false;//앉기 키를 누른경우
	bool isMove = false;//움직이는 경우
	bool isHandUp = false;//손을 위로 올린 경우
	
	DIRECTION dir=DIRECTION::NONE;
	SOLDIERSTATE soldierState = SOLDIERSTATE::NONE;

	//점프 수치
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 5.0f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -1.0f;
};