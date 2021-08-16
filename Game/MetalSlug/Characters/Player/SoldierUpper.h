#pragma once

class SoldierUpper : public PlayerAnimationRect//upper
{
public://持失切 社瑚切 update render
	SoldierUpper(Vector3 position, Vector3 size, float rotation);
	~SoldierUpper();
	void Update() override;
	void Render() override;
	void SetClip(string name);
	void PivotUpdate();
public:
	void SetAnimation();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
	void SetPlayer(Player* player) { this->player = player; }
	Animator* GetAnimator() { return animator; }
	void SetisRestart(bool val) { isRestart = val; }
private:
	Player* player;
	bool isRestart = false;
};