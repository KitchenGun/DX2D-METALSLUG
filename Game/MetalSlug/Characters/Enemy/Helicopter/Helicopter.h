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
	void DropBomb();
	void AddBomb();
	void HPCheck();
	void Die() override;

	void AltitudeHold();
	void PlayerPosTracking();
	void SetPos(Vector3 tempPos);
	void SetClip(); 
	Vector3 GetPos() { return position; }
	HELISTATE GetState() { return HeliState; }
private:
	Blade* blade = nullptr;
	HELISTATE HeliState = HELISTATE::NONE;
	bool isEngage = false;
	bool isAtk = false;
	float AtkRate = 2.0f;
	float DropRate = 0.3f;
	float Altitude = 0;
	SPEED speed = 0.0f;
};