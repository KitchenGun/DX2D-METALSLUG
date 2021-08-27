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

	player = new Player(Vector3(1800*4, 400, 0), Vector3(30*3, 40*3, 1), 0);
	//ground
	SetGround();
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

	Camera::Get()->Move(player->GetPosition()-Vector3(200,100,0));
}

void Stage::PreRender()
{
}

void Stage::Render()
{//���� ���� ��Ȯ�ϰ��ϱ�
	
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

}

void Stage::SetGround()
{
	GroundList.push_back(new Ground(Vector3(0, 100, 0), Vector3(680 * 4, 100, 1), 0, false));
	GroundList.push_back(new Ground(Vector3(670 * 4, 0 * 4, 0), Vector3(1130 * 4, 100, 1), 0, false));
	GroundList.push_back(new Ground(Vector3(1800 * 4, 15 * 4, 0), Vector3(30 * 4, 50, 1), 30, true));
	GroundList.push_back(new Ground(Vector3(1818 * 4, 20 * 4, 0), Vector3(60 * 4, 80, 1), 0, true));
}



