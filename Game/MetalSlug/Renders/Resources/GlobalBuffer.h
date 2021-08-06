#pragma once

#include "stdafx.h"
//world & view,projection 이렇게 나눈이유는 이동을 구현할때 world 행렬만 있으면 되기때문이다
//dx 행우선 gpu 열우선 행렬 그렇기 때문에 전치 행렬이 필요함

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(WorldStruct))
	{
		//항등행열
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world) 
	{
		//전치 시킨다
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct WorldStruct
	{
		Matrix world;
	};
private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ShaderBuffer
{
public: 
	ViewProjectionBuffer() :ShaderBuffer(&data, sizeof(ViewProjStruct))
	{
		//항등행열
		D3DXMatrixIdentity(&data.View);
		D3DXMatrixIdentity(&data.Projection);
	}
	void SetView(Matrix view)
	{
		//전치 시킨다
		D3DXMatrixTranspose(&data.View, &view);
	}
	void SetProjection(Matrix projection)
	{
		//전치 시킨다
		D3DXMatrixTranspose(&data.Projection, &projection);
	}
		
	struct ViewProjStruct
	{
		Matrix View;
		Matrix Projection;
	};

private :
	ViewProjStruct data;
};

class ColorBuffer : public ShaderBuffer
{
public:
	ColorBuffer() : ShaderBuffer(&data, sizeof(Struct))
	{
		data.color = Color(0, 0, 0, 1);
	}

	void SetColor(Color color)
	{
		data.color = color;
	}

	struct Struct
	{
		Color color;
	};

private:
	Struct data;
};