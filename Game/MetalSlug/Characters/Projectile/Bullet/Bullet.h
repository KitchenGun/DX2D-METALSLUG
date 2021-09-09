#pragma once

class Bullet : public Projectile
{
public:
	Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT,EnemyManager* EnemyM);
	~Bullet();
public:
	void Update() override;
	void Render() override;
	void Move(Vector3 position) override;
private:
};