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
	string objName = "Ground" + to_string(ordinal);//ordinal�� ���� ������ ��
	if (ImGui::BeginMenu(objName.c_str()))
	{//GUIâ �ȿ� �޴��� ���ڴ�

		//���ý� �ܰ��� ���� Ȱ��ȭ
		SB->SetOutline(true);
		//������ ���� �̸� �ؽ�Ʈ ����
		ImGui::Text(objName.c_str());
		//�����̴��� ����Ͽ� ��ü�� ���� ���� �����̴����� �Ҽ��� 2�ڸ������� �����
		ImGui::InputFloat3("Translation", position,0);
		ImGui::InputFloat3("Size", size, 1);
		ImGui::SliderAngle("Rotation", &rotation);
		ImGui::Checkbox("isOBB", &isObb);
		//gui���� ���氪�� ����
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
		//���ý� �ܰ��� ���� ����
		SB->SetOutline(false);
	}
}

void Ground::SaveGroundTile(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&Ground::SaveGroundTile, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::GroundTileFilter, L"./", func, handle);
	}
	else
	{
		if (!groundInfo) return;
		FileStream* out = new FileStream(String::ToString(path), FILE_STREAM_WRITE);
	
		out->Write(position);
		out->Write(size);
		out->Write(rotation);
		out->Write(isObb);

		SAFE_DELETE(out);
	}
}

void Ground::LoadGroundTile(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&Ground::LoadGroundTile, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::GroundTileFilter, L"./", func, handle);
	}
	else
	{
		if (!groundInfo) return;

		/*
		width = in->Read<UINT>();
		height = in->Read<UINT>();
		*/

		FileStream* in = new FileStream(String::ToString(path), FILE_STREAM_READ);

		SAFE_DELETE(in);
	}
}
