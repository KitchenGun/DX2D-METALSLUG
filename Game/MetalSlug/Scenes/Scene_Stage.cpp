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

	ground = new Ground(Vector3(0,100,0),Vector3(1000*4,100,1),0);
	player = new Player(Vector3(100, 200, 0), Vector3(3, 3, 1), 0);
	temp = new EnemySoldier(Vector3(400, 200, 0), Vector3(3, 3, 1), 0, ENEMYTYPE::Grenadier);
}

void Stage::Update()
{
	player->SetisGround(Math::Intersect(player, ground));
	player->Update(); 
	ground->Update();
	temp->Update();
	//Camera::Get()->Move(player->GetPosition()-Vector3(200,100,0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{//랜더 순서 명확하게하기
	Map->Render();
	player->Render();
	ground->Render();
	temp->Render();
}

void Stage::PostRender()
{

}


