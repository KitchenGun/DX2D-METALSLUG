#pragma once
enum class ENEMYTYPE
{
	NONE = 0,
	Grenadier
};
class Enemy : public PlayerAnimationRect
{
public:
	Enemy(Vector3 position, Vector3 size, float rotation,ENEMYTYPE enemyType);
	~Enemy();
	
	virtual void Update() override;
	virtual void Render() override;

protected:
	ENEMYTYPE enemyType = ENEMYTYPE::NONE;
};