#pragma once


class Gui
{
public :
	static void Create();
	static void Delete();
	static Gui* Get();

	LRESULT MSGProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void PrintFrame();
	void GroundGUIS(vector<class Ground*>& groundVec, const char* name);

	void Update();
	void Render();

private:
	Gui();
	~Gui();
private:
	void ApplyStyle();
private:
	static Gui* instance;
};