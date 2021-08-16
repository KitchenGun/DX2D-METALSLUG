#pragma once

class AnimationClip
{
public:
	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReverse = false);
	~AnimationClip();

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	Vector2 GetKeyframe(UINT index) { return keyframes[index]; }//쌓아둔 키 프레임의 인덱스를 통해서 포지션 정보를 획득
	Vector2 GetTexelFrameSize() { return texelFrameSize; }
	UINT GetFrameCount() { return frameCount; }
	int GetLastFrameIndex() { return keyframes.size()-1; } //마지막 값을 받는 것이다 그렇기 때문에 -1하는 것이다.
	bool GetIsReverse() { return bReverse; }

	wstring GetClipName() { return clipName; }

private:
	wstring clipName = L"";
	vector<Vector2> keyframes;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;

	Vector2 texelFrameSize;

	bool bReverse = false;
};

class Animator
{
public:
	Animator(AnimationClip* animClip);
	Animator(vector<AnimationClip*> animClips);
	~Animator();

	void Update();
	void Render(UINT slotIndex = 0);

	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentAnimClip->GetTexelFrameSize(); }

	void SetIndex(int val) { currentFrameIndex = val; }
	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName, bool Changeblock = false, bool GetCurIndex = false);

	bool isFirstPlay = false;
	bool bLoop = true;
	float playRate = 1.0f / 20.0f;//파일들에 맞춰서 조절해야함 분모가 커지면 더 빠르게 재생이 된다
	bool bStop = false;
private:
	//자료구조 map과 다르게 중복 데이터 허용 안하고 map에 비하여 데이터가 많을때 월등한 탐색능력을 보여줌
	unordered_map<wstring, AnimationClip*> animClips;
	AnimationClip* currentAnimClip = nullptr;

	float deltaTime = 0.0f;
	int currentFrameIndex = 0;
	Vector2 currentFrame = Vector2(0, 0);
	Vector2 TexelFrameSize = Vector2(0, 0);
};