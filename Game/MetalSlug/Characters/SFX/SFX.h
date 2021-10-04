#pragma once

enum class SFXTYPE
{
	NONE =0,
	BULLET,
	ENEMYGRENADE
};

class SFX :public AnimationRect
{
public:
	SFX(Vector3 pos, Vector3 size, float rotation, SFXTYPE sfxt);
	~SFX();

	void Update() override;
	void Render() override;

private:
	SFXTYPE SFXT=SFXTYPE::NONE;
	bool isNeedDestroy = false;

};