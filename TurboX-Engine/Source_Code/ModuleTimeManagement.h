#pragma once

#include "Application.h"
#include "Module.h"
#include "Timer.h"

class ModuleTimeManagement : public Module
{
public:
	ModuleTimeManagement(Application* app, bool start_enabled = true);
	~ModuleTimeManagement();

	bool Start() override;
	update_status PreUpdate(float dt) override;
	bool CleanUp() override;

	void Play();
	void Resume();
	void Pause();
	void Stop();

	const float GetGameTimeInSeconds()const;
	const float GetGameDeltaTime() const;

	const float GetRealTimeInSeconds();
	const bool IsPaused() const;

	float* GetTimeScale();
	void SetTimeScale(float val);
	float GetDeltaTime() const;

private:
	float timeScale;
	float gameDeltaTime;
	float deltaTime;

	Timer realTimeClock;
	float gameClock;
	bool paused;
};