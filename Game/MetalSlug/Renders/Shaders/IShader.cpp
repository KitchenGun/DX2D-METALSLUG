#include "stdafx.h"
#include "IShader.h"

IShader::IShader()
{
}


void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob ** blob)
{//이진데이터를 만드는 함수
	this->path = path;
	this->entryName = entryName;
	this->profile = profile;

	ID3DBlob* error = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),												//파일이름
		nullptr,													//hlsl define 쓰는 부분
		//#include를 hlsl에서 쓸수있도록 하는 옵션
		D3D_COMPILE_STANDARD_FILE_INCLUDE,							//hlsl include 쓰는 부분
		entryName.c_str(),											//랜더링 파이프 라인 진입점에 사용하는 함수 쓰는 부분(진입점 함수 이름)
		profile.c_str(),											//쉐이더 모델 버전 기입
		D3DCOMPILE_ENABLE_STRICTNESS,	//flag 옛 구문 사용 안함		//쉐이더 컴파일 플래그 //특정 동작 수행 여부를 결정하는 것이다
		0,															//효과 컴파일 플래그	//특정 동작 수행 여부를 결정하는 것이다(현재 필요없음 0)
		blob,														//이진 데이터의 집합  -> 컴퓨터가 읽을 수 있는 기계어로 만드는 과정 바이너리라지오브젝트
		&error //에러 추가											//error msg
	);																
	CheckShaderError(hr, error);									//에러가 있으면 확인용
	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob * error)
{
	if (FAILED(hr))
	{
		if (error)
		{
			string str = (const char*)error->GetBufferPointer();	
			MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);	//에러메세지를 메세지 박스(ok버튼이 존재하는)와 같이 띄운다
		}
		ASSERT(false);
	}
}
