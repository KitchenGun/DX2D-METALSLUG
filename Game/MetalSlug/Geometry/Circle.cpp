#include "stdafx.h"
#include "Circle.h"

Circle::Circle(Vector3 position, Vector3 size, int segments, Color color)
	:position(position),
	size(size),
	segments(segments),
	color(color)

{
	//정점 정보 입력
	vertices.assign(segments + 1, VertexColor());
	{
		for (int i = 0; i <= segments; ++i)
		{
			float t = 2 * (float)D3DX_PI*i / segments;//각도 구하기
			
			vertices[i].position = Vector3(cosf(t), -sinf(t), 0); //cosf은 반환이 float 값 cos은 double

		}
	}

	//클래스화 한 객체 생성
	VB = new VertexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	WB = new WorldBuffer();
	CB = new ColorBuffer();
	//객체에서 함수 호출
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;

	WB->SetWorld(world);
	SetColor(color);

}

Circle::~Circle()
{
	SAFE_DELETE(CB);

	SAFE_DELETE(WB);

	SAFE_DELETE(IL);

	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(VB);
}

void Circle::SetColor(Color color)
{
	this->color = color;
	CB->SetColor(this->color);
}


void Circle::Update()
{
	
}

void Circle::Render()
{
	VB->SetIA();
	IL->SetIA();
	//기본 도형 형성 방법 지정
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);
	VS->SetShader();
	PS->SetShader();
	//인덱스 버퍼를 이용해서 그리기
	DC->Draw(segments+1, 0);
}


