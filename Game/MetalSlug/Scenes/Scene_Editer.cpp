#include "stdafx.h"
#include "Scene_Editer.h"

Editer::Editer()
{
}

Editer::~Editer()
{
	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}
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
	//ground
	InputGround();
	
	//manager
	PlayerPM = new ProjectileManager();
	EnemyPM = new ProjectileManager(false);
	EnemyM = new EnemyManager(EnemyPM);
	PlayerM = new PlayerManager(PlayerPM, EnemyM);
	EnemyM->SetPM(PlayerM);
	PlayerPM->SetTargetM(EnemyM);
	EnemyPM->SetTargetM(PlayerM);
	PlayerM->AddPlayer(Vector3(3200 *3, 500, 0));

	EnemyM->AddEnemy(Vector3(600, 500, 0), ENEMYTYPE::Grenadier);

	GameM = new GameManager(PlayerM, EnemyM);
	
	ObjectM = new ObjectManager(PlayerM, EnemyM,PlayerPM);
	ObjectM->AddObject(Vector3(2150, 175, 0), ObjectType::ROCK);
	ObjectM->AddObject(Vector3(2400, 5, 0), ObjectType::ROCK, false);
	ObjectM->AddObject(Vector3(7350, 0, 0), Vector3(40 * 4, 30 * 4, 1), ObjectType::ROCK);
	ObjectM->AddObject(Vector3(7750, 5, 0), ObjectType::ROCK);
	ObjectM->AddObject(Vector3(8150, 20, 0), ObjectType::ROCK, false);
	ObjectM->AddObject(Vector3(8300, 20, 0),Vector3(64 * 4, 90 * 4, 1), ObjectType::ROCK,false);
	ObjectM->AddBuilding(Vector3(11300, 120, 0), Vector3(150 * 4, 169 * 4, 1),1);

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
}

void Editer::PreRender()
{
}

void Editer::Render()
{//랜더 순서 명확하게하기
	//player뒤에 출력
	Map->Render();
	MapObj2->Render();
	//manager
	PlayerPM->Render();
	EnemyPM->Render();
	EnemyM->Render();
	ObjectM->Render();
	PlayerM->Render();
	//ground
	for (Ground* tempGround : GroundList)
	{
		tempGround->Render();
	}
	//player앞에 출력
	MapObj0->Render();
	MapObj1->Render();
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

void Editer::ObjectCollision()
{
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



