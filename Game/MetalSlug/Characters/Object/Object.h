#pragma once
class EnemyManager;

class Object:public PlayerAnimationRect
{
public:
	Object(Vector3 position, Vector3 size, float rotation);
	virtual ~Object() override;

	void Update() override;
	void Render() override;

	void PlayerBlock();
	void EnemyBlock();
	void SetTarget(Player* val) { target = val; }

private:
	EnemyManager* EM;
	Player* target;
};