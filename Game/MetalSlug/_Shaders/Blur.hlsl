#include "CBuffers.hlsl"

//glsl과의 차이는 메인 함수없이 특정함수를 진입점으로 사용할수있는 특징이 있다
struct VertexInput//pos 색 들어있음
{
	float4 position : POSITION0;
	//Semantics이란?	
	//사용자가 임의로 설정하는 전역변수나 버텍스 쉐이더의 입력 구조체의 변수들이 어떤 자료와 연결될지 알려주는 것이 시맨틱이다
	float2 uv : TEXCOORD0;
};
struct PixelInput
{
	float4 position : SV_POSITION0;//sv_ system value의 약자로 특별한 의미를 가진 Semantics name으로 사용됨
    float2 uv : TEXCOORD0;
};



PixelInput VS(VertexInput input)//입력 pos와 입력 color 를 그대로 PixelInput 형태로 반환
{
	PixelInput output;
    //백터와 행렬의 곱을 수행할것
	output.position = mul(input.position, _world); //world 공간으로 변환
	output.position = mul(output.position, _view); //view 공간에서 변화
	output.position = mul(output.position, _proj); //projection 공간을 변환
    
    //현재방식은 정점별 방식이 아닌 일반적으로 사용하는 방식
	output.uv = input.uv;
    
	return output;
}

Texture2D srcTex0 : register(t0);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target //현재 세팅한 타겟에 그려라
{
	float4 result = 0;
	float4 color = srcTex0.Sample(samp, input.uv);//원본
	
	float2 arr[8] =
	{
		float2(-1, -1), float2(0, -1), float2(1, -1),
		float2(-1, 0),				   float2(1, 0),
		float2(-1, 1), float2(0, 1),   float2(1, 1)
	};
	
	
	[flatten]//0,1 사이값으로 좌표를 변경 //blur를 적용할 지역 //input 사이즈가 변경됨 나머지 사이즈가 변경됨  
	if (input.uv.x > _localRect.x / _textureSize.x &&
		input.uv.x < _localRect.z / _textureSize.x &&
		input.uv.y > _localRect.y / _textureSize.y &&
		input.uv.y < _localRect.w / _textureSize.y)
	{
		//blur변수는 원본 픽셀과의 거리를 의미함
		/*
			즉 blur가 8일 경우 8만큼 거리의 값들을 평균을 낸다.
		*/
		for (int blur = 0; blur < _count; blur++)//한번 돌때마다 blur 처리함
		{
			for (int i = 0; i < 8; i++)
			{
				//배열내부의 방향 픽셀의 색상값을 평균을 내는 과정 다운샘플링하는 과정
				float x = arr[i].x * (float) blur / _textureSize.x;//정규화작업으로 좌표를 정함
				float y = arr[i].y * (float) blur / _textureSize.y;
				//가운데 픽셀에서 주변으로 이동
				float2 uv = input.uv + float2(x, y);
				//이동부분 픽셀 변환값으로 지정
				color += srcTex0.Sample(samp, uv);//픽셀만큼 이동한 uv를 원본의 색값에 더해준다
			}
		}
		//자기 자신을 포함한 9개의 구역의 색 평균을 넣는다
		color /= _count * 8 + 1;
		result = float4(color.rgb, 1);

	}
	else
	{
		result = color;
	}
	
	if (_bOutline && (input.uv.x < 0.01f || input.uv.x > 0.99f || input.uv.y < 0.01f || input.uv.y > 0.99f))//액자
	{
		result = float4(1, 1, 1, 1);
	}
	return result;
}
