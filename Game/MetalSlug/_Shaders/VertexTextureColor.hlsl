#include "CBuffers.hlsl"

//glsl과의 차이는 메인 함수없이 특정함수를 진입점으로 사용할수있는 특징이 있다
struct VertexInput//pos 색 들어있음
{
	float4 position : POSITION0;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};
struct PixelInput
{
	float4 position : SV_POSITION0;//sv_ system value의 약자로 특별한 의미를 가진 Semantics name으로 사용됨
	float4 color : COLOR0;
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
	
	return color;

}
