#ifndef _CURSOR_MANAGER_H_
#define _CURSOR_MANAGER_H_

#include <SDL.h>

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

	enum class MouseType
	{
		NORMAL,		//Õý³£
		HOVER,		//Ðü¸¡
		CLICK,		//µã»÷
	};

public:
	void render(SDL_Renderer* renderer);

	void input(const SDL_Event& event);

	SDL_Point getPosCurr() { return this->m_position_current; }
	SDL_Point getPosPre() { return this->m_position_previous; }
	bool isLeftKeyDown() { return this->is_left_down; }

private:
	int m_mouse_size = 3;

	SDL_Point m_position_current = { 0 };
	SDL_Point m_position_previous = { 0 };

	MouseType m_current;

	bool is_left_down = false;

};

#endif
