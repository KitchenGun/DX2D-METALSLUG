#include "stdafx.h"
#include "FilledCircle.h"

FilledCircle::FilledCircle(Vector3 position, Vector3 size, int segments, Color color)
	:position(position),
	size(size),
	segments(segments),
	color(color)

{
	//정점 정보 입력
	vertices.assign(segments+ 1, VertexColor());
	{
		vertices[0].position = Vector3(0, 0, 0);
		for (int i = 0; i < segments; i++)
		{
			float t = 2 * (float)D3DX_PI*i / segments;//각도 구하기
			vertices[i+1].position = Vector3(cosf(t), -sinf(t), 0);
			//sin값 -붙인 이유는 시계방향으로 그리기 위해서이다.
		}
	}
	indices.assign(segments * 3, sizeof(UINT));
	{//012023034....순서를 위해서 만든 for문
		for (int i = 0; i < segments; i++)
		{
			indices[i * 3] = 0;
			indices[i * 3 + 1] = i + 1;
			if (i == segments - 1)//정점 최소화 작업 if문으로 마지막 정점을 기존것을 이용하는 방식
			{
				indices[i * 3 + 2] = 1;
			}
			else
			{
				indices[i * 3 + 2] = i + 2;
			}
		}
	}
	//클래스화 한 객체 생성
	VB = new VertexBuffer();
	IB = new IndexBuffer();
	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	WB = new WorldBuffer();
	CB = new ColorBuffer();
	//객체에서 함수 호출
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);
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

FilledCircle::~FilledCircle()
{
	SAFE_DELETE(CB);

	SAFE_DELETE(WB);

	SAFE_DELETE(IL);

	SAFE_DELETE(PS);
	SAFE_DELETE(VS);
	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void FilledCircle::SetColor(Color color)
{
	this->color = color;
	CB->SetColor(this->color);
}


void FilledCircle::Update()
{
	
}

void FilledCircle::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	//기본 도형 형성 방법 지정
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);
	VS->SetShader();
	PS->SetShader();
	//인덱스 버퍼를 이용해서 그리기
	DC->DrawIndexed(IB->GetCount(),0, 0);
}


