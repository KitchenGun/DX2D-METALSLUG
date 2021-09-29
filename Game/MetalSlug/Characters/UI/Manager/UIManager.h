#pragma once

class UIManager
{
public:
	UIManager(PlayerManager* pm);
	~UIManager();

	void Update();
	void Render();

private:
	AmmoUI* ammoUI;
	PlayerManager* pm = nullptr;
};