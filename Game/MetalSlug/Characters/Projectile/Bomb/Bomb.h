#pragma once

class Bomb : public Projectile
{
public:
	Bomb(Vector3 position, Vector3 size, float rotation, DIRECTION dir, PROJECTILETYPE BT, bool bisPPM = false);
	~Bomb();
public:
	void Update() override;
	void Render() override;
	void Move(Vector3 position) override;
private:
};