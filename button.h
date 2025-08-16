#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <functional>

#include "camera.h"
#include "animation.h"
#include "vector2.h"


class Button
{
	friend class ButtonFactory;
public:
	Button();
	~Button();

	enum class ButtonType
	{
		Unknow,
		Normal,
		Float,
		KeyDown,
	};

	void render(SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void update(float delta);
	void input(SDL_Event& event);

	void restart();

	void addOnKeyupFunction(std::function<void()> func);
	void addOnMoveFunction(std::function<void()> func);
	void addEveryKeyupFunction(std::function<void()> func);

	void setPosition(int x, int y);
	void setTexture(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n = 1, int f = 1, int k = 1);
	void setTextureSheet(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_num, int f_num, int k_num, int n_duration, int f_duration, int k_duration);
	void setTexture_ex(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n = 1, int f = 1, int k = 1);
	void setTextureSheet_ex(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_num, int f_num, int k_num, int n_duration, int f_duration, int k_duration);
	void setOnFloatFunction(std::function<void()> func) { this->on_onfloat = func; }
	void setOutFloatFunction(std::function<void()> func) { this->on_outfloat = func; }
	void setOnKeydownFunction(std::function<void()> func) { this->on_keydown = func; }
	void setOnKeyupFunction(std::function<void()> func) { this->on_keyup = func; }

	bool isOnButton(const Vector2& pos) const;
	bool isOnButton(const SDL_Point& pos) const;
	bool isOnButton_ex(const Vector2& pos) const;
	bool isOnButton_ex(const SDL_Point& pos) const;
	Animation* getCurrentAnimation() const;
	Vector2 getPosition() { return Vector2{ this->m_rect_dst.x, this->m_rect_dst.y }; }

public:
	bool is_show = true;//是否显示
	Vector2 m_move_base;//临时偏移位置
	Vector2 m_flag;//创建时原始位置
	Vector2 m_flag_pmv;//最大移动正范围
	Vector2 m_flag_nmv;//最大移动负方向范围

private:
	bool is_streaming = false;
	bool is_move = false;

	SDL_Rect m_rect_src;
	SDL_FRect m_rect_dst;
	SDL_FPoint m_rect_center;


	float m_angle;

	ButtonType m_type = ButtonType::Normal;

	Animation* m_tex_normal;
	Animation* m_tex_float;
	Animation* m_tex_keydown;

	std::function<void()> on_move = []() {};
	std::function<void()> on_onfloat = []() {};
	std::function<void()> on_outfloat = []() {};
	std::function<void()> on_keydown = []() {};
	std::function<void()> on_keyup = []() {};
	std::function<void()> on_everykeyup = []() {};
};

class ButtonFactory 
{
private:
	ButtonFactory() = default;

	ButtonFactory(const ButtonFactory&) = delete;
	ButtonFactory& operator=(const ButtonFactory&) = delete;

public:
	static ButtonFactory* getInstance()
	{
		static ButtonFactory instance;
		return &instance;
	}

	Button* create(std::string button_type, int x = 0, int y = 0);

};

#endif