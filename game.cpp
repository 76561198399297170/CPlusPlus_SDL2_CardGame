#include "game.h"
#include <cmath>
#include "dataManager.h"
#include <fstream>
#include <iostream>

Game::Game()
{
	this->m_game_camera = new Camera(DataManager::getInstance()->renderer);

	this->m_map = new GameMap();
	this->m_palyer = new GamePlayer();
}

void Game::startGame(bool is_restart)
{
	if (is_restart)
	{
		this->m_game_camera = new Camera(DataManager::getInstance()->renderer);

		if (this->m_map->createNewGame() || this->m_palyer->createPlayer()) DataManager::getInstance()->is_quit = true;

		this->m_game_camera->setPosition((this->m_map->getMapMid_x() - DataManager::getInstance()->window_width) / 2.0f, (this->m_map->getMapMid_y() - DataManager::getInstance()->window_height) / 2.0f);

		return;
	}
	std::string errors;
	Json::Value root_map;

	std::ifstream file("./save/map.json");
	if (!file.is_open())
	{
		this->startGame(true);
		return;
	}

	Json::CharReaderBuilder reader;
	if (!Json::parseFromStream(reader, file, &root_map, &errors) || true)//暂时设置强制断开，避免加载数据而使用创建方法
	{
		this->startGame(true);
		return;
	}

	//不应该触发
	system("pause");

	this->m_game_camera->setPosition(root_map["camera"]["x"].asFloat(), root_map["camera"]["y"].asFloat());

	this->m_map->loadMapInf(root_map);
	this->m_palyer->reload();
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

		move_pos.m_x = (float)(DataManager::getInstance()->game_camera_move_speed * normalized_x);
		move_pos.m_y = (float)(DataManager::getInstance()->game_camera_move_speed * normalized_y);
	}

	this->m_game_camera->movePosition(move_pos);
}

bool Game::saveGame()
{
	return this->m_map->saveMapInf() && this->m_palyer->savePlayerInf();
}

void Game::clearKey()
{
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
		}
			break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
	int wheel = CursorManager::getInstance()->getWheel();
	if ((this->is_ctrl || CursorManager::getInstance()->isMiddleKeyDown()) && wheel != 0)
	{
		float scale = this->m_map->getScale() + (wheel > 0 ? 1 : -1) * 0.01f;
		scale = std::max(0.1f, std::min(0.5f, scale));


		Vector2 center_pos = Vector2{ DataManager::getInstance()->window_width / 2.0f, DataManager::getInstance()->window_height / 2.0f } + this->m_game_camera->m_position - MapPlace().base;
		center_pos = center_pos * scale / this->m_map->getScale() - Vector2{ DataManager::getInstance()->window_width / 2.0f, DataManager::getInstance()->window_height / 2.0f } + MapPlace().base;

		this->m_game_camera->setPosition(center_pos);
		
		this->m_map->setScale(scale);
	}

	if (CursorManager::getInstance()->isRightKeyDown())
	{
		this->m_game_camera->movePosition(CursorManager::getInstance()->getVecPre() - CursorManager::getInstance()->getVecCurr());
	}

	this->m_map->input(event);
	this->m_palyer->input(event);
}