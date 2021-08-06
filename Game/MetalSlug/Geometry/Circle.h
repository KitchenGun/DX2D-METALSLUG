#pragma once

class Circle
{
public:
	Circle(Vector3 position, Vector3 size, int segments, Color color);
	~Circle();

	void SetColor(Color color);

	void Update();
	void Render();


private:
	//정보
	vector<VertexColor> vertices;
	InputLayout* IL = nullptr;
	//buffer
	VertexBuffer *VB = nullptr;
	//쉐이더
	VertexShader *VS = nullptr;
	PixelShader *PS = nullptr;
	//상수버퍼 크기 회전 이동 관련 행렬
	ColorBuffer* CB = nullptr;
	WorldBuffer*WB = nullptr;
	Matrix world, S, T;
	Vector3 position, size;
	Color color;
	int segments;

	bool bIntersect = false;


};