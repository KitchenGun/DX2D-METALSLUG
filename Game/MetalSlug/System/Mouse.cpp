#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
{
	//초기화
	//위치
	position = Vector3(0.0f, 0.0f, 0.0f);

	wheelStatus = Vector3(0.0f, 0.0f, 0.0f);
	wheelOldStatus = Vector3(0.0f, 0.0f, 0.0f);
	wheelMoveValue = Vector3(0.0f, 0.0f, 0.0f);

	ZeroMemory(buttonStatus, sizeof(byte)*MAX_INPUT_MOUSE);
	ZeroMemory(buttonOldStatus, sizeof(byte)*MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte)*MAX_INPUT_MOUSE);

	ZeroMemory(startDblClk, sizeof(DWORD)*MAX_INPUT_MOUSE);
	ZeroMemory(buttonCount, sizeof(int)*MAX_INPUT_MOUSE);
	//클릭
	timeDblClk = GetDoubleClickTime();
	startDblClk[0] = GetTickCount();
	
	for (int i = 1; i < MAX_INPUT_MOUSE; i++)
	{
		startDblClk[i] = startDblClk[0];
	}

	//휠

	DWORD tLine = 0; //휠줄 수
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);//세로 마우스 휠을 움직일 때 스크롤 할 줄 수를 검색합니다. 
}

Mouse::~Mouse()
{

}

void Mouse::Update()
{
	memcpy(buttonOldStatus, buttonStatus, sizeof(buttonOldStatus));

	ZeroMemory(buttonStatus, sizeof(buttonStatus));
	ZeroMemory(buttonMap, sizeof(buttonMap));
	//버튼 클릭 확인
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		int tOldStatus = buttonOldStatus[i];
		int tStatus = buttonStatus[i];

		if (tOldStatus == 0 && tStatus == 1)
		{
			buttonMap[i] = BUTTON_INPUT_STATUS_DOWN;
		}
		else if (tOldStatus == 1 && tStatus == 0)
		{
			buttonMap[i] = BUTTON_INPUT_STATUS_UP;
		}
		else if (tOldStatus == 1 && tStatus == 1)
		{
			buttonMap[i] = BUTTON_INPUT_STATUS_PRESS;
		}
		else
		{
			buttonMap[i] = BUTTON_INPUT_STATUS_NONE;
		}
	}
	//좌표 & 휠 갱신
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);
	wheelOldStatus.x = wheelStatus.x;
	wheelOldStatus.y = wheelStatus.y;

	wheelStatus.x = float(point.x);
	wheelStatus.y = float(point.y);

	wheelMoveValue = wheelStatus - wheelOldStatus;
	wheelOldStatus.z = wheelStatus.z;

	//버튼 클릭 기록을 모아서 확인
	DWORD tButtonStatus = GetTickCount();
	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (buttonMap[i] == BUTTON_INPUT_STATUS_DOWN)
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDblClk[i]) >= timeDblClk)
					buttonCount[i] = 0;
			}
			buttonCount[i]++;

			if (buttonCount[i] == 1)
				startDblClk[i] = tButtonStatus;
		}

		if (buttonMap[i] == BUTTON_INPUT_STATUS_UP)
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDblClk[i]) >= timeDblClk)
					buttonCount[i] = 0;
			}
			else if (buttonCount[i] == 2)
			{
				if ((tButtonStatus - startDblClk[i]) <= timeDblClk)
					buttonMap[i] = BUTTON_INPUT_STATUS_DBLCLK;

				buttonCount[i] = 0;
			}
		}//if
	}//for(i)
}

LRESULT Mouse::InputProc(UINT message, WPARAM wParam, LPARAM lParam)//API마우스 메세지 가져와서 값전달
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = WinMaxHeight - (float)HIWORD(lParam);
	}

	if (message == WM_MOUSEWHEEL)
	{
		short tWheelValue = (short)HIWORD(wParam);

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z += (float)tWheelValue;
	}
	return true;
}
