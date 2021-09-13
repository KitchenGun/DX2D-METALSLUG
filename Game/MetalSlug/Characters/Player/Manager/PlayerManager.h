#pragma once
class PlayerManager
{
public:
	PlayerManager(ProjectileManager* ppm,EnemyManager* em);
	~PlayerManager();

	void Update();
	void Render();

	void AddPlayer(Vector3 position);
	void RemovePlayer(Player* tempPlayer);

	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Player*> GetPlayerList() { return playerList; }
private:
	list<Player*> playerList;
	list<Player*>::iterator iter;
	//ÁöÇü
	vector<Ground*> GroundList;
	ProjectileManager* PPM = nullptr;
	EnemyManager* EM = nullptr;
};