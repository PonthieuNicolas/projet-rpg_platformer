#pragma once
#include "SystemInterface.h"
#include "ECS_Manager.h"

class TimerSystem : public ISystem {
private:
	ECS_Manager* ecsManager;
	double mSecondsPerCount;
	double mDeltaTime;
	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;
	bool mStopped;

public:
	TimerSystem();
	virtual ~TimerSystem() = default;

	virtual void setECSManager(ECS_Manager* manager) override;
	virtual void start() override;
	virtual void update() override;
	virtual void addEntity(Entity* entity) override;

	float TotalTime() const;
	float DeltaTime() const;
	void Reset();
	void Start();
	void Stop();
	void Tick();
};


