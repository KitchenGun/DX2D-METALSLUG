#pragma once

class GameManager
{
public:
	GameManager(PlayerManager* pm, EnemyManager* em);
	~GameManager();
public:
	void AddEnemy(ENEMYTYPE ET,Vector3 Pos);
	void AddPlayer(Vector3 Pos);

	void CameraMove();
	void EnemySpawn();
	void Update();
	void PlayerTracking();
	void Win();
	void ScoreChange(int val);
private:
	PlayerManager* PM;
	EnemyManager* EM;

	//�ܰ� phase(ī�޶� ������ ����)
	int phase = 0;
	float SpawnRate = 1;
	//����
	int Score=0;
};