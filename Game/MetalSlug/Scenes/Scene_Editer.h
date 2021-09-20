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
	void ObjectCollision();

	//저장&불러오기
	void SaveGroundTile(const wstring& path = L"");
	void LoadGroundTile(const wstring& path = L"");
private:
	TextureRect* Map = nullptr;
	TextureRect* MapObj0 = nullptr;
	TextureRect* MapObj1 = nullptr;
	TextureRect* MapObj2 = nullptr;
	TextureRect* MapObj3 = nullptr;
	TextureRect* MapObj4 = nullptr;

	PlayerManager* PlayerM = nullptr;
	//지형 테스트
	vector<Ground*> GroundList;
	Ground* ground = nullptr;
	Rock1* object = nullptr;
	Rock1* object1 = nullptr;
	//manager
	ProjectileManager* PlayerPM = nullptr;
	ProjectileManager* EnemyPM = nullptr;
	EnemyManager* EnemyM = nullptr;
	ObjectManager* ObjectM = nullptr;
	GameManager* GameM = nullptr;
};