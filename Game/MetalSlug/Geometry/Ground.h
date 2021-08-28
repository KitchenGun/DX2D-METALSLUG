#pragma once

class Animator;
class AnimationClip;

struct GroundInfo//Ÿ�� ��ĭ�� ���� ����ü
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
	//gui�۾�
	void GUI(int ordinal);

	//����&�ҷ�����
	void SaveGroundTile(const wstring& path = L"");
	void LoadGroundTile(const wstring& path = L"");

	bool GetisObb() { return isObb; }
private:
	GroundInfo** groundInfo;
	bool isObb = true;
};