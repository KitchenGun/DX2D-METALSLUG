#pragma once

class UIManager
{
public:
	UIManager(PlayerManager* pm, GameManager* gm);
	~UIManager();

	void Update();
	void Render();

private:
	AmmoUI* ammoUI=nullptr;
	ScoreUI* scoreUI=nullptr;
	Timer* timer = nullptr;
	PlayerManager* pm = nullptr;
	GameManager* gm = nullptr;
};