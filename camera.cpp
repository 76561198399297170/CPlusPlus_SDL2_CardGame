#include "camera.h"

#include <mutex>
#include <ctime>

Camera::Camera(SDL_Renderer* renderer)
{
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

	if (this->is_shaking)
	{
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

		//this->m_position.m_x = (-50 + rand() % 100) / 50.0f * this->m_shaking_strength;
		//this->m_position.m_y = (-50 + rand() % 100) / 50.0f * this->m_shaking_strength;
	}
}

void Camera::render(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_FRect* rect_dest, double angle, const SDL_FPoint* center) const
{
	SDL_FRect rect_dst_win = *rect_dest;
	rect_dst_win.x -= this->m_position.m_x;
	rect_dst_win.y -= this->m_position.m_y;

	SDL_RenderCopyExF(this->m_renderer, texture, rect_src, &rect_dst_win, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Camera::shake(float duration, float strength)
{
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
