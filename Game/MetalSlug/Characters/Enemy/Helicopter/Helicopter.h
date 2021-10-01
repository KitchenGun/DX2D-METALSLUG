#pragma once
enum class HELISTATE
{
	NONE = 0,
	LEFTMOVE,
	RIGHTMOVE
};

class Helicopter:public Enemy
{
public:
	Helicopter(Vector3 position, Vector3 size, float altitude);
	~Helicopter();

	void Update() override;
	void Render() override;

	void SetClip(); 
	Vector3 GetPos() { return position; }
	HELISTATE GetState() { return HeliState; }
private:
	Blade* blade = nullptr;
	HELISTATE HeliState = HELISTATE::NONE;
};