#pragma once
class BulletSFX : public SFX
{
public:
	BulletSFX(Vector3 pos, Vector3 size, float rotation, SFXTYPE sfxt,DIRECTION dir);
	~BulletSFX();

	void Update() override;
	void Render() override;

	void SetRotation(float rotation);

	void SetSFX();

private:	   
	DIRECTION dir = DIRECTION::NONE;
	SFXTYPE sfxt;
};