#include "stdafx.h"
#include "Camera.h"

void Camera::Update()
{
	//Move(position);
}

void Camera::Render()
{
	VPBuffer->SetVSBuffer(1);
}

void Camera::Move(Vector3 position)
{
	if (this->position.x+position.x > fMinXValue && this->position.x + position.x < fMaxXValue)
	{
		this->position += position * Time::Delta();
		UpdateView();
	}
}

void Camera::SetCamPos(Vector3 position)
{
	this->position = position;
	UpdateView();
}

void Camera::UpdateView()
{
	//결과값을 요구함(매트릭스),객체 위치,			눈의 위치,			 천장의 위치
	D3DXMatrixLookAtLH(&view, &position, &(position + Vector3(0, 0, 1)), &(Vector3(0, 1, 0)));//z축으로 이동할 일이 없음
	VPBuffer->SetView(view);
}

void Camera::UnProjection(Vector3 * out, Vector3 source, Matrix world)
{
	Vector3 position = source;
	out->x = (position.x*2.0f / WinMaxWidth) - 1.0f;
	out->y = (position.y*2.0f / WinMaxHeight) - 1.0f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);

	D3DXVec3TransformCoord(out, out, &wvp);
}


Camera::Camera()
{
	VPBuffer = new ViewProjectionBuffer();
	//보여주는 방향
	D3DXMatrixLookAtLH(&view,&Vector3(0,0,0),&Vector3(0,0,1), &Vector3(0, 1, 0));
	//좌하단 원점이 아닌 화면기준을 원점으로 잡음
	//잘건드리면 확대기능 만들수있을 것 같다
	D3DXMatrixOrthoOffCenterLH(&proj, 0, WinMaxWidth, 0, WinMaxHeight, 0, 1);
	VPBuffer->SetView(view);
	VPBuffer->SetProjection(proj);
}

Camera::~Camera()
{
}
