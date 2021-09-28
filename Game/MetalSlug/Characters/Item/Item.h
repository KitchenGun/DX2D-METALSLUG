#pragma once
class Item :public AnimationRect
{
public:
	Item(Vector3 position,Vector3 size,PROJECTILETYPE pt,PlayerManager* pm);
	~Item();
	
	void Update() override;
	void Render() override;

	void Take();


	bool GetisTake() { return isTake; }
private:
	PROJECTILETYPE pt = PROJECTILETYPE::NONE;
	PlayerManager* pm;
	bool isTake = false;
};