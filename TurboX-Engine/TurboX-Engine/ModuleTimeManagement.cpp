#include "ModuleTimeManagement.h"
#include "ModuleScene.h"

ModuleTimeManagement::ModuleTimeManagement(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	timeScale = 1.0f;
	gameDeltaTime = 0.0f;

	gameClock = 0.0f;
	paused = true;
}


ModuleTimeManagement::~ModuleTimeManagement()
{
}

update_status ModuleTimeManagement::PreUpdate(float dt)
{
	if (!paused) {
		gameDeltaTime = dt * timeScale;
		gameClock += gameDeltaTime;
	}
	return UPDATE_CONTINUE;
}

bool ModuleTimeManagement::CleanUp()
{
	return true;
}

bool ModuleTimeManagement::Start()
{
	realTimeClock.Stop();
	realTimeClock.ResetTimer();

	return true;
}

void ModuleTimeManagement::Play()
{
	paused = false;
	realTimeClock.Start();
}

void ModuleTimeManagement::Resume()
{
	realTimeClock.Resume();
	paused = false;
}

void ModuleTimeManagement::Pause()
{
	realTimeClock.Stop();
	paused = true;
}

void ModuleTimeManagement::Stop()
{
	realTimeClock.Stop();
	realTimeClock.ResetTimer();
	paused = true;
	gameClock = 0;
	gameDeltaTime = 0;
}

const float ModuleTimeManagement::GetGameTimeInSeconds() const
{
	return gameClock;
}

const float ModuleTimeManagement::GetGameDeltaTime() const
{
	return gameDeltaTime;
}

const float ModuleTimeManagement::GetRealTimeInSeconds()
{
	return realTimeClock.ReadSec();
}

const bool ModuleTimeManagement::IsPaused() const
{
	return paused;
}

float* ModuleTimeManagement::GetTimeScale()
{
	return &timeScale;
}

void ModuleTimeManagement::SetTimeScale(float val)
{
	timeScale = val;
}