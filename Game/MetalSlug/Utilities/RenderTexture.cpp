#include "stdafx.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
}

RenderTexture::~RenderTexture()
{
	SAFE_RELEASE(shaderResourceView);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(renderTargetTexture);
}

void RenderTexture::Initialize()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	HRESULT hr;

	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	textureDesc.Width = WinMaxWidth;
	textureDesc.Height = WinMaxHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &renderTargetTexture);//texture2d 자원 만듬
	ASSERT(hr);
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	//렌더링 파이프라인의 출력을 받을 자원을 연결하는 데 쓰인다. 
	hr = DEVICE->CreateRenderTargetView(renderTargetTexture, &renderTargetViewDesc,&renderTargetView);//renderTargetTexture가지고 rtv 만드는 중
	ASSERT(hr);

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	//파이프라인의 프로그램 가능 셰이더 단계가 자원을 읽을 수 있게 한다. 이 뷰는 예전에 픽셀 셰이더에서 텍스처가 하던 역할, 
	//즉 셰이더 프로그램 안에서 읽고 사용할 수는 있지만 기록하지는 못하는 자료에 해당하는 것이다. 
	hr = DEVICE->CreateShaderResourceView(renderTargetTexture, &shaderResourceViewDesc, &shaderResourceView);
	ASSERT(hr);

}


void RenderTexture::RenderToTexture()//Begin과 동일한 과정을 밟음
{
	DC->OMSetRenderTargets(1, &renderTargetView, nullptr);
	//매개변수1.설정하는 렌더타겟의 개수.최대 8개까지 설정가능하다.
	//매개변수2.렌더링 파이프라인에 설정하는 렌더타겟 뷰의 배열. NULL을 넘기면, 렌더타겟이 설정되지 않게 된다.
	//매개변수3.렌더링 파이프라인에 넘겨주는 깊이 / 스텐실 뷰의 포인터. NULL을 넘기면, 깊이 / 스텐실 버퍼가 설정되지 않게 된다.

	DC->ClearRenderTargetView(renderTargetView, Graphics::Get()->GetClearColor());
	//화면을 깨끗히 지우라는 명령하는 함수
	//매개변수1.렌더링 대상에 대한 포인터입니다.
}

void RenderTexture::SaveTexture(const wstring & path)
{
	HRESULT hr = D3DX11SaveTextureToFile
	(
		DC,							
		renderTargetTexture,		//저장 질감의 포인터  //현재 그려져있는 rtv
		D3DX11_IFF_PNG,				//저장 형식
		path.c_str()				//저장 위치
	);
	ASSERT(hr);
}
