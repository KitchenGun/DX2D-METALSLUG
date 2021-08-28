#include "stdafx.h"
#include "FileStream.h"
//stream 흐름이다 -> 강물은 흐르는 방향이 일정하다 
//buffer 줄을 묶어 댓목 -> 댓목은 가만히 있다가 물건을 올려놓으면 임시적으로 데이터가 머문다고 할수있다.
//강물의 흐름을 따라서 움직인다.
//cin에 비교하면 "asd"입력하고 enter가 줄을 푸는 행위
FileStream::FileStream(string path, UINT flags)
{
	isOpen = false;
	this->flags = flags;

	int iosFlags = ios::binary;									//이진 모드
	//FILE *pstWStream = fopen("Resources/E11_01.txt", "wt");
	iosFlags |= this->flags & FILE_STREAM_WRITE ? ios::out : 0;	//쓰기
	iosFlags |= this->flags & FILE_STREAM_READ ? ios::in : 0;		//읽기

	if (this->flags & FILE_STREAM_WRITE)
	{
		out.open(path, iosFlags);
		if (out.fail())
		{
			ASSERT(false);
			return;
		}
	}
	else if (this->flags & FILE_STREAM_READ)
	{
		in.open(path, iosFlags);
		if (in.fail())
		{
			ASSERT(false);
			return;
		}
	}
	isOpen = true;
}

FileStream::~FileStream()
{
	Close();
}
void FileStream::Close()
{
	if (flags & FILE_STREAM_WRITE)
	{
		out.flush();
		out.close();
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.clear();
		in.close();
	}
}
//endl를 작성하면 끝에 개행문자가 들어가지않는다 같은 효과는 나오지만
void FileStream::Skip(UINT n)
{
	if (flags & FILE_STREAM_WRITE)
	{
		//n = offset 얼마나 건너 뛸거냐 
		out.seekp(n, ios::cur);
	}
}
