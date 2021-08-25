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

	ground = new Ground(Vector3(0, 100, 0), Vector3(1000 * 4, 100, 1), 0);
	player = new Player(Vector3(100, 400, 0), Vector3(30*3, 40*3, 1), 0);
	temp = new EnemySoldier(Vector3(400, 200, 0), Vector3(30 * 3, 40 * 3, 1), 0, ENEMYTYPE::Grenadier);

	//manager
	PlayerPM = new ProjectileManager();

	player->SetPM(PlayerPM);
}

void Stage::Update()
{
	player->SetisGround(Math::GroundObbIntersect(player, ground));
	temp->SetisGround(Math::GroundObbIntersect(temp, ground));
	player->Update(); 
	ground->Update();
	temp->Update();

	//manager
	PlayerPM->Update();

	//Camera::Get()->Move(player->GetPosition()-Vector3(200,100,0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{//랜더 순서 명확하게하기
	Map->Render();
	ground->Render();
	temp->Render();

	//manager
	PlayerPM->Render();
	//player
	player->Render();
}

void Stage::PostRender()
{

}


