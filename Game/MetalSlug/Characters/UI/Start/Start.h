#pragma once
class Start
{
public:
	Start();
	~Start();

	void Update();
	void Render();

	void SetPos(Vector3 pos);
	void Blink();
private:
	bool bIsActive = true;
	
	Vector3 Pos;
	float MaxTime = 0.0f;
	float DeltaTime = 0.0f;
	float count = 0.0f;

	TextureRect* MissionStart = nullptr;
	bool isRender = true;
	bool bInPos = false;
};