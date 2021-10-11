#pragma once

class Bomb : public Projectile
{
public:
	Bomb(Vector3 position, Vector3 size, float rotation, SFXManager* sfxm, bool bisPPM);
	~Bomb();
public:
	void Update() override;
	void Render() override;
	void Move(Vector3 position) override;

	void Hit();
private:
	HP PHP = 6;
};