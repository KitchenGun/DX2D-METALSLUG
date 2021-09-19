#pragma once

class Building :public Object
{
public:
	Building(Vector3 position, Vector3 size, float rotation, int BuildIndex);
	~Building();

	void Update() override;

private:
	bool isNeedDestroy = false;
};