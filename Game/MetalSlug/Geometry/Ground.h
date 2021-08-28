#pragma once

class Animator;
class AnimationClip;

struct GroundInfo//타일 한칸의 정보 구조체
{
	Vector3 pos;
	Vector3 size;
	float rotation;
	bool isObb;
};

class Ground : public PlayerAnimationRect
{
public:

	Ground(Vector3 position, Vector3 size, float rotation,bool isObb);
	~Ground();

	void Update() override;
	void Render() override;
	//gui작업
	void GUI(int ordinal);

	//저장&불러오기
	void SaveGroundTile(const wstring& path = L"");
	void LoadGroundTile(const wstring& path = L"");

	bool GetisObb() { return isObb; }
private:
	GroundInfo** groundInfo;
	bool isObb = true;
};