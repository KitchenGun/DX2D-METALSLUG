#pragma once
#define MAX_INPUT_MOUSE 8

class Mouse :public Singleton<Mouse>
{
public:
	friend class Singleton<Mouse>;

	void SetHandle(HWND handle)
	{
		this->handle = handle;
	}
	
	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);
	
	Vector3 GetPosition() { return position; }

	bool Down(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
	}
	bool Up(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
	}
	bool Press(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS;
	}
	Vector3 GetMoveValue() { return wheelMoveValue; }
private:
	Mouse();
	~Mouse();

	HWND handle;
	Vector3 position;

	byte buttonStatus[MAX_INPUT_MOUSE];			//현재 버튼 상태
	byte buttonOldStatus[MAX_INPUT_MOUSE];		//이전 버튼 상태
	byte buttonMap[MAX_INPUT_MOUSE];			//최종 버튼 상태

	Vector3	wheelStatus;					//현재 휠 상태
	Vector3 wheelOldStatus;					//이전 휠 상태
	Vector3 wheelMoveValue;					//최종 휠 상태

	DWORD timeDblClk;							//더블 클릭 시간
	DWORD startDblClk[MAX_INPUT_MOUSE];			//더블 클릭 시작
	int buttonCount[MAX_INPUT_MOUSE];			//버튼 클릭 횟수

	enum
	{
		MOUSE_ROTATION_NONE = 0,
		MOUSE_ROTATION_LEFT,
		MOUSE_ROTATION_RIGHT
	};

	enum 
	{
		BUTTON_INPUT_STATUS_NONE=0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};