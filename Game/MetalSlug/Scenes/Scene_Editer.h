#pragma once
class Editer :public Scene
{
public:
	Editer();
	~Editer();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void InputGround();
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