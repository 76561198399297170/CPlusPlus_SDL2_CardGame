#include "gameScene.h"
#include "resourcesManager.h"
#include "sceneManager.h"
#include <iostream>

extern int window_width;
extern int window_height;

extern Camera* main_camera;

void GameScene::enter()
{
	this->is_input = true;
	main_camera->turnLight(2000);

}

void GameScene::exit()
{
	main_camera->turnLight(2000);
}

void GameScene::render(const Camera* camera)
{
	const SDL_FRect bk_plc = { -10 + camera->m_position.m_x, -10 + camera->m_position.m_y, window_width + 20, window_height + 20 };
	const SDL_FRect bk_sky = { -10, -10, window_width + 20, (window_height + 20) / 2 };

    SDL_RenderCopyExF(camera->m_renderer, ResourcesManager::getInstance()->queryTexture("background_sky"), nullptr, &bk_sky, 0.0f, nullptr, SDL_FLIP_NONE);
    SDL_RenderCopyExF(camera->m_renderer, ResourcesManager::getInstance()->queryTexture("background_place"), nullptr, &bk_plc, 0.0f, nullptr, SDL_FLIP_NONE);
}

void GameScene::update(float delta)
{
	static int shake_time = 10;

	static bool turn_menu = false;
	if (shake_time > 0 && main_camera->isStopShake()) 
	{
		main_camera->shake(shake_time * 100);
		shake_time--;

		system("pause");
	}
	else if (!turn_menu && main_camera->isStopTurn() && shake_time <= 0)
	{
		turn_menu = true;
		SceneManager::getInstance()->switchTo(SceneManager::SceneType::Menu, 3000);
	}
}

void GameScene::input(SDL_Event& event)
{
}