#include "stdafx.h"
#include "Line.h"

Line::Line(Vector3 position, float length, float rotation,Color color)
	:position(position),
	length(length),
	rotation(rotation),
	color(color)
{
	//정점 정보 입력
	vertices.assign(4, VertexColor());
	vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	//vertices[0].color =Red;

	vertices[1].position = Vector3(1.0f, 0.0f, 0.0f);
	//vertices[1].color =Red;
	
	//클래스화 한 객체 생성
	VB = new VertexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	WB = new WorldBuffer();
	CB = new ColorBuffer();
	SetColor(color);
	//객체에서 함수 호출
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	
	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	//행렬 곱을 생각하여서 y z의 0이 아닌 다른것을 넣어도 0이 됨으로 0을 넣는다
	D3DXMatrixScaling(&S, length, 0 , 0);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);


}

Line::~Line()
{
	SAFE_DELETE(CB);
	
	SAFE_DELETE(WB);
	
	SAFE_DELETE(IL);
	
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(VB);
}



void Line::Update()
{
	
}

void Line::Render()
{
	VB->SetIA();
	IL->SetIA();
	//기본 도형 형성 방법 지정
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	
	WB->SetVSBuffer(0);
	//색상 지정
	CB->SetVSBuffer(2);
	
	VS->SetShader();
	PS->SetShader();
	//인덱스 버퍼를 이용해서 그리기
	DC->Draw(VB->GetCount(), 0);
}

void Line::Rotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R,(float)D3DXToRadian(this->rotation));

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
}

void Line::SetColor(Color color)
{
	this->color = color;
	//버퍼에 넣어줘야함
	CB->SetColor(color);
}
