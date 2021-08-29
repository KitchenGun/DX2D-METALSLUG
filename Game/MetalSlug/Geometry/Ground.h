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

	//Load Setting
	void Load()
	{
		//gui에서 변경값을 적용
		D3DXMatrixScaling(&S, size.x, size.y, size.z);
		D3DXMatrixRotationZ(&R, -rotation);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		world = S * R * T;

		WB->SetWorld(world);
		TransformVertices();
	}

	void SetPos(Vector3 val) { position=val; }
	void SetSize(Vector3 val) { size=val; }
	void SetRotation(float val) { rotation=val; }
	void SetisObb(bool val) { isObb=val; }

	Vector3 GetPos() { return position; }
	Vector3 GetSize() { return size; }
	float GetRotation() { return rotation; }
	bool GetisObb() { return isObb; }
private:
	bool isObb = true;
};