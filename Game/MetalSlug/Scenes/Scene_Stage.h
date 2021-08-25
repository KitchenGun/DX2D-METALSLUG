#pragma once
class Stage :public Scene
{
public:
	Stage();
	~Stage();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void GroundAdd(Ground* ground);
private:
	TextureRect* Map = nullptr;
	Player* player = nullptr;
	EnemySoldier* temp = nullptr;
	//지형 테스트
	vector<Ground*> GroundList;
	Ground* ground = nullptr;
	//manager
	ProjectileManager* PlayerPM = nullptr;
	EnemyManager* EnemyM = nullptr;
};