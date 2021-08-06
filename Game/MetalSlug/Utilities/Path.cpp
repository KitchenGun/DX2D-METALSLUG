#include "stdafx.h"
#include "Path.h"

bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

bool Path::ExistFile(wstring path)
{
	//unsigned short
	//word
	//unsigned long
	DWORD fileValue = GetFileAttributes(path.c_str());//기존 파일 속성 확인 파일 없으면 -1
	//최소값보다 작은 값이 들어갔을 때 최대값이 나오는 것이 -> 언더 플로우
	return fileValue < 0xFFFFFFFF;//최대값 = -1 = 파일이 없는상황
}

bool Path::ExistDirectory(string path)//파일이 존재하는 지 안하는지 확인용
{

	return ExistDirectory(String::ToWString(path));
}

bool Path::ExistDirectory(wstring path)//이미 경로가 존재하는지 존재하지 않는지 확인
{
	DWORD attribute = GetFileAttributes(path.c_str());
	//INVALID_FILE_ATTRIBUTES는 (DWORD)-1				비트연산자 and를 사용하여 둘다 1일 경우를 찾는거임 
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && (attribute & FILE_ATTRIBUTE_DIRECTORY));
	//파일 존재을 확인하면서 attribute가 파일 디렉토리인것을 확인하고 확인값을 반환
	return temp == TRUE;
}

string Path::Combine(string path1, string path2)//string문 2개를 합치기
{
	return path1+path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{//for문을 사용해서 vector안에 분리되어있는 스트링을 합치는 역할 
	string temp = "";
	for (string path : paths)
		temp += path;
	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;
	return temp;
}

string Path::GetDirectoryName(string path)
{//파일 명을 땐 경로를 얻는 함수
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	//확장자를 얻음
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index+1,path.length());
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');//전체 경로에서 마지막으로 나오는/를 찾아라
	//이름과 확장자를 반환 
	return path.substr(index + 1, path.length());
}

string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(string path)
{
	//확장자를 제외한 파일이름
	string fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0,index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);
	size_t index = fileName.find_last_of('.');

	return fileName.substr(0, index);
}

//확장자와 파일형식을 확인하기 위해서 작성함
						//뜻	 =	  항목+아무파일,확장자
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";
const WCHAR* Path::SoundFilter = L"Sound file\0*.wav;*.mp3;*.flac";

void Path::OpenFileDialog(wstring file, const WCHAR * filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];//선택한 파일이름
	wcscpy_s(name, file.c_str());
	//초기경로로 지정할 string변수
	wstring tempFolder = folder;
	//윈도우 경로로 변경
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"불러오기";
	ofn.nMaxFile = 255;
	//폴더 경로 초기화
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)//파일을 열수있으면
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");
			//변환값을 매개변수의 함수에 전달
			func(loadName);
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR * filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	
	String::Replace(&tempFolder, L"/", L"\\");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;
	//
	if (filter == TextFilter)
		ofn.lpstrDefExt = L".txt";
	else if (filter == ShaderFilter)
		ofn.lpstrDefExt = L".hlsl";


	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring saveName = name;
			String::Replace(&saveName, L"\\", L"/");

			func(saveName);
		}
	}
}

void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);
	for (wstring str : wFiles)
	{
		files->push_back(String::ToString(str));
	}
}
//										파일들이 있는 경로
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	//파일이 여러개 반환 경로에 있으면서 필터에 충족하는 자료들을 불러옴
	wstring file = path + filter;

	WIN32_FIND_DATA findData;//파일정보를 넘겨주는 함수와 호완이 되는 자료형
	HANDLE handle = FindFirstFile(file.c_str(), &findData);
	if (handle != INVALID_HANDLE_VALUE)//핸들이 있는지 없는지 확인
	{
		do
		{
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)//불러온 파일 속성이 폴더인 경우
			{
				//하위폴더를 탐색할것인가?   .이 있으면 현재 폴더이기때문에 제외한다
				if (bFindSubFolder == true && findData.cFileName[0] != '.')//내부에 폴더가 있는 경우 수색을 한건가 안할건가?
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";//마지막에 /넣어주겠다는 의미
					GetFiles(files, folder, filter, bFindSubFolder);//재귀함수를 사용해서 계속 하위로 들어감 모든 하위 폴더 탐색
				}
			}
			else//속성이 폴더가 아니라 파일일때 이름을 벡터에 넣음
			{
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));//다음데이터가 존재한다면 계속 반복
		//끝나면 탐색 종료
		FindClose(handle);
	}
}

void Path::CreateFolder(string path)//folder 생성
{
	CreateFolder(String::ToWString(path));
}

void Path::CreateFolder(wstring path)
{
	//경로가 존재하지않으면 폴더 만듬
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);//폴더 생성시 옵션은 null ex)읽기 전용, 숨김
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

void Path::CreateFolders(wstring path)
{
	//없는 폴더 만들면서 하위폴더까지 한번에 만들기 
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	// 자르는 기준이 / 이다 그리고 vector에 넣어줌
	String::SplitString(&folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";
		CreateFolder(temp);
	}
}
