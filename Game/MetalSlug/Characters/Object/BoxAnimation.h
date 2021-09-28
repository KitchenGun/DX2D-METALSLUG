#pragma once
class ItemBox;
class BoxAnimation :public PlayerAnimationRect
{
public:
	BoxAnimation(Vector3 position, Vector3 size, float rotation,ItemBox* box);
	~BoxAnimation();

	void Update() override;
	void Render() override;

private:
	ItemBox* box=nullptr;
};