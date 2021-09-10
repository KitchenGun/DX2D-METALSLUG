#pragma once

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void Update();
	void Render();

	void AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void AddGrenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void RemoveProjectile(Projectile* tempProjectile);
	void SetEM(EnemyManager* val) { EM = val; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Projectile*> GetList() {return projectileList;}
private:
	list<Projectile*> projectileList;
	list<Projectile*>::iterator iter;

	EnemyManager* EM=nullptr;
	vector<Ground*> GroundList;
};