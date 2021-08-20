#pragma once
enum class BULLETTYPE
{
	NONE=0,
	PISTOL,
	HEAVY
};

class Bullet : public Projectile
{
public:
	Bullet(Vector3 position, Vector3 size, float rotation, DIRECTION dir,BULLETTYPE BT);
	~Bullet();
public:
	void Update() override;
	void Render() override;
	void Move(Vector3 position) override;
private:
	BULLETTYPE bt = BULLETTYPE::NONE;
};