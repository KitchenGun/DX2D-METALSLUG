#pragma once
class ScoreUI
{
public:
	ScoreUI(GameManager* gm);
	~ScoreUI();

	void Update();
	void Render();

	void SetPos(Vector3 pos);

	void ScoreChange();

private:
	TextureRect* print0 = nullptr;
	TextureRect* print01 = nullptr;
	TextureRect* score0 = nullptr;
	TextureRect* score1 = nullptr;
	TextureRect* score2 = nullptr;
	TextureRect* score3 = nullptr;
	TextureRect* score4 = nullptr;
	TextureRect* bar = nullptr;
	TextureRect* up = nullptr;

	GameManager* gm = nullptr;
};