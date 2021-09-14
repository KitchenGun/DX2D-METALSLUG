#pragma once

class ProjectileManager
{
public:
	ProjectileManager(bool isPM=true);
	~ProjectileManager();

	void Update();
	void Render();

	void AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void AddGrenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void RemoveProjectile(Projectile* tempProjectile);
	void SetTargetM(EnemyManager* val) { EM = val; }
	void SetTargetM(PlayerManager* val) { PM = val; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Projectile*> GetList() {return projectileList;}

	const bool bIsPM;
private:
	list<Projectile*> projectileList;
	list<Projectile*>::iterator iter;

	EnemyManager* EM=nullptr;
	PlayerManager* PM = nullptr;
	vector<Ground*> GroundList;
};