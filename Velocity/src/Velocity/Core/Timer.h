#pragma once
#include <chrono>
#include <string_view>

namespace Velocity
{
	class Timer
	{
	public:
		Timer() {}

		~Timer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Begin()
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
			m_Stopped = false;
		}

		void Stop()
		{
			m_EndTimePoint = std::chrono::high_resolution_clock::now();
			m_Stopped = true;
		}

		float GetDuration()
		{
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(m_EndTimePoint).time_since_epoch().count();
			float duration = (end - start) * 0.001f;
			return duration;
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint, m_EndTimePoint;
		bool m_Stopped = false;
	};
}