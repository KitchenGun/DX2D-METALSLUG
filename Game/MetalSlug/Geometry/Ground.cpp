#include "stdafx.h"
#include "Ground.h"
#include "Utilities/Animator.h"

Ground::Ground(Vector3 position, Vector3 size, float rotation,bool isObb)
	:PlayerAnimationRect( position,  size,  rotation),
	isObb(isObb)
{
	texture = new Texture2D(L"./_Textures/TestBox.png");
	animClips.push_back(new AnimationClip(L"temp", texture, 1, { 0, 0 }, { (float)texture->GetWidth(),(float)texture->GetHeight() }));
	animator = new Animator(animClips);

	animator->SetCurrentAnimClip(L"temp");
	animator->bLoop = true;
	TransformVertices();
}

Ground::~Ground()
{
}

void Ground::Update()
{
	PlayerAnimationRect::Update();
}

void Ground::Render()
{
	PlayerAnimationRect::Render();
}

void Ground::GUI(int ordinal)
{
	string objName = "Ground" + to_string(ordinal);//ordinal에 따라서 결정이 됨
	if (ImGui::BeginMenu(objName.c_str()))
	{//GUI창 안에 메뉴를 띄우겠다

		//선택시 외곽선 강조 활성화
		SB->SetOutline(true);
		//선택한 파일 이름 텍스트 띄우기
		ImGui::Text(objName.c_str());
		//슬라이더를 사용하여 객체의 상태 변경 슬라이더에는 소수점 2자리까지만 출력함
		ImGui::InputFloat3("Translation", position,0);
		ImGui::InputFloat3("Size", size, 1);
		ImGui::SliderAngle("Rotation", &rotation);
		//gui에서 변경값을 적용
		D3DXMatrixScaling(&S, size.x, size.y, size.z);
		D3DXMatrixRotationZ(&R, -rotation);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		world = S * R * T;

		WB->SetWorld(world);
		TransformVertices();
		ImGui::EndMenu();
	}
	else
	{
		//선택시 외곽선 강조 해제
		SB->SetOutline(false);
	}
}
