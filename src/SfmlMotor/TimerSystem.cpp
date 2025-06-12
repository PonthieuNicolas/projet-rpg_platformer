#include "pch.h"
#include "TimerSystem.h"
#include <windows.h>

TimerSystem::TimerSystem() : ecsManager(nullptr), mSecondsPerCount(0.0), mDeltaTime(0.0),
	mBaseTime(0), mPausedTime(0), mStopTime(0), mPrevTime(0), mCurrTime(0), mStopped(true) {}

void TimerSystem::setECSManager(ECS_Manager* manager) {
	ecsManager = manager;
}

void TimerSystem::start() {
	Reset();
}

void TimerSystem::update() {
	Tick();
}

void TimerSystem::addEntity(Entity* entity) {
}

float TimerSystem::TotalTime() const {
	return static_cast<float>((mCurrTime - mBaseTime) * mSecondsPerCount);
}

float TimerSystem::DeltaTime() const {
	return static_cast<float>(mDeltaTime);
}

void TimerSystem::Reset() {
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / static_cast<double>(countsPerSec);

	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrTime);
	mBaseTime = mCurrTime;
	mPrevTime = mCurrTime;
	mStopTime = 0;
	mPausedTime = 0;
	mStopped = false;

	std::cout << "TimerSystem: Reset - mSecondsPerCount = " << mSecondsPerCount << std::endl;
}

void TimerSystem::Start() {
	if (mStopped) {
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
		if (mStopTime >= 0) {
			mPausedTime += (startTime - mStopTime);
			mPrevTime = startTime;
			mStopTime = 0;
			mStopped = false;
		}
		std::cout << "TimerSystem: Started" << std::endl;
	}
}

void TimerSystem::Stop() {
	if (!mStopped) {
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mStopTime = currTime;
		mStopped = true;
		std::cout << "TimerSystem: Stopped" << std::endl;
	}
}

void TimerSystem::Tick() {
	if (mStopped) {
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;
	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0) {
		mDeltaTime = 0.0;
	}

	static int frameCount = 0;
	frameCount++;
}