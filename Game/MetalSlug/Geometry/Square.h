#pragma once


struct RectEdges //모서리 좌표
{
	Vector3 LT;
	Vector3 RB;
	Vector3 Point;
};

class Square
{
public:
	Square(Vector3 position, Vector3 size, float rotation,Color color);
	~Square();

	void Move(Vector3 position);

	void Update();
	void Render();

	void SetColor(Color color);
	RectEdges GetTransformedCoord() { return r; }

	void SetIntersect(bool bIntersect) { this->bIntersect = bIntersect; }

private:
	void TransformVertices();
	//정보
	vector<VertexColor> vertices;
	vector<UINT> indices;
	InputLayout* IL = nullptr;
	//buffer
	VertexBuffer *VB = nullptr;
	IndexBuffer *IB = nullptr;
	//쉐이더
	VertexShader *VS = nullptr;
	PixelShader *PS = nullptr;
	//상수버퍼 크기 회전 이동 관련 행렬
	WorldBuffer*WB=nullptr;
	Matrix world, S, R, T;
	Vector3 position, size;
	float rotation;
	Color color;
	
	RectEdges r;
	ColorBuffer* CB = nullptr;
	bool bIntersect = false;


};