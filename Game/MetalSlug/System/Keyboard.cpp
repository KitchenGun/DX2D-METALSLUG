#include "stdafx.h"
#include "Keyboard.h"


Keyboard::Keyboard()
{
	//초기화
	ZeroMemory(KeyState, sizeof(KeyState));
	ZeroMemory(KeyOldState, sizeof(KeyOldState));
	ZeroMemory(KeyMap, sizeof(KeyMap));
}

Keyboard::~Keyboard()
{

}


void Keyboard::Update()
{
	//이전 키 상태에 현재 키 넣기
	memcpy(KeyOldState, KeyState, sizeof(KeyOldState));
	
	ZeroMemory(KeyState, sizeof(KeyState));
	ZeroMemory(KeyMap, sizeof(KeyMap));

	GetKeyboardState(KeyState);					//256 개의 가상 키 상태를 지정된 버퍼에 복사합니다.

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = KeyState[i] & 0x80;			//and 비트연산을 통해서 입력을 확인하고 80보다 크면 아스키 코드의 값이 아니다
		KeyState[i] = key ? 1 : 0;				//입력했으면 1 입력이 없었으면 0으로 저장을 한다

		int oldState = KeyOldState[i];
		int state = KeyState[i];

		if (oldState == 0 && state == 1)		//이전상태와 현재 상태를 프레임 마다 비교하여 입력 상태를 확인
		{
			KeyMap[i] = KEY_INPUT_STATUS_DOWN;
		}
		else if (oldState == 1 && state == 0)
		{
			KeyMap[i] = KEY_INPUT_STATUS_UP;
		}
		else if (oldState == 1 && state == 1)
		{
			KeyMap[i] = KEY_INPUT_STATUS_PRESS;
		}
		else
		{
			KeyMap[i] = KEY_INPUT_STATUS_NONE;
		}

	}
	GetKeyState(0);  //가상키에 대한 상태를 반환?  현재는 사용안함
}

