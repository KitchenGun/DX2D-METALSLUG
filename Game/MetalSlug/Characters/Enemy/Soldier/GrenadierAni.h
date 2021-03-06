#pragma once
class EnemySoldier;

class GrenadierAni : public PlayerAnimationRect
{
public:
	GrenadierAni(Vector3 position, Vector3 size, float rotation,EnemySoldier* enemy);
	~GrenadierAni();
	void Update() override;
	void Render() override;
	void SetClip();
public:
	void SetAnimation();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
	void SetHit(bool val) { SB->SetHit(val); }
	Animator* GetAnimator() { return animator; }
private:
	void ValueUpdate();
	void PivotUpdate();

private:
	EnemySoldier* enemy;
	DIRECTION dir = DIRECTION::NONE;
	float HitDeltaTime = 0;
	float IMGsize = 3;
};