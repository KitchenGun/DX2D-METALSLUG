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
	
	virtual void Update()=0;
	virtual void Render() = 0;

	virtual void Move(Vector3 pos)=0;

protected:
	ENEMYTYPE enemyType = ENEMYTYPE::NONE;
};