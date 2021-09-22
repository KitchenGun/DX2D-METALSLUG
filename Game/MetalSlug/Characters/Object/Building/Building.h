#pragma once

class Building :public Object
{
public:
	Building(Vector3 position, Vector3 size, float rotation, int BuildIndex, bool isRender = true);
	~Building();

	void Update() override;

	void ColliderSizeChange(COLLIDER val);
	void HPCheck();

	void SetStage1Texture(TextureRect* val) { Stage1Texture = val; }
private:
	bool isNeedDestroy = false;
	int BuildIndex = 0;

	TextureRect* Stage1Texture = nullptr;
};