#pragma once
class AmmoUI
{
public:
	AmmoUI(PlayerManager* pm);
	~AmmoUI();

	void Update();
	void Render();

	void SetPos(Vector3 pos);

	void AmmoNumChange();
	void BombNumChange();

private:
	TextureRect* ammo0 = nullptr;
	TextureRect* ammo1 = nullptr;
	TextureRect* ammo2 = nullptr;

	TextureRect* MainUI = nullptr;

	TextureRect* bomb0 = nullptr;
	TextureRect* bomb1 = nullptr;

	PlayerManager* pm = nullptr;
};