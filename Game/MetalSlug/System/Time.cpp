#include "stdafx.h"
#include "Time.h"
//싱글톤패턴
bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void)
{
	//QueryPerformanceCounter : 일정지점안에서 몇번 진동 하였는가를 나타내는 함수
	//QueryPerformanceFrequency  : 1초당 틱(진동)수를 반환한다 매개변수(lpFrequency)에는 해당 타이머의 주기가 설정됨
	//cpu의 일정한 진동  초당 몇번 인지 반환하는것 
	//즉 매개변수에게 현재 시간값을 전달함							멀티프로레스에서 시간을 일정하게 측정하기 위해 사용
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);//어떤 기기에서나 일정한 실행카운터의 빈도 반환 
	//반환하는 카운터가 시스템 부팅과 동시에 일정하게 반납하는것
	//초당 cpu 진동수
	fpsUpdateInterval = ticksPerSecond >> 1;
}

Time::~Time(void)
{

}


void Time::Update()
{
	if (isTimerStopped) return;
	//현재 시간과 간격의 업데이트
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	//update한 번 돌때 즉 한 프레임 주기의 싸인 틱수 (컴퓨터 마다 사양이 다름) 
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	//결론은 작동환경과 상관없는 일정한 비율이 된다.
	runningTime += timeElapsed;
	//fps 업데이트 프레임 수 증가
	frameCount++;
	
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}
	lastTime = currentTime;
}

void Time::Start()//시간 흐르게함
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()//시간이 멈출 때 프로그램 정지
{
	if (!isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}

