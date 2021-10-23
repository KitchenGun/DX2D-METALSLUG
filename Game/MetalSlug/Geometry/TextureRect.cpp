#include "stdafx.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
	:
	position(position),
	size(size),
	rotation(rotation)
{
	//정점 정보 입력
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[0].uv = Vector2(0.0f, 1.0f);

	vertices[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[1].uv = Vector2(0.0f, 0.0f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
	vertices[2].uv = Vector2(1.0f, 1.0f);

	vertices[3].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	indices = { 0,1,2,2,1,3 };

	//클래스화 한 객체 생성
	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	WB = new WorldBuffer();

	//객체에서 함수 호출
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);


	shaderPath = L"./_Shaders/Animation.hlsl";//VertexTexture.hlsl";
	//경로의 변수화
	VS->Create(shaderPath, "VS");
	PS->Create(shaderPath, "PS");

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);
	//기존의 colorbuffer대신 사용
	SB = new SelectBuffer();
	//blur 기능 생성자
	BB = new BlurBuffer();
	LB = new LocalBuffer();
	//좌상단 우상단 좌표
	LB->SetLocalRect({ 100,100,400,400 });
}

TextureRect::~TextureRect()
{
	SAFE_RELEASE(nullView);
	SAFE_RELEASE(srv);

	SAFE_DELETE(LB);
	SAFE_DELETE(BB);
	SAFE_DELETE(SB);

	SAFE_DELETE(WB);

	SAFE_DELETE(IL);

	SAFE_DELETE(PS);
	SAFE_DELETE(VS);

	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void TextureRect::SetSRV(wstring path)
{
	this->texturePath = path;
	//텍스쳐가 쉐이더에 접근 할 수 있게 함
	ViewFactory::GenerateSRV(path, &srv);
}

void TextureRect::SetShader(wstring shaderPath)
{

	this->shaderPath = shaderPath;
	//vs와ps객체에 함수 호출// 실행중간에 교체할수있도록 함수화 하였음
	if (VS)
	{
		VS->Clear();
		VS->Create(shaderPath, "VS");
	}

	if (PS)
	{	
		PS->Clear();
		PS->Create(shaderPath, "PS");
	}
}

void TextureRect::Move(Vector3 position)
{
	this->position = position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;
	WB->SetWorld(world);
}

void TextureRect::MoveLocalRect(Vector4 localMove)
{	//정점정보를 전달하여 이동을 처리함
	LB->MoveLocalRect(localMove);
}

void TextureRect::SetSize(Vector3 size)
{
	this->size = size;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * R * T;
	WB->SetWorld(world);//내부에서 transpose해줌
}

void TextureRect::Update()
{
	if (Keyboard::Get()->Down(VK_00))
	{
		BB->SetCount(1);
	}
	else if (Keyboard::Get()->Down(VK_01))//1번 누르면 selection값이 바뀜
	{
		SB->SetSelection(1);
		BB->SetCount(2);
	}
	else if(Keyboard::Get()->Down(VK_02))
	{
		SB->SetSelection(2);
		BB->SetCount(4);
	}
	else if(Keyboard::Get()->Down(VK_03))
	{
		SB->SetSelection(3);  
		BB->SetCount(8);
	}
	else if (Keyboard::Get()->Down(VK_04))
	{
		SB->SetSelection(4);
		BB->SetCount(32);
	}

}

void TextureRect::Render()
{
	if (isRender)
	{
		VB->SetIA();
		IB->SetIA();
		IL->SetIA();
		//기본 도형 형성 방법 지정
		DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		WB->SetVSBuffer(0);
		VS->SetShader();

		PS->SetShader();
		if (srv)
		{
			DC->PSSetShaderResources(0, 1, &srv);
		}
		SB->SetPSBuffer(0);//ps단계에서 사용하는 첫번째 값이여서 0으로 입력해도됨
		//블러효과위해서 추가함
		BB->SetPSBuffer(1);
		LB->SetPSBuffer(2);
		//인덱스 버퍼를 이용해서 그리기
		DC->DrawIndexed(IB->GetCount(), 0, 0);
		if (srv)//텍스쳐를 지정하지 않아도 지정이 되는 문제를 해결하기 위한 예외 처리
		{
			DC->PSSetShaderResources(0, 1, &nullView);//더블 포인터 요청하는데 nullptr넣으면 당연히 안됨 
			//nullView는 엄밀히 말하면 nullView != nullptr
		}
	}
}

void TextureRect::GUI(int ordinal)//ordinal에 따라서 다르게 함수를 실행함
{
	string objName = "TextureRect" + to_string(ordinal);//ordinal에 따라서 결정이 됨
	string imgName = "Image : " + String::ToString(Path::GetFileName(texturePath));
	string shaderName = "Shader : " + String::ToString(Path::GetFileName(shaderPath));
	if (ImGui::BeginMenu(objName.c_str()))
	{//GUI창 안에 메뉴를 띄우겠다

		//선택시 외곽선 강조 활성화
		//SB->SetOutline(true);
		//선택한 파일 이름 텍스트 띄우기
		ImGui::Text(objName.c_str());
		ImGui::Text(imgName.c_str());
		ImGui::Text(shaderName.c_str());
		//버튼 클릭시 해당 함수 실행
		if (ImGui::Button("ChangeImage", ImVec2(100, 30)))
		{
			ChangeImageFunc();
		}
		if (ImGui::Button("ChangeShader", ImVec2(100, 30)))
		{
			ChangeShaderFunc();
		}
		if (ImGui::InputText("InputText", text, sizeof(text), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			SaveTextAsFile(text);
		}
		//슬라이더를 사용하여 객체의 상태 변경 슬라이더에는 소수점 2자리까지만 출력함
		ImGui::SliderFloat3("Translation", position, 0, WinMaxWidth, "%.2f");
		ImGui::SliderFloat3("Size", size, 1, WinMaxWidth, "%.2f");
		ImGui::SliderAngle("Rotation", &rotation);
		//gui에서 변경값을 적용
		D3DXMatrixScaling(&S, size.x, size.y, size.z);
		D3DXMatrixRotationZ(&R, -rotation);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		world = S * R * T;

		WB->SetWorld(world);

		ImGui::EndMenu();
	}
	else
	{
		//선택시 외곽선 강조 해제
		//SB->SetOutline(false);
	}
}

void TextureRect::ChangeImageFunc(const wstring & path)
{
	if (path.length() < 1)//주소가 없으면
	{
		//bind = 함수의 일부 매개 변수를 고정 값으로 세팅한 후, 한번 Wrapping 하여 사용할 수 있게 해주는 함수
		//Wrapping이란 데이터를 객체에 넣기 위해서 제공하는 함수들이라고 생각하면된다
		function<void(wstring)> func = bind(&TextureRect::ChangeImageFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L"./_Textures/", func, handle);
	}
	else
	{
		SetSRV(path);
	}
}

void TextureRect::ChangeShaderFunc(const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeShaderFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ShaderFilter, L"./_Shaders/", func, handle);
	}
	else
	{
		SetShader(path);
	}
}

void TextureRect::SaveTextAsFile(const string & text, const wstring & path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::SaveTextAsFile, this, text, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TextFilter, L"./", func, handle);
	}
	else
	{
		ofstream writefile(path.c_str());
		if (writefile.is_open())
		{
			writefile << text << endl;
			writefile.clear();
		}
		writefile.close();
	}
}
