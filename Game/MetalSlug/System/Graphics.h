#pragma once
//싱글톤 
//GPU다루는 것이 핵심 = DX
//쉐이더 표현을 하기위해서 사용하는 것 HLSL

//전방선언 //지금같은 경우는 밑의 클래스를 Graphics 클래스에서 사용하기 위함
/*
전방 선언을 할 경우 클래스의 존재만 인지시키는 것이기 때문에 포인터로 밖에 선언하지 못한다.
전방선언을 사용하는 이유는 참조하려는 헤더파일에 변경이 생겨도 헤더파일의 재컴파일이 이루어지 지지 않기 때문에 효율성과 속도를 증진시키고자 사용한다.
또한 역참조가 되는 구조를 막기도 한다.
*/
class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;

class Graphics : public Singleton<Graphics>
{
public:
	friend class Singleton<Graphics>;
public:
	ID3D11Device*GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }

	void Resize(const UINT& width, const UINT& height);
	void SetViewport(const UINT& width, const UINT& height);

	void Begin();
	void End();

	void SetViewport();
	Color GetClearColor() { return clearColor; }
	void SetBackBufferToRTV();

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	Graphics();
	~Graphics();

	static Graphics* instance;

	void EnumerateAdapters();										//그래픽 카드 정보
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfos);	//그래픽 카드의 정보를 토대로 모니터 정보 읽기
	void SetGPUInfo();
	
private:
	ID3D11Device* device=nullptr;				//자원을 생성하는 역할  desc(설명서 주문서)와 유사한 역할
												//com interface (componant object model)내부에 이미 할당되어서 수정하지 않는 영역  앞에 I가 붙어있는 경우  삭제가 아니라 해제하는 것 
	ID3D11DeviceContext* deviceContext=nullptr;	//그림그릴때 씀
												//safe release로 지워야함
	IDXGISwapChain* swapChain = nullptr;		//이중 버퍼링 해주는 객체 //프론트와 백을 교체해주는 체인
	ID3D11RenderTargetView* rtv = nullptr;		//백버퍼에 연결되어있는 화면에 rtv효과를 만들어 저장하여 스왑체인이 동작하면 연결되어 실행됨
												//비트맵 같은 효과
	D3D11_VIEWPORT viewport = { 0 };			//보여지는 영역	
	Color clearColor = 0xff555566;			//초기색 
	//갱신 주기를 위해 필요한 변수
	UINT numerator;					//분자
	UINT denominator;				//분모
	//그래픽카드 정보저장
	UINT gpuMemorySize;
	wstring gpuDescription;
	//컴퓨터의 모든 그래픽 카드정보들을 벡터 형태로 저장
	vector<D3DEnumAdapterInfo*> adapterInfos;
	//필요한 그래픽카드의 정보를 즉각 호출하기위해 저장할수있는 인덱스
	int selectedAdapterIndex;

	bool bVsync = true; // 수직 동기화 모니터에 맞춰서 해줌 평균 60hz라고 생각하면됨//현재 모디터와 주사율을 맞춘다   
	//티어링 현상을 방지하기 위해서 사용(모니터 주사율과 그래픽카드의 성능이 차이날때 생기는 현상이다)
	
};

//////////////////////////////////////////////////////////////////////////////////////////
class D3DEnumAdapterInfo//그래픽 카드 정보
{
public:
	D3DEnumAdapterInfo()=default;
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	IDXGIAdapter1* adapter = nullptr;		//핵심 com interface 디스플레이 서브 시스템 여러 gpu의 정보 및 메모리를 받아올수있다.
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	D3DEnumOutputInfo* outputInfo = nullptr;

	
private:
	const D3DEnumAdapterInfo& operator = (const D3DEnumAdapterInfo& rhs);
};

class D3DEnumOutputInfo//모니터 정보
{
public:
	D3DEnumOutputInfo() = default;
	~D3DEnumOutputInfo();

	IDXGIOutput* output = nullptr;			//핵심 com interface 모니터 정보를 받아오는데 사용함
	DXGI_OUTPUT_DESC outputDesc = { 0 };
	//주사율과 관련있음
	UINT numerator;
	UINT denominator;

private:
	const D3DEnumOutputInfo &operator = (const D3DEnumOutputInfo& rhs);
};