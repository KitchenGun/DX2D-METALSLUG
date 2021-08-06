#pragma once
class Time: public Singleton<Time>
{
public:
	friend class Singleton<Time>;

	static bool Stopped() { return isTimerStopped; }
	static float Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

	void Update();

	void Start();
	void Stop();
	float FPS() const { return framePerSecond; }
	float Running() const { return runningTime; }
private:
	Time(void);
	~Time(void);

	
	static bool isTimerStopped;	//시간이 멈췄는지 아닌지 확인용 변수
	static float timeElapsed;	//경과 시간

	//64비트 정수를 사용할 수 있도록 정의한 이유는 microsecond(1 / 1000000)초까지 측정하여 좀 더 정확한 시간값을 저장하기 위함
	
	INT64 ticksPerSecond=0;		//1초당 실행카운터의 빈도
	INT64 currentTime=0;		//현재시간
	INT64 lastTime=0;			//마지막 측정 시간
	INT64 lastFPSUpdate=0;		//마지막 초당 프레임 업데이트 시간
	INT64 fpsUpdateInterval=0;  //초당 프레임 업데이트 간격 = delta time = current time - previous time

	UINT frameCount=0;			//프레임
	float runningTime=0.0f;		//실행시간
	float framePerSecond=0.0f;
};