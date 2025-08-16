#include "game.h"
#include <cmath>
#include "dataManager.h"
#include <iostream>

Game::Game()
{
	this->m_game_camera = new Camera(DataManager::getInstance()->renderer);

	this->m_map = new GameMap();
	this->m_palyer = new GamePlayer();
}

void Game::startGame()
{
	this->m_game_camera->setPosition(0, 0);
	this->m_palyer->reload();
	this->m_map->loadMapInf();
}

void Game::moveCamera()
{
	int dir_x = this->is_right - this->is_left;
	int dir_y = this->is_down - this->is_up;
	float dir_len = sqrt(pow(dir_x, 2) + pow(dir_y, 2));
	Vector2 move_pos{ 0, 0 };

	if (dir_len != 0)
	{
		float normalized_x = dir_x / dir_len;
		float normalized_y = dir_y / dir_len;

		move_pos.m_x = (int)(DataManager::getInstance()->game_camera_move_speed * normalized_x);
		move_pos.m_y = (int)(DataManager::getInstance()->game_camera_move_speed * normalized_y);
	}
	std::cout << "move: " << move_pos.m_x << ", " << move_pos.m_y << "\n";

	this->m_game_camera->movePosition(move_pos);
}

void Game::clearKey()
{
	this->m_wheel = 0;

	this->is_ctrl = false;

	this->is_up = false;
	this->is_down = false;
	this->is_left = false;
	this->is_right = false;
}

void Game::update(float delta)
{
	this->moveCamera();

	this->m_map->update(delta);
	this->m_palyer->update(delta);
}

void Game::render(SDL_Renderer* renderer, const Camera* camera)
{
	this->m_map->render(renderer, this->m_game_camera);
	this->m_palyer->render(renderer, camera);
}

void Game::input(SDL_Event& event)
{
	this->m_wheel = 0;
	SDL_Scancode scancode = event.key.keysym.scancode;

	switch (event.type)
	{
	case SDL_KEYDOWN:
	{
		switch (scancode)
		{
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
			{
				this->is_up = true;
			}
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN: 
			{
				this->is_down = true;
			}
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
			{
				this->is_left = true;
			}
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
			{
				this->is_right = true;
			}
				break;
			case SDL_SCANCODE_LCTRL:
			case SDL_SCANCODE_RCTRL:
			{
				this->is_ctrl = true;
			}
			break;
			default:
				break;
		}
	}
	break;
	case SDL_KEYUP:
	{
		switch (scancode)
		{
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
		{
			this->is_up = false;
		}
		break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
		{
			this->is_down = false;
		}
		break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
		{
			this->is_left = false;
		}
		break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
		{
			this->is_right = false;
		}
		break;
		case SDL_SCANCODE_LCTRL:
		case SDL_SCANCODE_RCTRL:
		{
			this->is_ctrl = false;
			this->m_wheel = 0;
		}
			break;
		default:
			break;
		}
	}
	break;
	case SDL_MOUSEWHEEL:
	{
		if (this->is_ctrl)
		{
			this->m_wheel = event.wheel.y;
		}
	}
	break;
	default:
		break;
	}

	this->m_map->input(event);
	this->m_palyer->input(event);
}