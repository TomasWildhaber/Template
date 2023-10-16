#pragma once

namespace Application
{
	class Time
	{
		Time() = delete;
	public:
		static float currentFrame;
		static float lastFrame;
		static float deltaTime;
	};
}