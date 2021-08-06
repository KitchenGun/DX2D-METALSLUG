#include "stdafx.h"
#include "ViewFactory.h"

void ViewFactory::GenerateSRV(const wstring & path, ID3D11ShaderResourceView ** srv)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		path.c_str(),
		nullptr,
		nullptr,
		srv,
		nullptr
	);
	ASSERT(hr);
}
