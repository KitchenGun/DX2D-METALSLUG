#include "stdafx.h"
#include "String.h"

void String::SplitString(vector<string>* result, string origin, string tok)//특정 문자를 기준으로 문자열 자르기
{
	result->clear();

	int cutAt = 0;//자를 위치 인덱스
	
	//문자열 origin에서 tok가 나오는 가장 첫번째 문자의 인덱스를 cutat에 넣고 while문 돌림
	//찾는 문자열이 있을 경우 돌린다
	//find_first_of(tok)를 긴것을 통째로 넣으면 토큰에 들어가있는 문자열을 구성하는 문자하나라도 발견되면 그위치가 먼저 반환한다
	//npos == -1로 취급
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)//연산자 우선순위때문에 이렇게 작성함
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));
		//오리지날에 자른부분을 제외하고 넣어준다
		origin = origin.substr(cutAt + 1);
	}
	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0;
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0)
		result->push_back(origin.substr(0, cutAt));
}

bool String::StartsWith(string str, string comp)//comp로 시작하는지 안하는지 확인용
{
	string::size_type index = str.find(comp);

	if (index != string::npos && (int)index == 0)//중복 경로를 찾을때 사용할 수 있다.
		return true;

	return false;
}

bool String::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found !=string::npos;
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

void String::Replace(string * str, string comp, string rep)//수정위해서 포인터로 받음
{
	//원래 문자열의 특정부분을 주어진 문자열로 교체
	string temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != string::npos) //반복으로 수행
	{
		temp.replace(start_pos, comp.length(), rep);//선택한 인덱스 범위를 rep로 교체함
		start_pos += rep.length();
	}

	*str = temp;
}

void String::Replace(wstring * str, wstring comp, wstring rep)
{
	wstring temp = *str;
	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}
	*str = temp;
}

string String::ToString(Vector3 vec3)
{
	wstring temp;
	temp = L" X:" + to_wstring(vec3.x)+L" Y:"+ to_wstring(vec3.y) + L" Z:" + to_wstring(vec3.z);
	string str = ToString(temp);

	return str;
}

wstring String::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

string String::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
