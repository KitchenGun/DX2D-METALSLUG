#pragma once
class GameManager;
class SFXManager;
class EnemyManager
{
public:
	EnemyManager(ProjectileManager* epm);
	~EnemyManager();

	void Update();
	void Render();

	void AddEnemy(Vector3 position, ENEMYTYPE enemyType);
	void AddBoss(Vector3 position);
	void RemoveEnemy(Enemy* tempEnemy);
	void SetPM(PlayerManager* val) { PM = val; }
	void SetGM(GameManager* val) { GM = val; }
	void SetGroundList(vector<Ground*> val) { GroundList = val; }
	list<Enemy*> GetEnemyList() { return enemyList; }
	void SetSFX(SFXManager* val) { SFXM = val; }

	void ScearmSoundPlay();
	void DieSoundPlay();
	void DropBomb();
	void BossAtrySoundPlay();
	void BossDie();
	void BossChangeMode();
	void BossLaserCharge();
	void BossLaserFire();
private:
	list<Enemy*> enemyList;
	list<Enemy*>::iterator iter;
	//ÁöÇü
	vector<Ground*> GroundList;
	ProjectileManager* EPM;
	PlayerManager* PM;
	GameManager* GM;
	SFXManager* SFXM;

	Enemy* boss = nullptr;

	SoundSystem* Voice = nullptr;
	SoundSystem* Sfx = nullptr;
	SoundSystem* Heli = nullptr;
};