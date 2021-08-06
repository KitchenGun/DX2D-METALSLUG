#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);
	ID3D11Buffer* GetResource() { return buffer; }
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	void SetIA();
private:
	ID3D11Buffer* buffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};

//버퍼 생성 텍스쳐를 넣나 단색을 넣나에 따라서 자료형이 바뀌기 때문에 template으로 제작
template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE & usage)
{
	stride = sizeof(T);
	count=(UINT)(vertices.size());
	//버퍼 만들기 위한 desc 제작
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = stride * count;

	//접근 방식에 대한 지정법 분리
	switch (usage)
	{
	case D3D11_USAGE_DEFAULT://gpu 읽기 쓰기만 가능
		break;
	case D3D11_USAGE_IMMUTABLE://gpu 읽기만 가능
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC://gpu 읽기 cpu 쓰기 가능
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING://복사 & 전부 접근 가능
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE|D3D11_CPU_ACCESS_READ;
		break;
	}
	//보조 자원데이터  ->사실상 리소스내에 있는 실제 데이터
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data(); //<-정점 정보를 넣어줘야함 선언후 초기화 해주는 과정
	
	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
	ASSERT(hr);
}
