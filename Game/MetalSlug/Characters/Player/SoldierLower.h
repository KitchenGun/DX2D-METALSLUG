#pragma once
class Player;

enum class LOWERSTATE
{
	NONE=0,
	IDLE,
	MOVE,
	JUMP,
	JUMPMOVE
};

class SoldierLower : public PlayerAnimationRect
{
public:
	SoldierLower(Vector3 position, Vector3 size, float rotation);
	~SoldierLower();
	void Update() override;
	void Render() override;
	void SetClip(string name);
public:
	void SetAnimation();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
	void SetPlayer(Player* player) { this->player = player; }
private:
	Player* player;
	LOWERSTATE lowerState;
};