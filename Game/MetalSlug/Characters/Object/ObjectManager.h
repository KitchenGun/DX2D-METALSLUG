#pragma once

class ObjectManager
{
public:
	ObjectManager(PlayerManager* pm, EnemyManager* em, ProjectileManager* ppm);
	~ObjectManager();

	void Update();
	void Render();

	void PlayerBlock();
	void EnemyBlock();

	void AddObject(Vector3 position,Vector3 size, ObjectType objectType, bool isRender = true);
	void AddObject(Vector3 position, ObjectType objectType, bool isRender = true);
	void AddBuilding(Vector3 position, Vector3 size, int buildIndex,bool isRender=true);
	void RemoveObject(Object* tempO);
	list<Object*> GetObjectList() { return objectList; }
	void SetIM(ItemManager* val) { IM = val; }
	void SetStage1Texture(TextureRect* val) { Stage1Texture = val; }
private:
	list<Object*> objectList;
	list<Object*>::iterator iter;
	PlayerManager* PM=nullptr;
	EnemyManager* EM=nullptr;
	ProjectileManager* PPM=nullptr;
	ItemManager* IM=nullptr;
	TextureRect* Stage1Texture = nullptr;
};