/////////////////vertex shader 부분
cbuffer World : register(b0)
{
    matrix _world;
};

cbuffer ViewProjection : register(b1) //상수 버퍼를 보낸다
{
    matrix _view;
    matrix _proj;
};

/////////////////pixel shader 부분
cbuffer SelectBuffer : register(b0)//효과 선택과 화면 크기(하지만 blur는 hlsl를 호출한 객체만 적용됨)
{
	int _selection;
	float2 _textureSize;
	bool _bOutline;
};

cbuffer BlurBuffer : register(b1)//blur 강도 
{
	uint _count;
};

cbuffer LocalBuffer : register(b2)//blur 처리할 공간 정보
{
	float4 _localRect;
};

