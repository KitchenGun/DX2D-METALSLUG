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

	player = new Player(Vector3(50 * 4, 400, 0), Vector3(30 * 3, 40 * 3, 1), 0);
	//ground
	InputGround();
	//manager
	PlayerPM = new ProjectileManager();
	player->SetPM(PlayerPM);

	EnemyM = new EnemyManager();
	EnemyM->SetGroundList(GroundList);
	EnemyM->SetPPM(PlayerPM);
	EnemyM->AddEnemy(Vector3(400, 400, 0), Vector3(30 * 3, 40 * 3, 1), 0, ENEMYTYPE::Grenadier);
}

void Editer::Update()
{
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		InputGround();
	}
	//이동
	player->SetisGround(Math::GroundIntersect(player, GroundList));
	//player->SetisGround(true);

	player->Update();
	for (Ground* tempGround : GroundList)
	{
		tempGround->Update();
	}
	//manager
	PlayerPM->Update();
	EnemyM->Update();

	Camera::Get()->Move(player->GetPosition() - Vector3(200, 100, 0));
}

void Editer::PreRender()
{
}

void Editer::Render()
{//랜더 순서 명확하게하기

	Map->Render();
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
}

void Editer::InputGround()
{
	GroundList.push_back(new Ground(Vector3(0, 100, 0), Vector3(100 * 4, 100, 1), 0, false));
}




