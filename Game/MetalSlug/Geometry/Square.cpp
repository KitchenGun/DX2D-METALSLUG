#include "stdafx.h"
#include "Square.h"

Square::Square(Vector3 position, Vector3 size, float rotation,Color color)
	:position(position),
	size(size),
	rotation(rotation),
	color(color)
{
	//정점 정보 입력
	vertices.assign(4, VertexColor());
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	//vertices[0].color =Red;

	vertices[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	//vertices[1].color =Red;
	
	vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
	//vertices[2].color =Red;
	
	vertices[3].position = Vector3(0.5f, 0.5f, 0.0f);
	//vertices[3].color =Red;

	indices = { 0,1,2,2,1,3 };
	
	//클래스화 한 객체 생성
	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	WB = new WorldBuffer();
	CB = new ColorBuffer();
	SetColor(color);
	//객체에서 함수 호출
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);
	
	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);
	TransformVertices();


}

Square::~Square()
{
	SAFE_DELETE(CB);
	
	SAFE_DELETE(WB);
	
	SAFE_DELETE(IL);
	
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void Square::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
	TransformVertices();
}

void Square::Update()
{
	/*//버텍스 버퍼를 갱신
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map
	(
		VB->GetResource(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subResource
	);
	//색상변환  //이제 이렇게 할 필요없음 color 버퍼가 있기 때문에 랜더링 파이프 라인으로 바로 꼽아줄수있다.
	//for (VertexColor&v : vertices)
	//{
	//	v.color = Red;
	//}
	//버퍼내 정점 저장
	//객체의 pData 멤버는 버퍼내 데이터의 시작에 대한 포인터입니다.
	memcpy(subResource.pData, vertices.data(), sizeof(VertexColor)*vertices.size());
	DC->Unmap(VB->GetResource(), 0);
	*/
}

void Square::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	//기본 도형 형성 방법 지정
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	WB->SetVSBuffer(0);
	//색상 지정
	CB->SetVSBuffer(2);
	
	VS->SetShader();
	PS->SetShader();
	//인덱스 버퍼를 이용해서 그리기
	DC->DrawIndexed(IB->GetCount(), 0, 0);
}

void Square::SetColor(Color color)
{
	this->color = color;
	//버퍼에 넣어줘야함
	CB->SetColor(color);
}

void Square::TransformVertices()
{
	//D3DXVec3TransformNormal() //벡터 이동   //지정된 행렬에 의해 3D 벡터 법선을 변환 한다.
	D3DXVec3TransformCoord//정점 이동   //충돌을 체크하기 위한 좌표저장
	(//지정된 행렬에 의해 3D 벡터를 변환 해, 그 결과를 w = 1 에 투영 한다.
		&r.LT,						//반환할곳
		&vertices[1].position,		//처리의 기본 정점정보
		&world						//처리의 기본 매트릭스 정보
	);
	D3DXVec3TransformCoord//정점 이동
	(
		&r.RB,
		&vertices[2].position,
		&world
	);
}
