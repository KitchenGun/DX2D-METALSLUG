#pragma once

class Animator;
class AnimationClip;

class AnimationRect
{
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation);
	~AnimationRect();

	virtual void Update();
	virtual void Render();

	virtual void Move(Vector3 position);
	Vector3 GetPosition() { return position; }
	RectEdges GetTransformedCoord() { return r; }
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
};