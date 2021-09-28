#pragma once
class ItemManager;
enum class BOXSTATE
{
	NONE=0,
	IDLE,
	DESTROY
};

class ItemBox : public Object
{
public:
	ItemBox(Vector3 position, Vector3 size, float rotation, bool isRender,PROJECTILETYPE pt,ItemManager* IM);
	~ItemBox();

	void Update() override;
	void Render() override;

	void HPCheck();
	void isDestroy();
	void isEat();

	BOXSTATE GetState() { return BState; }
	void ColliderSizeChange(COLLIDER val);
private:
	bool isAddItem = false;
	PROJECTILETYPE PT;
	BOXSTATE BState = BOXSTATE::IDLE;
	BoxAnimation* BAni = nullptr;
	ItemManager* IM;
};