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
	float4 result = 0;
	
	
	if (_selection == 1)
	{
		result = srcTex0.Sample(samp, float2(1-input.uv.x,input.uv.y));
	}
	else if (_selection == 2)//좌우 거울
	{
		float4 l = srcTex0.Sample(samp, input.uv);
		float4 r = srcTex0.Sample(samp, float2(input.uv.x - 0.5f, input.uv.y));
		
		if (input.uv.x < 0.5f)

			result = l;
		if (input.uv.x > 0.5f)
			result = r;
		
		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
		{
			result = float4(1, 1, 1, 1);
		}
	}
	else if (_selection == 3)//4분면 거울
	{
		float4 site1 = srcTex0.Sample(samp, 2 * float2(input.uv.x, input.uv.y));
		float4 site2 = srcTex0.Sample(samp, 2 * float2(1-input.uv.x, input.uv.y));
		float4 site3 = srcTex0.Sample(samp, 2 * float2(input.uv.x, 1 - input.uv.y));
		float4 site4 = srcTex0.Sample(samp, 2 * float2(1-input.uv.x, 1-input.uv.y));
		
		if (input.uv.x < 0.5f && input.uv.y < 0.5f)
			result = site1;
		if (input.uv.x > 0.5f && input.uv.y < 0.5f)
			result = site2;
		if (input.uv.x < 0.5f && input.uv.y > 0.5f)
			result = site3;
		if (input.uv.x > 0.5f && input.uv.y > 0.5f)
			result = site4;
		
		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
		{
			result = float4(1, 1, 1, 1);
		}
		if (input.uv.y > 0.499f && input.uv.y < 0.501f)
		{
			result = float4(1, 1, 1, 1);
		}
	}
	else if (_selection == 4)//과제
	{
		float4 site1 = srcTex0.Sample(samp, 2 * float2(input.uv.x, input.uv.y));
		float4 site2 = srcTex0.Sample(samp, 2 * float2(1 - input.uv.x, input.uv.y));
		float4 site3 = srcTex0.Sample(samp, 2 * float2(input.uv.x, 1 - input.uv.y));
		float4 site4 = srcTex0.Sample(samp, 4 * float2(input.uv.x-0.5f, input.uv.y - 0.5f));
		float4 site5 = srcTex0.Sample(samp, 4 * float2(1-input.uv.x, input.uv.y - 0.5f));
		float4 site6 = srcTex0.Sample(samp, 4 * float2(input.uv.x - 0.5f, 1-input.uv.y));
		float4 site7 = srcTex0.Sample(samp, 4 * float2(1-input.uv.x, 1-input.uv.y));
		
		if (input.uv.x < 0.5f && input.uv.y < 0.5f)
			result = site1;
		if (input.uv.x > 0.5f && input.uv.y < 0.5f)
			result = dot(site2,float4(0.299f, 0.587f, 0.114f,0));
		if (input.uv.x < 0.5f && input.uv.y > 0.5f)
		{
			site3.r = dot(site3.rgb, float3(0.393f, 0.769f, 0.189f));
			site3.g = dot(site3.rgb, float3(0.349f, 0.686f, 0.168f));
			site3.b = dot(site3.rgb, float3(0.272f, 0.534f, 0.131f));
			result = site3;
		}
		if (input.uv.x > 0.5f && input.uv.x < 0.75f && input.uv.y > 0.5f && input.uv.y < 0.75f)
			result = site4;
		if (input.uv.x < 1.0f && input.uv.x > 0.751f && input.uv.y > 0.5f && input.uv.y < 0.75f)
			result = dot(site5, float4(0.299f, 0.587f, 0.114f,0));
		if (input.uv.x > 0.5f && input.uv.x < 0.75f && input.uv.y < 1.0f && input.uv.y > 0.751f)
		{
			site6.r = dot(site6.rgb, float3(0.393f, 0.769f, 0.189f));
			site6.g = dot(site6.rgb, float3(0.349f, 0.686f, 0.168f));
			site6.b = dot(site6.rgb, float3(0.272f, 0.534f, 0.131f));
			result = site6;
		}
		if (input.uv.x < 1.0f && input.uv.x > 0.751f && input.uv.y < 1.0f && input.uv.y > 0.751f)
			result = site7;

		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
		{
			result = float4(1, 1, 1, 1);
		}
		if (input.uv.y > 0.499f && input.uv.y < 0.501f)
		{
			result = float4(1, 1, 1, 1);
		}
		if (input.uv.x > 0.5f && input.uv.x < 1.0f&&input.uv.y > 0.749f && input.uv.y < 0.751f)
		{
			result = float4(1, 1, 1, 1);
		}
		if (input.uv.x > 0.749f && input.uv.x < 0.751f&&input.uv.y > 0.501f && input.uv.y < 1.0f)
		{
			result = float4(1, 1, 1, 1);
		}
	}
	if (_bOutline && (input.uv.x < 0.01f || input.uv.x > 0.99f || input.uv.y < 0.01f || input.uv.y > 0.99f))//액자
	{
		result = float4(1, 1, 1, 1);
	}
	return result;
}