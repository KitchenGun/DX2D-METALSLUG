#include "stdafx.h"
#include "AnimationRect.h"
#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation)
	:position(position),
	size(size),
	rotation(rotation)
{
	/*사각형 정점 인덱스 별 위치
	13
	02
	*/
	//local 좌표 입력
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[0].uv = Vector2(0.0f, 1.0f);

	vertices[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[1].uv = Vector2(0.0f, 0.0f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
	vertices[2].uv = Vector2(1.0f, 1.0f);

	vertices[3].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[3].uv = Vector2(1.0f, 0.0f);
	//인덱스 버퍼
	//다시한번 기억하자 시계방향으로 그린다
	indices = { 0, 1, 2, 2, 1, 3 };

	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);
	//hlsl 파일 설정
	wstring shaderPath = L"./_Shaders/Animation.hlsl";
	VS->Create(shaderPath, "VS");
	PS->Create(shaderPath, "PS");

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());
	//공간 변환
	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);
	
	//Create BlnedState//현재는 기능이 없음
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.AlphaToCoverageEnable = false;//3d사용되는 기능
		desc.IndependentBlendEnable = false;
		//독립적으로 블랜드 가능 지금 당장은 false로 설정하면 RenderTarget 0번의 설정값을 모든 타겟에 적용한다 라는 뜻이다
		desc.RenderTarget[0].BlendEnable = true;
		//모든 곳에서 blend적용하겠다.
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;//넣어준 소스의 알파값으로 변경  
		//기본값이 1임 그래서 png파일을 넣을때 투명부분이 검은색으로 나옴
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//넣어준 소스의 알파를 반전한 값 
		//기본값이 0임 
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		//색상결정에 대한 계산식 float4 color =(src*srcblend) Blend op (des*destblend)
		HRESULT hr = DEVICE->CreateBlendState(&desc, &BS);
		ASSERT(hr);
		TransformVertices();
	}
	//Create SamplerState//텍스쳐를 uv에 맞게 바꾸는 과정
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
		//D3D11_TEXTURE_ADDRESS_CLAMP = [0.0, 1.0] 범위를 벗어난 텍스처 좌표는 각각 0.0 또는 1.0의 텍스처 색상으로 설정됩니다.
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		//linear 선형 보간 하겠다는 이야기임 평균값을 섞는다		비용이 비싸고 질이 좋다
		//POINT 겹치는 픽셀이 있으면 하나를 폐기한다는 이야기다		비용이 싸지만 질이 안좋다
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//축소, 확대 및 밉 레벨 샘플링에 포인트 샘플링을 사용합니다.
		desc.MaxAnisotropy = 16;
		desc.MinLOD = numeric_limits<float>::min();
		desc.MaxLOD = numeric_limits<float>::max();
		desc.MipLODBias = 0.0f;						//카메라에서 멀어질수록 흐리멍텅하게 보이도록 렌더링하는것 2d 의미 없음

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &SS);
		ASSERT(hr);
	}
}

AnimationRect::~AnimationRect()
{
	SAFE_RELEASE(SS);
	SAFE_RELEASE(BS);

	SAFE_DELETE(animator);

	SAFE_DELETE(WB);

	SAFE_DELETE(IL);

	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void AnimationRect::Update()
{
	animator->Update();

	right = Vector3((int)R._11, (int)R._12, (int)R._13);
	up = Vector3((int)R._21, (int)R._22, (int)R._23);

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		//gpu에 접근해서 uv좌표 변경 
		//텍셀에 접근하면 uv 값을 알 수 있음  삼각형 2개로 사각형이 이루어져있음을 기억하자
		//좌하단
		vertices[0].uv = Vector2(animator->GetCurrentFrame().x, animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y);
		//좌상단
		vertices[1].uv = animator->GetCurrentFrame();
		//우하단
		vertices[2].uv = animator->GetCurrentFrame() + animator->GetTexelFrameSize();
		//우상단
		vertices[3].uv = Vector2(animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x, animator->GetCurrentFrame().y);

		memcpy(subResource.pData, vertices.data(), sizeof(VertexTexture) * vertices.size());
		/*
			cout <<" X:" << animator->GetCurrentFrame().x<<" Y:"<< animator->GetCurrentFrame().y << endl;
			를 통해서 uv 값의 변화
			정방향일때 uv = 0 반대 일때 uv = 0.5
			x값은 0~1사이로 계속 변화함
			animator->GetTexelFrameSize() == 출력할 이미지 한장당 클래스의 변화 비율을 가지고 있음 ex)0.1이런식의 값을 가지고 있음
		*/
	}
	DC->Unmap(VB->GetResource(), 0);
}

void AnimationRect::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VS->SetShader();
	WB->SetVSBuffer(0);
	
	{
		ID3D11ShaderResourceView* srv = texture->GetSRV();
		DC->PSSetShaderResources(0, 1, &srv);
	}

	PS->SetShader();
	DC->PSSetSamplers(0, 1, &SS);
	/////////////수정 부분 blendstate를 추가하여 투명 부분을 자연스럽게 변경
	DC->OMSetBlendState(BS, nullptr, 0xFFFFFFF);
	DC->DrawIndexed(IB->GetCount(), 0, 0);
}

void AnimationRect::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);
	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void AnimationRect::Rotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(this->rotation));

	world = S * R * T;
	WB->SetWorld(world);
	TransformVertices();
}

void AnimationRect::TransformVertices()
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
	D3DXVec3TransformCoord//정점 이동
	(
		&r.Point,
		&(vertices[0].position + Vector3(0.5f, 0.5f, 0)),
		&world
	);
}
