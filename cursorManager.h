#ifndef _CURSOR_MANAGER_H_
#define _CURSOR_MANAGER_H_

#include <SDL.h>
#include "vector2.h"
#include "singleton.h"


class CursorManager : public Singleton<CursorManager>
{
	friend class Singleton<CursorManager>;
private:
	CursorManager();

public:
	CursorManager(const CursorManager&) = delete;
	CursorManager(CursorManager&&) = delete;
	CursorManager operator=(const CursorManager&) = delete;
	CursorManager operator=(const CursorManager&&) = delete;

	~CursorManager();

	enum MouseType
	{
		HOVER,		//悬浮
		CLICK,		//点击
		Catch,		//抓取
		Grab		//抓住
	};

public:
	void resetWheel() { this->m_mid_wheel = 0; }
	
	void render(SDL_Renderer* renderer);
	void update(float delta);
	void input(const SDL_Event& event);

	void switchType(MouseType type);

	SDL_Point getPosCurr() { return this->m_position_current; }
	Vector2 getVecCurr() { return Vector2{ (float)this->m_position_current.x, (float)this->m_position_current.y }; }

	SDL_Point getPosPre() { return this->m_position_previous; }
	Vector2 getVecPre() { return Vector2{ (float)this->m_position_previous.x, (float)this->m_position_previous.y }; }

	int getWheel() { return this->m_mid_wheel; }
	bool isLeftKeyDown() { return this->is_left_down; }
	bool isMiddleKeyDown() { return this->is_mid_down; }
	bool isRightKeyDown() { return this->is_right_down; }
	
private:
	int m_mouse_size = 3;

	SDL_Point m_position_current = { 0 };
	SDL_Point m_position_previous = { 0 };

	MouseType m_current;

	int m_mid_wheel = 0;
	bool is_left_down = false;
	bool is_mid_down = false;
	bool is_right_down = false;
};

#endif
