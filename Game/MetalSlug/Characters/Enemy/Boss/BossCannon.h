#pragma once
class Boss;

class BossCannon : public PlayerAnimationRect
{
public:
	BossCannon(Vector3 Position,Vector3 Size,Boss* boss);
	~BossCannon();

	void Update() override;
	void Render() override;
	void SetClip();
public:
	void SetAnimation();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
	Animator* GetAnimator() { return animator; }
private:
	void PivotUpdate();
	Boss* boss;
	DIRECTION dir = DIRECTION::NONE;
	float IMGsize = 3;
};