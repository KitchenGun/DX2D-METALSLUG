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

	//사운드
	void DieSoundPlay();
	void GetHeavySoundPlay();
	void GunFireSoundPlay(bool isHeavy);
	void KnifeSoundPlay();
	//GetSet
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Player*> GetPlayerList() { return playerList; }
	Player* GetPlayer() { return player; }
private:
	list<Player*> playerList;
	list<Player*>::iterator iter;
	
	vector<Ground*> GroundList;
	ProjectileManager* PPM = nullptr;
	EnemyManager* EM = nullptr;

	Player* player;
	bool isDieTrigger = false;

	//사운드
	SoundSystem* Voice = nullptr;
	SoundSystem* Sfx = nullptr;
};