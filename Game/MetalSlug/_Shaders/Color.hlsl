//glsl과의 차이는 메인 함수없이 특정함수를 진입점으로 사용할수있는 특징이 있다
struct VertexInput//pos 색 들어있음
{
	float4 position : POSITION0;
	//Semantics이란?	
	//사용자가 임의로 설정하는 전역변수나 버텍스 쉐이더의 입력 구조체의 변수들이 어떤 자료와 연결될지 알려주는 것이 시맨틱이다
	float4 color : COLOR0;
};
struct PixelInput
{
	float4 position : SV_POSITION0;//sv_ system value의 약자로 특별한 의미를 가진 Semantics name으로 사용됨
	float4 color : COLOR0;
};

cbuffer TransformBuffer : register(b0)  //상수 버퍼를 보낸다
{
    matrix _world;
    matrix _view;
    matrix _proj;
}

PixelInput VS(VertexInput input)//입력 pos와 입력 color 를 그대로 PixelInput 형태로 반환
{
    PixelInput output;
    //백터와 행렬의 곱을 수행할것
    output.position = mul(input.position, _world);//world 공간으로 변환
    output.position = mul(output.position, _view);//view 공간에서 변화
    output.position = mul(output.position, _proj); //projection 공간을 변환
    output.color = input.color;
    
    return output;
}


float4 PS(PixelInput input) : SV_Target //현재 세팅한 타겟에 그려라
{
    return input.color;
}
