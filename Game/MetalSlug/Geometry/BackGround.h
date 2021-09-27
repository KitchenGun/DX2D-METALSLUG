#pragma once

enum class BGTYPE
{
	NONE,
	STAGE1BOAT,
	STAGE1WATERFALL,
	STAGE1GROUNDWATERFALL1,
	STAGE1GROUNDWATERFALL2,
	STAGE1WATER0UP,
	STAGE1WATER0DOWN,
	STAGE1WATER1UP,
	STAGE1WATER1DOWN,
	STAGE1WATER2UP,
	STAGE1WATER2DOWN,
	STAGE1BOSSBOTTOM
};

class BackGround : public AnimationRect
{
public:
	BackGround(Vector3 position,Vector3 size,float rotation,BGTYPE bgt);
	~BackGround();
public:
	void Update() override;
	void Render() override;

private:
	void SetClip();
	BGTYPE bgt = BGTYPE::NONE;
};