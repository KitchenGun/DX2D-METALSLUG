#pragma once

class Building :public Object
{
public:
	Building(Vector3 position, Vector3 size, float rotation, int BuildIndex, bool isRender = true, TextureRect* Stage1Texture=nullptr);
	~Building();

	void Update() override;

	void ColliderSizeChange(COLLIDER val);
	void HPCheck();

	void SetStage1Texture(TextureRect* val) { Stage1Texture = val; }
	HP GetHP() { return ObjHP; }

	int GetBuilding = 0;
private:
	bool isNeedDestroy = false;
	int BuildIndex = 0;
	TextureRect* Stage1Texture = nullptr;
};