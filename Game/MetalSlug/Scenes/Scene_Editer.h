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

	//����&�ҷ�����
	void SaveGroundTile(const wstring& path = L"");
	void LoadGroundTile(const wstring& path = L"");
private:
	TextureRect* Map = nullptr;
	Player* player = nullptr;
	EnemySoldier* temp = nullptr;
	//���� �׽�Ʈ
	vector<Ground*> GroundList;
	Ground* ground = nullptr;
	Object* object = nullptr;
	//manager
	ProjectileManager* PlayerPM = nullptr;
	EnemyManager* EnemyM = nullptr;
};