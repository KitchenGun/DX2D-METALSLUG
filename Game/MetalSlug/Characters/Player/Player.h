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
	JUMPMOVE
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

class Player
{
public://생성자 소멸자 update render
	Player(Vector3 position, Vector3 size, float rotation);
	~Player();
	void Update();
	void Render();
	void Input();
public:
	Vector3 GetPos() { return pos; }
	float GetSize() { return size; }
	DIRECTION GetDir() { return dir; }
	bool GetisCrouch() { return isCrouch; }
	bool GetisMove() { return isMove; }
protected:
	HP PlayerHP = 0;
	JUMPPOW PlayerJumpPow = 0;
	MOVESPEED PlayerSpeed = 0;
	STATE PlayerState = STATE::NONE;
	SOLDIER PlayerCharacter = SOLDIER::NONE;

private:
	SoldierLower* lowerBody = nullptr;
	SoldierUpper* upperBody = nullptr;

	bool isCrouch = false;//앉기 키를 누른경우
	bool isMove = false;//움직이는 경우
	Vector3 pos;
	float size;
	DIRECTION dir=DIRECTION::NONE;
	SOLDIERSTATE soldierState = SOLDIERSTATE::NONE;
};