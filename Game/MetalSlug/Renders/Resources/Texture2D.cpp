#include "stdafx.h"
#include "Texture2D.h"

using namespace DirectX;

vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath, D3DX11_IMAGE_LOAD_INFO * loadInfo)
	: filePath(filePath)
{
	//경로만 전달하고 load 함수실행
	Textures::Load(this, loadInfo);
}

Texture2D::~Texture2D()
{
}

D3D11_TEXTURE2D_DESC Texture2D::ReadPixel(DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels)
{
	ID3D11Texture2D* srcTexture;
	view->GetResource((ID3D11Resource**)&srcTexture);
	//src를 만들어서 오버로딩 함수에 넘김
	return ReadPixel(srcTexture, readFormat, pixels);
}

D3D11_TEXTURE2D_DESC Texture2D::ReadPixel(ID3D11Texture2D * src, DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	src->GetDesc(&srcDesc);
	//texture2d desc 제작 
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = srcDesc.Width;
	desc.Height = srcDesc.Height;
	desc.MipLevels = 1;									//멑티샘플링된 텍스쳐를 사용하겠다.
	desc.ArraySize = 1;									//텍스쳐 배열의 텍스처 수
	desc.Format = readFormat;
	desc.SampleDesc = srcDesc.SampleDesc;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;					//cpu읽고 쓰기 gpu읽고 쓰기 허용

	ID3D11Texture2D* texture;
	ASSERT(DEVICE->CreateTexture2D(&desc, nullptr, &texture));//2d 텍스쳐 자원 만들고
	ASSERT(D3DX11LoadTextureFromTexture(DC, src, nullptr, texture));//텍스쳐를 전달하는 것 같음
	UINT* colors = new UINT[desc.Width * desc.Height];
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(texture, 0, D3D11_MAP_READ, NULL, &subResource);
	{//gpu메모리 접근
		memcpy(colors, subResource.pData, sizeof(UINT) * desc.Width * desc.Height);
	}
	DC->Unmap(texture, 0);

	//뭐하는 건지 모르겠음

	for (UINT y = 0; y < desc.Height; y++)
	{
		for (UINT x = 0; x < desc.Width; x++)
		{
			UINT index = desc.Width * y + x;

			float f = 1.0f / 255.0f;

			float b = f * (float)((0x000000FF & colors[index]) >> 0);
			float g = f * (float)((0x0000FF00 & colors[index]) >> 8);
			float r = f * (float)((0x00FF0000 & colors[index]) >> 16);
			float a = f * (float)((0xFF000000 & colors[index]) >> 24);

			pixels->push_back(D3DXCOLOR(r, g, b, a));
		}
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(texture);

	return desc;
}

void Texture2D::SaveFile(wstring filePath)
{
	ID3D11Texture2D* srcTexture;
	view->GetResource((ID3D11Resource**)&srcTexture);

	SaveFile(filePath, srcTexture);
}

void Texture2D::SaveFile(wstring filePath, ID3D11Texture2D * originalTex, vector<D3DXCOLOR>& pixels, UINT width, UINT height)
{
	view->GetResource((ID3D11Resource**)&originalTex);
	D3D11_TEXTURE2D_DESC originalDesc;
	originalTex->GetDesc(&originalDesc);
	//srv의 저장된 정보를 포인터를 사용해서 바꾸는것? 
	ID3D11Texture2D* srcTexture;
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Width = width;
	destDesc.Height = height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = originalDesc.Format;
	destDesc.SampleDesc = originalDesc.SampleDesc;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	destDesc.Usage = D3D11_USAGE_STAGING;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &srcTexture);
	ASSERT(hr);
	//뭐하는 건지 모르겠음
	UINT* rawPixels = new UINT[width * height];
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			UINT index = width * y + x;

			rawPixels[index] = pixels[index];
		}
	}
	//cpu gpu모두 엑세스 가능이기에 gpu 엑세스
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(srcTexture, 0, D3D11_MAP_WRITE, NULL, &subResource);
	{
		memcpy(subResource.pData, rawPixels, sizeof(UINT) * width * height);
	}
	DC->Unmap(srcTexture, 0);

	SAFE_DELETE_ARRAY(rawPixels);

	SaveFile(filePath, srcTexture);
}

void Texture2D::SaveFile(wstring file, ID3D11Texture2D * src)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	src->GetDesc(&srcDesc);

	ID3D11Texture2D* dest;
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	destDesc.SampleDesc = srcDesc.SampleDesc;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	destDesc.Usage = D3D11_USAGE_STAGING;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &dest);
	ASSERT(hr);
	//dest 텍스쳐를 만들고 src로 복사?
	hr = D3DX11LoadTextureFromTexture(DC, src, nullptr, dest);
	ASSERT(hr);

	wstring ext = Path::GetExtension(file);
	transform(ext.begin(), ext.end(), ext.begin(), toupper);

	if (ext == L"BMP")
		hr = D3DX11SaveTextureToFile(DC, dest, D3DX11_IFF_BMP, file.c_str());
	else
		hr = D3DX11SaveTextureToFile(DC, dest, D3DX11_IFF_PNG, file.c_str());

	ASSERT(hr);

	SAFE_RELEASE(dest);

}

ID3D11Texture2D * Texture2D::GetTexture()
{

	ID3D11Texture2D* texture;
	//텍스쳐 리소스를 건내줌
	view->GetResource((ID3D11Resource**)&texture);
	return texture;
}

void Textures::Create()
{
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
	{//안에 들어있는 텍스쳐 삭제
		SAFE_RELEASE(desc.view);
	}
}

void Textures::Load(Texture2D * texture, D3DX11_IMAGE_LOAD_INFO * loadInfo)
{
	HRESULT hr;

	TexMetadata metaData;
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")//텍스쳐(이미지) 파일 형식 마다 처리방식이 조금씩 다름 메타 데이터에 desc에 사용될 정보를 넣음
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		ASSERT(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		ASSERT(hr);
	}
	else if (ext == L"hdr")
	{
		//assert(SUCCEEDED(false))   assert(SUCCEEDED(true)); 전부 참으로 나옴
		//assert(true); 참
		//assert(false); 거짓
		//항상 에러가 걸리는 것을 만들기 위해서 임
		//hr = GetMetadataFromHDRFile( 존재함 사용안해서 없는것
		assert(false);
	}
	else
	{
		//WIC(Windows Imaging Component)
		//이미지 메타데이터는 이미지를 캡처하는 데 사용되는 장치 또는 이미지의 크기와 같은 
		//이미지에 대한 추가 정보를 제공하는 이미지 파일 내부에 포함된 데이터입니다. 
		//추출하는 과정
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		ASSERT(hr);
	}
	//분석내용을 가지고 desc만듬
	UINT width = metaData.width;
	UINT height = metaData.height;

	if (loadInfo != nullptr)
	{//만약에 사용자가 사이즈 정보를 주면 준 사이즈 정보로 제작
		width = loadInfo->Width;
		height = loadInfo->Height;

		metaData.width = loadInfo->Width;
		metaData.height = loadInfo->Height;
	}

	TextureDesc desc;
	desc.file = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		//저장된 것과 동일한것이 있는지 확인
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{//저장된것과 동일한 것이 있으면
		texture->metaData = exist.metaData;
		texture->view = exist.view;
	}
	else
	{//동일한 것이 없었을 경우
		ScratchImage image;
		//dx의 텍스쳐 읽어오는 방법임 즉 DirectxTex라이브러리는  
		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			ASSERT(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			ASSERT(hr);
		}
		else if (ext == L"hdr")
		{
			//hdr은 역시 받지 않음
			assert(false);
		}
		else
		{
			//wic는 기본적인 이미지 포멧을 받는 듯함(jpg png)
			hr = LoadFromWICFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			ASSERT(hr);
		}
		//텍스쳐리소스 쉐이더에 접근하기 위해서 쉐이더 리소스 뷰 제작
		ID3D11ShaderResourceView* view;
		//srv를 만들기 위해서 directTex라이브러리 함수를 사용
		//쉐이더 리소스 뷰를 만들기 위한 정보들을 집어넣음
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &view);
		ASSERT(hr);

		desc.file = texture->filePath;
		desc.width = metaData.width;
		desc.height = metaData.height;
		desc.view = view;
		desc.metaData = metaData;

		texture->view = view;
		texture->metaData = metaData;
		//사용한 desc를 저장
		descs.push_back(desc);
	}
}
