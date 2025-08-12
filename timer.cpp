#include "timer.h"

Timer::Timer(float duration, std::function<void()> callback)
	: m_duration(duration), m_callback(callback)
{

}

Timer::Timer(const Timer& other)
{
	this->is_auto_restart = other.is_auto_restart;
	this->is_reached = other.is_reached;
	this->is_running = other.is_running;

	this->m_callback = other.m_callback;
	this->m_current_time = other.m_current_time;
	this->m_duration = other.m_duration;
}

void Timer::setAutoRestart(bool is_auto)
{
	this->is_auto_restart = is_auto;
}

void Timer::setCallback(std::function<void()> callback)
{
	this->m_callback = callback;
}

void Timer::setDuration(float duration)
{
	this->m_duration = duration;
	this->is_reached = (this->m_current_time >= this->m_duration ? true : false);
}

float Timer::getPercentage()
{
	if (this->m_duration <= 0) return 100.0f;
	if (this->m_current_time <= 0) return 0.0f;
	float res = (float)this->m_current_time / this->m_duration * 100.0f;

	return res < 100.0f ? res : 100.0f;
}

float Timer::getDurattion()
{
	return this->m_duration;
}

void Timer::update(float delta)
{
	if (!this->is_running || (!this->is_auto_restart && this->is_reached)) return;
	
	this->m_current_time += delta;
	if (this->m_current_time >= this->m_duration)
	{
		if (this->is_auto_restart) this->m_current_time -= this->m_duration;
		if ((!this->is_reached || this->is_auto_restart) && this->m_callback) this->m_callback();
		this->is_reached = !this->is_auto_restart;
	}
}

void Timer::pause()
{
	this->is_running = false;
}

void Timer::start()
{
	this->is_running = true;
}

void Timer::reset()
{
	this->m_current_time = 0;
	this->is_reached = false;
}

bool Timer::isReached()
{
	if (this->is_auto_restart) return false;
	return this->is_reached;
}
