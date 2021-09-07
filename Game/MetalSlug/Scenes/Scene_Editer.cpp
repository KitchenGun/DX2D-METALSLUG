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

	player = new Player(Vector3(50 * 4, 500, 0), Vector3(30 * 3, 40 * 3, 1), 0);
	//ground
	InputGround();
	object = new Rock1(Vector3(300, 150, 0), Vector3(64 * 4, 45 * 4, 1), 0);
	object->SetTarget(player);
	//manager
	PlayerPM = new ProjectileManager();
	player->SetPM(PlayerPM);

	EnemyM = new EnemyManager();
	EnemyM->SetGroundList(GroundList);
	EnemyM->SetPPM(PlayerPM);
	EnemyM->AddEnemy(Vector3(200, 400, 0), Vector3(30 * 3, 40 * 3, 1), 0, ENEMYTYPE::Grenadier);
	player->SetEM(EnemyM);
	//Camera::Get()->Move(player->GetPosition() - Vector3(200, 400, 0));
}

void Editer::Update()
{
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		InputGround();
	}
	//충돌 처리
	if (!player->GetisJump())
	{
		//player->SetisGround(false);
		player->SetisGround(Math::GroundIntersect(player, GroundList));
	}
	object->Update();

	player->Update();
	for (Ground* tempGround : GroundList)
	{
		tempGround->Update();
	}
	//manager
	PlayerPM->Update();
	EnemyM->Update();

	//Camera::Get()->Move(player->GetPosition() - Vector3(200, 100, 0));
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
	EnemyM->Render();
	//player
	player->Render();
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



