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

	virtual void Update() override;
	virtual void Render() override;

	bool GetIsNeedDestroy() { return isNeedDestroy; }
protected:
	SFXTYPE SFXT=SFXTYPE::NONE;
	bool isNeedDestroy = false;

};