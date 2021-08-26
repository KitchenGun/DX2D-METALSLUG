#pragma once
enum class ENEMYSOLDIERSTATE
{
	NONE=0,
	IDLE,
	DIE
};

class EnemySoldier :public Enemy
{
public:
	EnemySoldier(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType);
	~EnemySoldier();

public:
	void Update() override;
	void Render() override;
	void Move(Vector3 pos) override;
	void Jump();
public://Animation
	void SetAnimation();
	void SetClip();
public://S*R*T
	void SetSize(Vector3 tempSize);
public:
	void SetisGround(bool val) { isGround = val; }
private:
	DIRECTION dir = DIRECTION::LEFT;
	ENEMYSOLDIERSTATE enemyState = ENEMYSOLDIERSTATE::NONE;
	//점프 수치
	JUMPPOW PlayerJumpPow = 0;
	bool isJump = false;
	bool isJumpEnd = false;
	float fJumpPower = 0.0f;
	const float fMaxJumpSpeed = 10.0f;
	int nJumpCount = 0;
	const int nMaxJumpCount = 1;
	float GravatiyPower = -5;
};
