#pragma once

class Animator;
class AnimationClip;

class PlayerAnimationRect
{
public:
	PlayerAnimationRect(Vector3 position, Vector3 size, float rotation);
	~PlayerAnimationRect();

	virtual void Update();
	virtual void Render();

	virtual void Move(Vector3 position);
	void Rotation(float rotation);

	Vector3 GetPosition() { return position; }
	RectEdges GetTransformedCoord() { return r; }

	Matrix GetSMatrix() { return S; }
	Matrix GetRMatrix() { return R; }
	Matrix GetTMatrix() { return T; }

	Vector3 GetPointPos() {return position + Vector3(size.x/ 2,size.y/2,0); }
	Vector3 GetScale() { return size; }
	Vector3 Right() { return right; }
	Vector3 Up() { return up; }
protected:
	Animator* animator = nullptr;
	vector<AnimationClip*> animClips;
	Texture2D* texture = nullptr;
protected:
	vector<VertexTexture> vertices;
	vector<UINT> indices;
	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;
	Matrix world, S, R, T;
	Vector3 position, size;
	float rotation;

	ID3D11BlendState* BS;
	ID3D11SamplerState* SS;
	//충돌처리
	void TransformVertices();
	RectEdges r;


	Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
};