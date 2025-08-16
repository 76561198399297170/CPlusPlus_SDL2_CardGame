#include "cursorManager.h"
#include "resourcesManager.h"
#include "dataManager.h"
#include <iostream>

CursorManager::CursorManager()
{
	this->m_current = MouseType::HOVER;

	SDL_GetMouseState(&m_position_current.x, &m_position_current.y);
	m_position_previous = m_position_current;
}

CursorManager::~CursorManager()
{

}

void CursorManager::render(SDL_Renderer* renderer)
{
	if (!renderer) return;

	SDL_Texture* curr_texture = nullptr;
	switch (this->m_current)
	{
	case MouseType::NORMAL: curr_texture = ResourcesManager::getInstance()->queryTexture("cursor_normal"); break;
	case MouseType::HOVER: curr_texture = ResourcesManager::getInstance()->queryTexture("cursor_hover"); break;
	case MouseType::CLICK: curr_texture = ResourcesManager::getInstance()->queryTexture("cursor_click"); break;
	}

	int w, h;
	SDL_QueryTexture(curr_texture, nullptr, nullptr, &w, &h);

	SDL_Rect destRect = { m_position_current.x,	m_position_current.y, w * this->m_mouse_size, h * this->m_mouse_size };
	SDL_RenderCopy(renderer, curr_texture, nullptr, &destRect);
}

void CursorManager::input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION://鼠标移动
	{
		this->m_position_previous.x = this->m_position_current.x, this->m_position_previous.y = this->m_position_current.y;
		this->m_position_current.x = event.motion.x, this->m_position_current.y = event.motion.y;
	}
	break;
	case SDL_MOUSEBUTTONDOWN://鼠标按下
	{
		if (event.button.button == SDL_BUTTON_LEFT)//左键
		{
			this->is_left_down = true;
			this->m_current = MouseType::CLICK;

			switch (rand() % 3)
			{
			case 0: Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("click_1"), 0); break;
			case 1: Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("click_2"), 0); break;
			case 2: Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("click_3"), 0); break;
			}
		}
	}
	break;
	case SDL_MOUSEBUTTONUP://鼠标抬起
	{
		if (event.button.button == SDL_BUTTON_LEFT)//左键
		{
			this->is_left_down = false;
			this->m_current = MouseType::HOVER;
		}
	}
	break;
	default:
		break;
	}
	system("cls");
	std::cout << this->m_position_current.x << " " << this->m_position_current.y << "\n";
}
