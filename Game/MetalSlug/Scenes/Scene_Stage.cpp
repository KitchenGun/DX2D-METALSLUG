#include "stdafx.h"
#include "Scene_Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	Map = new TextureRect(Vector3(4153*4 / 2, 306 * 4 / 2, 0), Vector3(4153 * 4, 306 *4, 1), 0);
	Map->SetSRV(L"./_Textures/Map/Map.png");

	player = new Player(Vector3(100, 400, 0), Vector3(30*3, 40*3, 1), 0);
	//ground
	ground = new Ground(Vector3(100*4, 100, 0), Vector3(1000 * 4, 100, 1), 40);
	GroundAdd(ground);
	ground = new Ground(Vector3(0, 100, 0), Vector3(100 * 4, 100, 1), 0);
	GroundAdd(ground);
	//manager
	PlayerPM = new ProjectileManager();
	player->SetPM(PlayerPM);

	EnemyM = new EnemyManager();
	EnemyM->SetGroundList(GroundList);
	EnemyM->SetPPM(PlayerPM);
	EnemyM->AddEnemy(Vector3(400, 400, 0), Vector3(30 * 3, 40 * 3, 1), 0, ENEMYTYPE::Grenadier);
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

	//Camera::Get()->Move(player->GetPosition()-Vector3(200,100,0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{//랜더 순서 명확하게하기
	Map->Render();
	for (Ground* tempGround : GroundList)
	{
		tempGround->Render();
	}
	//manager
	PlayerPM->Render();
	//player
	player->Render();
	EnemyM->Render();
}

void Stage::PostRender()
{

}

void Stage::GroundAdd(Ground* ground)
{
	GroundList.push_back(ground);
}


