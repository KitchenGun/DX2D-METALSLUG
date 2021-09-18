#pragma once
#pragma once
enum class ObjectType
{
	NONE = 0,
	ROCK,
	BOX,
	POW
};

class ObjectManager
{
public:
	ObjectManager(PlayerManager* pm, EnemyManager* em, ProjectileManager* ppm);
	~ObjectManager();

	void Update();
	void Render();

	void PlayerBlock();
	void EnemyBlock();

	void AddObject(Vector3 position, ObjectType objectType);
	void RemoveObject(Object* tempO);
	list<Object*> GetObjectList() { return objectList; }
private:
	list<Object*> objectList;
	list<Object*>::iterator iter;
	PlayerManager* PM;
	EnemyManager* EM;
	ProjectileManager* PPM;
};