#pragma once

class Object:public PlayerAnimationRect
{
public:
	Object(Vector3 position, Vector3 size, float rotation);
	virtual ~Object() override;

	void Update() override;
	void Render() override;

	void PlayerBlock();

	void SetTarget(Player* val) { target = val; }
private:
	Player* target;
};