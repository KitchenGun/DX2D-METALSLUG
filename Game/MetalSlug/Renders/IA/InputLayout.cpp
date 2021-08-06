#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * desc, const UINT & count, ID3DBlob * blob)
{
	if (!desc || !count || !blob)//매개변수가 모두있는지 체크
	{
		assert(false);
	}
	HRESULT hr = DEVICE->CreateInputLayout 
	(
		desc,							//VertexType에서 만든 desc를 가지고 만듬
		count,							//입력 데이터 항목수
		blob->GetBufferPointer(),		//이진데이터
		blob->GetBufferSize(),			//이진데이터 크기
		&inputLayout					//결과물 넣을 포인터 객체
	);
	ASSERT(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout);
}

