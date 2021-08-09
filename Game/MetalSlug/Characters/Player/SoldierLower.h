#pragma once
class SoldierLower : public PlayerAnimationRect
{
public:
	SoldierLower(Vector3 position, Vector3 size, float rotation);
	~SoldierLower();
	void Update() override;
	void Render() override;

public:
	void SetAnimation();
};