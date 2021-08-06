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
    output.position = mul(input.position, _world);//world 공간으로 변환
    output.position = mul(output.position, _view);//view 공간에서 변화
    output.position = mul(output.position, _proj); //projection 공간을 변환
    
    //현재방식은 정점별 방식이 아닌 일반적으로 사용하는 방식
    output.uv = input.uv;
    
    return output;
}

Texture2D srcTex0 : register(t0);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target //현재 세팅한 타겟에 그려라
{
	float4 color = srcTex0.Sample(samp, input.uv);
	float3 grayscale = 0;
	if (_selection == 1)
	{
		
	}
	else if (_selection == 2)//야매
	{
		grayscale = (color.r + color.g + color.b) / 3.0f;
		color = float4(grayscale.xyz,1);
	}
	else if (_selection == 3)//정석
	{
		grayscale = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
		color = float4(grayscale.xyz, 1);//color값을 수정하여서 전달
	}
	else if (_selection == 4)//세피아
	{
		grayscale.r = dot(color.rgb, float3(0.393f,0.769f,0.189f));
		grayscale.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
		grayscale.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
		color = float4(grayscale.rgb, 1);
		//color값을 수정하여서 전달
	}
	
	if (_bOutline && (input.uv.x < 0.01f || input.uv.x > 0.99f || input.uv.y < 0.01f || input.uv.y > 0.99f))//액자
	{
		color = float4(1, 1, 1, 1);
	}
	return color;
}   
