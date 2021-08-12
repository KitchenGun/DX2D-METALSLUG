#pragma once
enum class UPPERSTATE
{
	NONE=0,
	IDLE,
	CROUCH,
	LJUMP,
	RJUMP,
	JUMPRUN,
	HandUp
};


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
	void SetLowerAnimRect(SoldierLower* val) { lowerAnimRect = val; }
private:
	Player* player;
	UPPERSTATE upperState=UPPERSTATE::NONE;
	SoldierLower* lowerAnimRect;
};