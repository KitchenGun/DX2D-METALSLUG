#pragma once

class Building :public Object
{
public:
	Building(Vector3 position, Vector3 size, float rotation, int BuildIndex);
	~Building();

	void Update() override;

	void ColliderSizeChange(COLLIDER val);
	void HPCheck();
private:
	bool isNeedDestroy = false;
	int BuildIndex = 0;
};