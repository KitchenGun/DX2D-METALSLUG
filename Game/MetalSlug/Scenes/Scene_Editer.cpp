#include "stdafx.h"
#include "Scene_Editer.h"

Editer::Editer()
{
}

Editer::~Editer()
{
	SAFE_DELETE(GameM);
	SAFE_DELETE(ItemM);
	SAFE_DELETE(ObjectM);
	SAFE_DELETE(EnemyM);
	SAFE_DELETE(EnemyPM);
	SAFE_DELETE(PlayerPM);
	SAFE_DELETE(PlayerM);
	SAFE_DELETE(object1);
	SAFE_DELETE(object);

	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}

	SAFE_DELETE(MapWaterFall3);
	SAFE_DELETE(MapWaterFall2);
	SAFE_DELETE(MapWaterFall1);
	SAFE_DELETE(MapWaterFall);

	SAFE_DELETE(MapBoat);
	SAFE_DELETE(MapGroundWaterUp1);
	SAFE_DELETE(MapGroundWaterDown1);
	SAFE_DELETE(MapGroundWaterUp);
	SAFE_DELETE(MapGroundWaterDown);
	SAFE_DELETE(MapBackGround1);
	SAFE_DELETE(MapBackGround);

	SAFE_DELETE(MapObj4);
	SAFE_DELETE(MapObj3);
	SAFE_DELETE(MapObj2);
	SAFE_DELETE(MapObj1);
	SAFE_DELETE(MapObj0);
	SAFE_DELETE(Map);

}

void Editer::Init()
{
	Map = new TextureRect(Vector3(4153 * 4 / 2, 306 * 4 / 2, 0), Vector3(4153 * 4, 306 * 4, 1), 0);
	Map->SetSRV(L"./_Textures/Map/Map.png");
	MapObj0 = new TextureRect(Vector3(1220 * 4, 30 * 4, 0), Vector3(69 * 4, 46 * 4, 1), 0);
	MapObj0->SetSRV(L"./_Textures/Map/MapObj1.png");
	MapObj1 = new TextureRect(Vector3(1440 * 4, 58 * 4, 0), Vector3(151 * 4, 90 * 4, 1), 0);
	MapObj1->SetSRV(L"./_Textures/Map/MapObj2.png");
	MapObj2 = new TextureRect(Vector3(2000 * 4, 110 * 4, 0), Vector3(65 * 4, 67 * 4, 1), 0);
	MapObj2->SetSRV(L"./_Textures/Map/MapObj5.png");
	MapObj3 = new TextureRect(Vector3(8230, 40 * 4, 0), Vector3(47 * 4, 32 * 4, 1), 0);
	MapObj3->SetSRV(L"./_Textures/Map/MapObj3.png");
	MapObj4 = new TextureRect(Vector3(12200, 100 * 4, 0), Vector3(236 * 4, 224 * 4, 1),0);
	MapObj4->SetSRV(L"./_Textures/Map/MapObj6.png");
	MapBackGround = new TextureRect(Vector3(7000 + (868 * 4) * 0.5f, 540, 0), Vector3(350 * 4, 180 * 4, 1), 0);
	MapBackGround->SetSRV(L"./_Textures/Map/MapBackGround.png");
	MapBackGround1 = new TextureRect(Vector3(7700+(860 * 2)+(868 * 2), WinMaxHeight/2+200, 0), Vector3(868*4, 214*4, 1), 0);
	MapBackGround1->SetSRV(L"./_Textures/Map/MapBackGround-1.png");
	MapGroundWaterDown = new BackGround(Vector3(7500 + (868 * 4) * 0.5f, 40, 0), Vector3(901 * 4, 32 * 4, 1), 0, BGTYPE::STAGE1WATER0DOWN);
	MapGroundWaterUp = new BackGround(Vector3(7500 + (868 * 4) * 0.5f, 150, 0), Vector3(901 * 4, 16 * 4, 1), 0, BGTYPE::STAGE1WATER0UP);
	MapGroundWaterDown1 = new BackGround(Vector3(12200, 50, 0), Vector3(605 * 4, 32 * 4, 1), 0, BGTYPE::STAGE1WATER1DOWN);
	MapGroundWaterUp1 = new BackGround(Vector3(12200, 150, 0), Vector3(605 * 4, 16 * 4, 1), 0, BGTYPE::STAGE1WATER1UP);
	MapBoat = new BackGround(Vector3(12100+ 605 * 2, 755, 0), Vector3(460 * 4, 310 * 4, 1), 0, BGTYPE::STAGE1BOAT);
	MapWaterFall = new BackGround(Vector3(15550, 855, 0), Vector3(277 * 4, 200 * 4, 1), 0, BGTYPE::STAGE1WATERFALL);
	MapWaterFall1 = new BackGround(Vector3(14200, 655, 0), Vector3(430 * 4, 272 * 4, 1), 0, BGTYPE::STAGE1GROUNDWATERFALL1);
	MapWaterFall2 = new BackGround(Vector3(14930, 595, 0), Vector3(832 * 4, 304 * 4, 1), 0, BGTYPE::STAGE1GROUNDWATERFALL2);
	//ground
	InputGround();
	
	//manager
	PlayerPM = new ProjectileManager();
	EnemyPM = new ProjectileManager(false);
	EnemyM = new EnemyManager(EnemyPM);
	PlayerM = new PlayerManager(PlayerPM, EnemyM);
	ItemM = new ItemManager(PlayerM);
	EnemyM->SetPM(PlayerM);
	PlayerPM->SetTargetM(EnemyM);
	EnemyPM->SetTargetM(PlayerM);
	PlayerM->AddPlayer(Vector3(50 *3, 700, 0));

	EnemyM->AddEnemy(Vector3(600, 500, 0), ENEMYTYPE::Grenadier);

	GameM = new GameManager(PlayerM, EnemyM);
	EnemyM->SetGM(GameM);
	ObjectM = new ObjectManager(PlayerM, EnemyM,PlayerPM);
	ObjectM->SetIM(ItemM);
	ObjectM->SetStage1Texture(MapObj4);
	ObjectM->AddObject(Vector3(2150, 175, 0), ObjectType::ROCK);
	ObjectM->AddObject(Vector3(2400, 5, 0), ObjectType::ROCK, false);
	ObjectM->AddObject(Vector3(7350, 0, 0), Vector3(40 * 4, 30 * 4, 1), ObjectType::ROCK,false);
	ObjectM->AddObject(Vector3(7750, 5, 0), ObjectType::ROCK);
	ObjectM->AddObject(Vector3(8150, 20, 0), ObjectType::ROCK, false);
	ObjectM->AddObject(Vector3(8300, 20, 0),Vector3(64 * 4, 90 * 4, 1), ObjectType::ROCK,false);
	ObjectM->AddBuilding(Vector3(11300, 80, 0), Vector3(150 * 4, 169 *4 , 1),1);
	ObjectM->AddBuilding(Vector3(12200, 80, 0), Vector3(150 * 4, 169 * 4, 1), 2, false);
	//아이템
	ObjectM->AddObject(Vector3(2050, 170, 0), ObjectType::BOX, true);
	ObjectM->AddObject(Vector3(5050, 80, 0), ObjectType::BOX, true);
	LoadGroundTile(L"./GroundData/Stage1.data");
	PlayerM->SetGroundList(GroundList);
	EnemyM->SetGroundList(GroundList);
	EnemyPM->SetGroundList(GroundList);
	PlayerPM->SetGroundList(GroundList);
	PlayerPM->SetOM(ObjectM);
}

void Editer::Update()
{
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		InputGround();
	}
	//충돌 처리
	for (Ground* tempGround : GroundList)
	{
		tempGround->Update();
	}
	//manager
	PlayerPM->Update();
	EnemyPM->Update();
	EnemyM->Update();
	PlayerM->Update(); 
	ObjectM->Update();
	GameM->Update();
	ItemM->Update();
	//animation
	MapGroundWaterDown->Update();
	MapGroundWaterUp->Update();
	MapGroundWaterDown1->Update();
	MapGroundWaterUp1->Update();
	MapBoat->Update();
	MapWaterFall->Update();
	MapWaterFall1->Update();
	MapWaterFall2->Update();
}

void Editer::PreRender()
{
}

void Editer::Render()
{//랜더 순서 명확하게하기
	//player뒤에 출력
	MapBoat->Render();
	MapWaterFall->Render();
	MapBackGround1->Render();
	MapBackGround->Render();
	MapGroundWaterUp1->Render();
	Map->Render();
	MapWaterFall1->Render();
	MapGroundWaterUp->Render();
	MapObj2->Render();
	MapObj3->Render();
	//manager
	EnemyM->Render();
	EnemyPM->Render();
	ObjectM->Render();
	ItemM->Render();
	PlayerM->Render();
	PlayerPM->Render();
	//ground
	//for (Ground* tempGround : GroundList)
	//{
	//	tempGround->Render();
	//}
	//player앞에 출력
	MapObj0->Render();
	MapObj1->Render();
	MapObj4->Render();
	//물
	MapGroundWaterDown1->Render();
	MapGroundWaterDown->Render();
	MapWaterFall2->Render();
}

void Editer::PostRender()
{
	Gui::Get()->GroundGUIS(GroundList, "GroundList");
	static bool bOpen = true;
	if (ImGui::Begin("GroundList", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveGroundTile();

		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadGroundTile();
	}
	ImGui::End();
}

void Editer::InputGround()
{
	GroundList.push_back(new Ground(Vector3(0, 100, 0), Vector3(200 * 4, 100, 1), 0, false));
}

void Editer::SaveGroundTile(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&Editer::SaveGroundTile, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::GroundTileFilter, L"./", func, handle);
	}
	else
	{
		if (GroundList.empty()) return; 
		FileStream* out = new FileStream(String::ToString(path), FILE_STREAM_WRITE);
		
		out->Write(GroundList.size());

		for (Ground* tempground : GroundList)
		{
			out->Write(tempground->GetPos());
			out->Write(tempground->GetSize());
			out->Write(tempground->GetRotation());
			out->Write(tempground->GetisObb());
		}

		SAFE_DELETE(out);
	}
}

void Editer::LoadGroundTile(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&Editer::LoadGroundTile, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::GroundTileFilter, L"./", func, handle);
	}
	else
	{
		cout << String::ToString(path) << endl;
		if (GroundList.empty()) return;
		FileStream* in = new FileStream(String::ToString(path), FILE_STREAM_READ);
		int size = in->Read<UINT>();
		for (int i = 0; i < size - 1; i++)
		{
			InputGround();
		}
		for (Ground* tempground : GroundList)
		{
			tempground->SetPos(in->Read<Vector3>());
			tempground->SetSize(in->Read<Vector3>());
			tempground->SetRotation(in->Read<float>());
			tempground->SetisObb(in->Read<bool>());
			tempground->Load();
		}

		SAFE_DELETE(in);
	}
}



