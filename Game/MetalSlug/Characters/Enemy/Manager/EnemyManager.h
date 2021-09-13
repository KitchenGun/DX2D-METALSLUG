#pragma once
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();

	void AddEnemy(Vector3 position, ENEMYTYPE enemyType);
	void RemoveEnemy(Enemy* tempEnemy);

	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	void SetPM(PlayerManager* val) { PM = val; }
	list<Enemy*> GetEnemyList() { return enemyList; }
private:
	list<Enemy*> enemyList;
	list<Enemy*>::iterator iter;
	//ÁöÇü
	vector<Ground*> GroundList;
	PlayerManager* PM;
};