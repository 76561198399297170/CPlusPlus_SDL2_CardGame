#ifndef _TIME_H_
#define _TIME_H_

#include <functional>


class Timer
{
public:
	Timer() = default;
	Timer(float duration, std::function<void()> callback);
	Timer(const Timer& other);
	~Timer() = default;

	void update(float delta);

	void pause();

	void start();

	void reset();

	bool isReached();
	float getPercentage();
	float getDurattion();

	void setAutoRestart(bool is_auto);
	void setCallback(std::function<void()> callback);
	void setDuration(float duration);

private:
	bool is_reached = false;
	bool is_running = false;
	bool is_auto_restart = false;

	float m_duration = 0;
	float m_current_time = 0;

	std::function<void()> m_callback = [&]() {};

};


#endif

