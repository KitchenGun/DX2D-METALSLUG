#pragma once
class SoldierUpper : public PlayerAnimationRect//upper
{
public://������ �Ҹ��� update render
	SoldierUpper(Vector3 position, Vector3 size, float rotation);
	~SoldierUpper();
	void Update() override;
	void Render() override;

public:
	void SetAnimation();
};