#pragma once
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();

	void ProjectileCollisionCheck(Enemy* tempEnemy);

	void AddEnemy(Vector3 position, Vector3 size, float rotation, ENEMYTYPE enemyType);
	void RemoveEnemy(Enemy* tempEnemy);

	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	void SetPPM(ProjectileManager* val) { PPM = val; }
private:
	list<Enemy*> enemyList;
	list<Enemy*>::iterator iter;
	//����
	vector<Ground*> GroundList;
	//player ����ü �Ŵ���
	ProjectileManager* PPM;

};