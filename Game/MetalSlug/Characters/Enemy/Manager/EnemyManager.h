#pragma once
class EnemyManager
{
public:
	EnemyManager(ProjectileManager* epm);
	~EnemyManager();

	void Update();
	void Render();

	void AddEnemy(Vector3 position, ENEMYTYPE enemyType);
	void RemoveEnemy(Enemy* tempEnemy);
	void SetPM(PlayerManager* val) { PM = val; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Enemy*> GetEnemyList() { return enemyList; }
private:
	list<Enemy*> enemyList;
	list<Enemy*>::iterator iter;
	//ÁöÇü
	vector<Ground*> GroundList;
	ProjectileManager* EPM;
	PlayerManager* PM;
};