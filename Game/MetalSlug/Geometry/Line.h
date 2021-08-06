#pragma once



class Line
{
public:
	Line(Vector3 position, float length, float rotation,Color color);//사이즈가 필요없으니 길이로 대체함
	~Line();

	virtual void Update();
	void Render();

	void Rotation(float rotation);


	void SetColor(Color color);

protected:
	//정보
	vector<VertexColor> vertices;
	InputLayout* IL = nullptr;
	//buffer
	VertexBuffer *VB = nullptr;
	//쉐이더
	VertexShader *VS = nullptr;
	PixelShader *PS = nullptr;
	//상수버퍼 크기 회전 이동 관련 행렬
	WorldBuffer*WB=nullptr;
	Matrix world, S, R, T;
	Vector3 position;
	float rotation;
	float length;
	Color color;

	
	ColorBuffer* CB = nullptr;
};