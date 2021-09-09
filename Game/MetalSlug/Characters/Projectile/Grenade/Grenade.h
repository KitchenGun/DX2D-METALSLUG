#pragma once

class Grenade : public Projectile
{
public:
	Grenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, EnemyManager* EnemyM);
	~Grenade();
public:
	void Update() override;
	void Render() override;
	void Move(Vector3 position) override;
private:
};