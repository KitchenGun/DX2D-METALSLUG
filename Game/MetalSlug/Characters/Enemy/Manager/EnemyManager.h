#pragma once
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();

	void AddEnemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType);
	void RemoveEnemy(Enemy* tempEnemy);

	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Enemy*> GetEnemyList() { return enemyList; }
private:
	list<Enemy*> enemyList;
	list<Enemy*>::iterator iter;
	//ÁöÇü
	vector<Ground*> GroundList;
};