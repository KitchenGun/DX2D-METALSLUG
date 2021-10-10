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

	TextureRect* MapBackGround = nullptr;
	TextureRect* MapBackGround1 = nullptr;
	BackGround* MapGroundWaterDown = nullptr;
	BackGround* MapGroundWaterUp = nullptr;
	BackGround* MapGroundWaterDown1 = nullptr;
	BackGround* MapGroundWaterUp1 = nullptr;
	BackGround* MapBoat = nullptr;
	BackGround* MapWaterFall = nullptr;
	BackGround* MapWaterFall1 = nullptr;
	BackGround* MapWaterFall2 = nullptr;
	BackGround* MapWaterFall3 = nullptr;
	//지형 테스트
	vector<Ground*> GroundList;
	Ground* ground = nullptr;
	Rock1* object = nullptr;
	Rock1* object1 = nullptr;
	//manager
	PlayerManager* PlayerM = nullptr;
	ProjectileManager* PlayerPM = nullptr;
	ProjectileManager* EnemyPM = nullptr;
	EnemyManager* EnemyM = nullptr;
	ObjectManager* ObjectM = nullptr;
	ItemManager* ItemM = nullptr;
	GameManager* GameM = nullptr;
	UIManager* UIM = nullptr;
	SFXManager* SFXM = nullptr;
};