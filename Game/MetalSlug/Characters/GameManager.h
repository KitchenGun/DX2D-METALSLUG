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

	void HeliDestroy();

	void Win();
	void ScoreChange(int val);
	int GetScore() { return Score; }
	bool GetisWin() { return isWin; }
	void SetTarget(Building* target) { Target=target; }
private:
	PlayerManager* PM;
	EnemyManager* EM;

	Building* Target = nullptr;

	//�ܰ� phase(ī�޶� ������ ����)
	int phase = 0;
	float SpawnRate = 1;
	bool isWin = false;
	//����
	int Score=0;
};