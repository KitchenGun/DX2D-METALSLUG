#pragma once

class Texture2D
{
public:
	friend class Textures;

public:
	Texture2D(wstring filePath, D3DX11_IMAGE_LOAD_INFO* loadInfo = nullptr);
	~Texture2D();
	//오버로딩 readpixel
	D3D11_TEXTURE2D_DESC ReadPixel(DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels);
	static D3D11_TEXTURE2D_DESC ReadPixel(ID3D11Texture2D* src, DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels);
	
	void SaveFile(wstring filePath);
	void SaveFile(wstring filePath, ID3D11Texture2D* originalTex, vector<D3DXCOLOR>& pixels, UINT width, UINT height);
	static void SaveFile(wstring file, ID3D11Texture2D* src);

	wstring GetFilePath() { return filePath; }
	UINT GetWidth() { return metaData.width; }
	UINT GetHeight() { return metaData.height; }

	void GetImageInfo(DirectX::TexMetadata* data)
	{
		*data = metaData;
	}

	ID3D11ShaderResourceView* GetSRV() { return view; }
	ID3D11Texture2D* GetTexture();

private:
	wstring filePath;
	DirectX::TexMetadata metaData;
	ID3D11ShaderResourceView* view;
};

struct TextureDesc
{
	wstring file;
	UINT width, height;
	DirectX::TexMetadata metaData;
	ID3D11ShaderResourceView* view;
	//desc 구조체 비교를 위한 연산자
	bool operator==(const TextureDesc& desc)
	{
		bool b = true;
		//And 비트연산자 //입력정보가 desc의 해당 정보인지 확인 하는듯함
		b &= file == desc.file;
		b &= width == desc.width;
		b &= height == desc.height;

		return b;
	}
};

class Textures
{
public:
	friend class Texture2D;

public:
	static void Create();
	static void Delete();

private:
	static void Load(Texture2D* texture, D3DX11_IMAGE_LOAD_INFO* loadInfo = nullptr);

private:
	static vector<TextureDesc> descs;
};