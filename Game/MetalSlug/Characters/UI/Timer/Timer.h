#pragma once

class Timer
{
public:
	Timer(PlayerManager* pm);
	~Timer();

	void Update();
	void Render();

	void SetPos(Vector3 pos);

	void TimerChange();
	void Blink();

private:
	TextureRect* subUI = nullptr;

	TextureRect* timer0 = nullptr;
	TextureRect* timer1 = nullptr;

	bool isRender = true;
	float timer = 60.0f;
	PlayerManager* pm = nullptr;
};