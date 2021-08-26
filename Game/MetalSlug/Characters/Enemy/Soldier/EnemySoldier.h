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
	
public://Animation
	void SetAnimation();
	void SetClip();
public://S*R*T
	void SetSize(Vector3 tempSize);
private:
	DIRECTION dir = DIRECTION::LEFT;
	ENEMYSOLDIERSTATE enemyState = ENEMYSOLDIERSTATE::NONE;
	
};
