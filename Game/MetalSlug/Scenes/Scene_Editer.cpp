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
	//ground
	InputGround();
	object = new Rock1(Vector3(400, 150, 0), Vector3(64 * 4, 45 * 4, 1), 0);
	//manager
	PlayerPM = new ProjectileManager();
	EnemyPM = new ProjectileManager(false);
	EnemyM = new EnemyManager(EnemyPM);
	PlayerM = new PlayerManager(PlayerPM, EnemyM);
	EnemyM->SetPM(PlayerM);
	PlayerPM->SetTargetM(EnemyM);
	EnemyPM->SetTargetM(PlayerM);
	PlayerM->AddPlayer(Vector3(200, 500, 0));

	EnemyM->AddEnemy(Vector3(600, 500, 0), ENEMYTYPE::Grenadier);

	GameM = new GameManager(PlayerM, EnemyM);

	LoadGroundTile(L"./GroundData/Stage1.data");
	PlayerM->SetGroundList(GroundList);
	EnemyM->SetGroundList(GroundList);
	EnemyPM->SetGroundList(GroundList);
	PlayerPM->SetGroundList(GroundList);
	object->SetTarget(PlayerM);
	object->SetTarget(EnemyM);
}

void Editer::Update()
{
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		InputGround();
	}
	//충돌 처리
	object->Update();

	for (Ground* tempGround : GroundList)
	{
		tempGround->Update();
	}
	//manager
	PlayerPM->Update();
	EnemyPM->Update();
	EnemyM->Update();
	PlayerM->Update(); 

	GameM->Update();
}

void Editer::PreRender()
{
}

void Editer::Render()
{//랜더 순서 명확하게하기

	Map->Render();
	object->Render();
	//manager
	PlayerPM->Render();
	EnemyPM->Render();
	EnemyM->Render();
	PlayerM->Render();
	//ground
	for (Ground* tempGround : GroundList)
	{
		tempGround->Render();
	}
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



