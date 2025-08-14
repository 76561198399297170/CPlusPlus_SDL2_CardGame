#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL.h>
#include <SDL_image.h>

#include "timer.h"
#include "vector2.h"
#include "utils.h"

class Camera
{
public:
	Camera(SDL_Renderer* renderer);
	~Camera() = default;

	void reset();

	void update(float delta);

	void render();

	void shake(float duration, float strength = 15);

	void turnLight(float duration);
	
	bool isStopShake() { return !this->is_shaking; }
	bool isStopTurn() { return this->m_timer_light.isReached(); }

public:
	SDL_Renderer* m_renderer;

	float m_random_phase_x, m_random_phase_y;
	float m_initial_offset_x, m_initial_offset_y;

	Vector2 m_position = { 0 ,0 };

private:
	Timer m_timer_light;
	Timer m_timer_shake;

	Vector2 m_shake_place = { 0, 0 };

	float m_shaking_strength = 0;
	bool is_shaking = false;
	bool is_light = false;
};

#endif

