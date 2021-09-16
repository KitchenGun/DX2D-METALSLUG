#include "stdafx.h"
#include "Scene_Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	for (Ground* temp : GroundList)
	{
		SAFE_DELETE(temp);
	}
}

void Stage::Init()
{
	Map = new TextureRect(Vector3(4153*4 / 2, 306 * 4 / 2, 0), Vector3(4153 * 4, 306 *4, 1), 0);
	Map->SetSRV(L"./_Textures/Map/Map.png");

	player = new Player(Vector3(3300*4, 400, 0), Vector3(30*3, 40*3, 1), 0);
	//ground
	SetGround();
	//manager
	PlayerPM = new ProjectileManager();
	player->SetPM(PlayerPM);

	EnemyM = new EnemyManager(PlayerPM);
	EnemyM->SetGroundList(GroundList);
	EnemyM->AddEnemy(Vector3(400, 400, 0), ENEMYTYPE::Grenadier);
}

void Stage::Update()
{
	player->SetisGround(Math::GroundIntersect(player, GroundList));
	
	player->Update(); 
	for (Ground* tempGround:GroundList)
	{
		tempGround->Update();
	}
	//manager
	PlayerPM->Update();
	EnemyM->Update();

	Camera::Get()->Move(player->GetPosition()-Vector3(200,100,0));
}

void Stage::PreRender()
{
}

void Stage::Render()
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

void Stage::PostRender()
{
	Gui::Get()->GroundGUIS(GroundList, "TextureRects");
}

void Stage::SetGround()
{

}



