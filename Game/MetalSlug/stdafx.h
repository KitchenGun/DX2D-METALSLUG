#pragma once

#pragma warning(disable: 26812)//dx 파일 경고 안보이게 만듬
#pragma warning(disable: 26595)//dx 파일 경고 안보이게 만듬
#pragma warning(disable: 26495)//dx 파일 경고 안보이게 만듬
#pragma warning(disable: 4390)//dx 파일 경고 안보이게 만듬
#pragma warning(disable: 4244)//dx 파일 경고 안보이게 만듬

#define NOMINMAX  //DX의 기본 최소 최대 정의 쓰지 않겠다
#define no_init_all//2017만 존재하는 버그 2019에서 수정됨

#ifdef _DEBUG
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <Windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

//DX
#include <D3Dcompiler.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
//라이브러리 참조
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dx11.lib")
#pragma comment (lib,"d3dx10.lib")
#pragma comment (lib,"d3dcompiler.lib")
//imgui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment (lib,"ImGui/ImGui.lib")
//fmod
#pragma comment(lib,"FMod/fmodex_vc.lib")
//texture
#include "DirectTex/DirectXTex.h"
#pragma comment(lib,"DirectTex/directxtex.lib")

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix;
typedef D3DXCOLOR Color;

#include "Utilities/Singleton.h"

//싱글톤 해더 추가
#include "System/Graphics.h"

#define DC Graphics::Get()->GetDC()
#define DEVICE Graphics::Get()->GetDevice()

#define SAFE_DELETE(p){if(p){delete (p);p=nullptr;}}//동적자원 해제
#define SAFE_DELETE_ARRAY(p){if(p){delete[](p);p=nullptr;}}//동적자원배열 해제
#define SAFE_RELEASE(p){if(p){p->Release(); p=nullptr;}}//DX 자원 해제(Com인터페이스의 참조횟수를 1 줄임) 

#define ASSERT(p) assert(SUCCEEDED(p));

//창크기
#define WinMaxWidth		1280
#define WinMaxHeight	720

#define Red		Color(1,0,0,1)
#define Green	Color(0,1,0,1)
#define Blue	Color(0,0,1,1)
#define Black	Color(0,0,0,1)
#define White	Color(1,1,1,1)
#define Yellow	Color(1,1,0,1)
#define Magenta Color(1,0,1,1)//투명 처리를 위해서 마젠타 색
#define Cyan	Color(0,1,1,1) // 청록색


typedef float HP;
typedef float JUMPPOW;
typedef float MOVESPEED;
typedef float DAMAGE;
typedef float SPEED;

//핸들러
extern HWND handle;

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Renders/Resources/VertexType.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/ViewFactory.h"
#include "Renders/Resources/Texture2D.h"

#include "System/Time.h"
#include "System/Mouse.h"
#include "System/Keyboard.h"
#include "System/GUI/Gui.h"
#include "System/Camera.h"

#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/FileStream.h"

#include "Scenes/Scene.h"
#include "Utilities/Math.h"