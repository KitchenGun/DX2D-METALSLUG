#pragma once

class ProjectileManager
{
public:
	ProjectileManager(bool isPM = true);
	~ProjectileManager();

	void Update();
	void Render();

	void AddBullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void AddGrenade(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT);
	void AddArty(Vector3 position, Vector3 size, float rotation,PROJECTILETYPE BT);
	void AddLaser(Vector3 position, Vector3 size, PROJECTILETYPE BT);
	void AddHeliBomb(Vector3 position, Vector3 size);
	void RemoveProjectile(Projectile* tempProjectile);
	void SetTargetM(EnemyManager* val) { EM = val; }
	void SetTargetM(PlayerManager* val) { PM = val; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	void SetOM(ObjectManager* val) { OM = val; }
	void SetEPM(ProjectileManager* val) { EPM = val; }
	list<Projectile*> GetList() {return projectileList;}

	const bool bIsPM;
private:
	list<Projectile*> projectileList;
	list<Projectile*>::iterator iter;

	EnemyManager* EM=nullptr;
	PlayerManager* PM = nullptr;
	ObjectManager* OM = nullptr;
	vector<Ground*> GroundList;
	//enemyProjectile 충돌처리를 위해서
	ProjectileManager* EPM = nullptr;
};