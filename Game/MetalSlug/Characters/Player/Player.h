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
	//����
	NONE = 0,
	IDLE,
	JUMP,
	JUMPMOVE,
	//��ݽ�
	CROUCHIDLE,
	CROUCHMOVE,
	CROUCHJUMP,
	UPSIDE,
	//�Ϲݽ�
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

class Player : public AnimationRect
{
public://������ �Ҹ��� update render
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

	bool isGround = false;//���� ����
	bool isCrouch = false;//�ɱ� Ű�� �������
	bool isMove = false;//�����̴� ���
	bool isHandUp = false;//���� ���� �ø� ���
	
	DIRECTION dir=DIRECTION::NONE;

	SOLDIERSTATE soldierUpperState = SOLDIERSTATE::NONE;
	SOLDIERSTATE soldierLowerState = SOLDIERSTATE::NONE;
	//���� ��ġ
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 3.5f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -2.5f;
};