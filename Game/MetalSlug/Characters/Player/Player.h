#pragma once
class ProjectileManager;

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
	//����
	NONE = 0,
	IDLE,
	JUMP,
	JUMPMOVE,
	//��ݽ�
	ATK,
	CROUCHIDLE,
	CROUCHATK,
	CROUCHMOVE,
	CROUCHJUMP,
	CROUCHJUMPATK,
	UPSIDE,
	UPSIDEATK,
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

class Player : public PlayerAnimationRect
{
public://������ �Ҹ��� update render
	Player(Vector3 position, Vector3 size, float rotation);
	~Player() override;
	void Update() override;
	void Render() override;
	void Input();
	void Move(Vector3 tempPos);
	void ObbGroundMove(Vector3 tempPos);
	
	
	void Fire();
	void Jump();
	void MoveFirePos();
	void ColliderSizeChange(bool isSmall);


public://Get&Set
	void SetUpperAni();
	void SetLowerAni();
	float GetSize() { return IMGsize; }
	DIRECTION GetDir() { return dir; }
	DIRECTION GetBlockDir() { return BlockDir; }
	void SetBlockDir(DIRECTION val) { BlockDir = val; }
	bool GetisCrouch() { return isCrouch; }
	bool GetisMove() { return isMove; }
	bool GetisGround() { return isGround; }
	Vector3 GetRootPos() { return RootPos; }
	void SetisGround(bool val) { isGround = val; }
	void SetPM(ProjectileManager* val) { PM = val; }
	OBBInfo* GetObbInfo() { return obbInfo; }
	SOLDIERSTATE GetLowerState() { return soldierLowerState; }
	SOLDIERSTATE GetUpperState() { return soldierUpperState; }

protected:
	HP PlayerHP = 1;
	MOVESPEED PlayerSpeed = 350.0f;
	STATE PlayerState = STATE::NONE;
	SOLDIER PlayerCharacter = SOLDIER::NONE;

private:
	SoldierLower* lowerBody = nullptr;
	SoldierUpper* upperBody = nullptr;
	Animator* upperBodyAnimator = nullptr;

	float IMGsize = 0;

	bool isGround = false;//���� ����
	bool isCrouch = false;//�ɱ� Ű�� �������
	bool isMove = false;//�����̴� ���
	bool isHandUp = false;//���� ���� �ø� ���
	bool isAtk = false;//���� ����

	DIRECTION dir=DIRECTION::NONE;
	DIRECTION BlockDir = DIRECTION::NONE;

	SOLDIERSTATE soldierUpperState = SOLDIERSTATE::NONE;
	SOLDIERSTATE soldierLowerState = SOLDIERSTATE::NONE;
	//���� ��ġ
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
	//��� 
	ProjectileManager* PM = nullptr;
	FirePos firePos;
};