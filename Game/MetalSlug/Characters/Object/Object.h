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
	void SetTarget(PlayerManager* val) { target = val; }
	void SetTarget(EnemyManager* val) { EM = val; }
private:
	EnemyManager* EM;
	PlayerManager* target;
};