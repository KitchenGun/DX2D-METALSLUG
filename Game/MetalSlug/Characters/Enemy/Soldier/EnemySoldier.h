#pragma once
enum class ENEMYSOLDIERSTATE
{
	NONE=0,
	IDLE,
	THROW,
	KNIFE,
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
	void Die() override;
public:
	//Grenadier
	void ScoutRangeCheck();


public: //SET&GET
	ENEMYSOLDIERSTATE GetState() { return enemyState; }
	DIRECTION GetDir() { return dir; }
public://S*R*T
	void SetSize(Vector3 tempSize);
private:
	DIRECTION dir = DIRECTION::LEFT;
	ENEMYSOLDIERSTATE enemyState = ENEMYSOLDIERSTATE::NONE;
	GrenadierAni* grenadierAni = nullptr;
};
