#pragma once
class BulletSFX : public SFX
{
public:
	BulletSFX(Vector3 pos, SFXTYPE sfxt, DIRECTION dir, bool loop = false);
	~BulletSFX();

	void Update() override;
	void Render() override;

	void SetRotation(float rotation);

	void SetSFX();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
private:	   
	DIRECTION dir = DIRECTION::NONE;
	SFXTYPE sfxt;
};