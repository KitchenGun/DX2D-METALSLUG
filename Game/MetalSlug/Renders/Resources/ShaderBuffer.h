#pragma once
#include "stdafx.h"


class ShaderBuffer
{
public:
	//(Normalized Device Coordinate System 정규화 장치 좌표계 max 1 min 0으로 표현)
	void SetVSBuffer(UINT slot)//ndc 좌표계로 보다가 공간변환을 해줌으로써 스케일 변환 필요함 
	{
		MapData(data, dataSize);
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(UINT slot)
	{
		MapData(data, dataSize);

		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}
protected:
	ShaderBuffer(void* data, UINT dataSize) : data(data), dataSize(dataSize)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = dataSize;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//바인딩 식별
		//데이터 패딩  데이터를 16바이트 단위에 맞게 보내주는것  지금은 필요없음 안썼음
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//cpu 쓰기 허용
		desc.MiscFlags = 0;									//기타 플래그 사용안하면 0
		desc.StructureByteStride = 0;						//버퍼뷰에서 사용하는 형식의 크기와 일치해야함
		HRESULT hr = DEVICE->CreateBuffer(&desc, NULL, &buffer);
		ASSERT(hr);
	}
	virtual ~ShaderBuffer()
	{
		SAFE_RELEASE(buffer);
	}
private:
	//lock의 역할 map과 unmap으로 수행
	void MapData(void* data, UINT dataSize)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DC->Map
		(
			buffer,					
			0,
			D3D11_MAP_WRITE_DISCARD,//맵해서 쓰고 버린다
			0,
			&subResource
		);
		memcpy(subResource.pData, data, dataSize);
		DC->Unmap(buffer, 0);
	}

	D3D11_BUFFER_DESC desc;
	ID3D11Buffer* buffer;		//gpu 버퍼
	void* data;					//cpu 버퍼
	UINT dataSize;
};