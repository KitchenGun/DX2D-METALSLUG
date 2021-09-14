#pragma once
enum class ENEMYSOLDIERSTATE
{
	NONE=0,
	IDLE,
	THROW,
	KNIFE,
	WALK,
	RUN,
	JUMP,
	SURPRISE,
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
	void HPCheck();

	void GroundCheck();
	void Move();
	void Die() override;
	void ATK();
	void MoveFirePos();

public:
	//Grenadier
	void ScoutRangeCheck();

public: //SET&GET
	ENEMYSOLDIERSTATE GetState() { return enemyState; }
public://S*R*T
	void SetSize(Vector3 tempSize);
private:
	ENEMYSOLDIERSTATE enemyState = ENEMYSOLDIERSTATE::NONE; 
	ENEMYSOLDIERSTATE nextEnemyState = ENEMYSOLDIERSTATE::NONE;
	ENEMYSOLDIERSTATE beforeEnemyState = ENEMYSOLDIERSTATE::NONE;
	GrenadierAni* grenadierAni = nullptr;
	Animator* EnemyAnimator = nullptr;
};
