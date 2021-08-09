#pragma once
class SoldierUpper : public PlayerAnimationRect//upper
{
public://持失切 社瑚切 update render
	SoldierUpper(Vector3 position, Vector3 size, float rotation);
	~SoldierUpper();
	void Update() override;
	void Render() override;

public:
	void SetAnimation();
};