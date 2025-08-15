#include "camera.h"

#include <mutex>
#include <ctime>

extern int window_width;
extern int window_height;

extern bool is_shake;

Camera::Camera(SDL_Renderer* renderer)
{
	this->m_timer_light.setDuration(600);
	this->m_timer_light.start();

	this->is_shaking = false;
	this->m_renderer = renderer;

	this->m_timer_shake.setAutoRestart(false);
	this->m_timer_shake.setCallback([&]()
		{
			this->is_shaking = false;
			this->reset();
		});

	static std::once_flag init_flag;
	std::call_once(init_flag, []()
		{
			std::srand((unsigned int)(std::time(nullptr)));
		});

}

void Camera::reset()
{
	this->m_position = this->m_shake_place;
}

void Camera::update(float delta)
{
	this->m_timer_shake.update(delta);
	this->m_timer_light.update(delta);

	if (this->is_shaking)
	{
		//正弦余弦叠加抖动
		float elapsed_time = m_timer_shake.getPercentage() * this->m_timer_shake.getDurattion();

        float speed_factor = m_shaking_strength * 3.0f;
        float time_factor = elapsed_time * speed_factor;

        float elastic_factor = 1.0f + (m_shaking_strength * 0.5f);

        float x_base = sin(time_factor * M_PI * 2 * 1.2f + m_random_phase_x) * m_shaking_strength;
        float y_base = cos(time_factor * M_PI * 2 * 1.5f + m_random_phase_y) * m_shaking_strength;

        float x_elastic = sin(time_factor * M_PI * 2 * 4.0f * elastic_factor + m_random_phase_x) * (m_shaking_strength * 0.6f);
        float y_elastic = cos(time_factor * M_PI * 2 * 4.5f * elastic_factor + m_random_phase_y) * (m_shaking_strength * 0.6f);

        float x_jitter = (sin(time_factor * 7.0f) * 0.5f + sin(time_factor * 11.0f) * 0.3f) * (m_shaking_strength * 0.3f);
        float y_jitter = (cos(time_factor * 8.0f) * 0.5f + cos(time_factor * 13.0f) * 0.3f) * (m_shaking_strength * 0.3f);

        m_position.m_x = x_base + x_elastic + x_jitter + m_initial_offset_x;
        m_position.m_y = y_base + y_elastic + y_jitter + m_initial_offset_y;

		//矩形随机位置抖动
		//this->m_position.m_x = (-50 + rand() % 100) / 50.0f * this->m_shaking_strength;
		//this->m_position.m_y = (-50 + rand() % 100) / 50.0f * this->m_shaking_strength;
	}
}

void Camera::render()
{
	float per = this->m_timer_light.getPercentage();
	copyexRect(this->m_renderer, 0, 0, 0, std::abs((this->is_light ? 255 : 0) - (per / 100.0f) * 255), -50, -50, window_width + 50, window_height + 50);
}

void Camera::shake(float duration, float strength)
{
	if (!is_shake) return;

	this->m_shake_place = this->m_position;

	this->is_shaking = true;
	this->m_shaking_strength = strength;

	m_initial_offset_x = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * strength;
	m_initial_offset_y = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * strength;

	m_random_phase_x = (float)(rand()) / RAND_MAX * 2.0f * (float)(M_PI);
	m_random_phase_y = (float)(rand()) / RAND_MAX * 2.0f * (float)(M_PI);

	this->m_timer_shake.setDuration(duration);
	this->m_timer_shake.reset();
	this->m_timer_shake.start();
}

void Camera::turnLight(float duration)
{
	this->is_light = !this->is_light;

	this->m_timer_light.reset();
	this->m_timer_light.setDuration(duration);
	this->m_timer_light.start();
}
