#pragma once

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void Update();
	void Render();

	void AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, BULLETTYPE BT);
	void RemoveProjectile(Projectile* tempProjectile);
private:
	list<Projectile*> projectileList;
	list<Projectile*>::iterator iter;
};