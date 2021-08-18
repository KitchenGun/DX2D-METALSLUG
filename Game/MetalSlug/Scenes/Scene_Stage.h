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

private:
	TextureRect* Map = nullptr;
	Player* player = nullptr;
	EnemySoldier* temp = nullptr;
	//���� �׽�Ʈ
	Ground* ground = nullptr;
	//manager
	ProjectileManager* PlayerPM = nullptr;

};