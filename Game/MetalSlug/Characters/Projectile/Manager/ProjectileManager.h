#pragma once

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void Update();
	void Render();

	void AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void RemoveProjectile(Projectile* tempProjectile);
	void SetEM(EnemyManager* val) { EM = val; }
	list<Projectile*> GetList() {return projectileList;}
private:
	list<Projectile*> projectileList;
	list<Projectile*>::iterator iter;

	EnemyManager* EM=nullptr;
};