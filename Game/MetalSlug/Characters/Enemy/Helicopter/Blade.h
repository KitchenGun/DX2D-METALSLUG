#pragma once
class Helicopter;
class Blade : public AnimationRect
{
public:
	Blade(Vector3 position, Vector3 size, float rotation, Helicopter* heli);
	~Blade();

	void Update() override;
	void Render() override;
public:
	void SetClip();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
private:
	Helicopter* Heli=nullptr;
};