#include "gameScene.h"
#include "resourcesManager.h"
#include "sceneManager.h"

extern int window_width;
extern int window_height;

extern Camera* main_camera;

GameScene::GameScene()
{
	this->m_tab_setting = new GameTable();

	this->m_btn_setting = ButtonFactory::getInstance()->create("Game_Setting", 1200, 10);
	this->m_btn_setting->addOnKeyupFunction([this]() { this->m_tab_setting->open(); });

}

void GameScene::enter()
{
	this->is_input = true;

	this->m_tab_setting->reload();
	this->m_btn_setting->restart();
	this->m_tab_setting->close();

	main_camera->turnLight(2000);
}

void GameScene::exit()
{
	main_camera->turnLight(2000);
}

void GameScene::render(const Camera* camera)
{
	this->m_tab_setting->render(camera);

	this->m_btn_setting->render(camera->m_renderer);

	//const SDL_FRect bk_plc = { -10 + camera->m_position.m_x, -10 + camera->m_position.m_y, window_width + 20, window_height + 20 };
	//const SDL_FRect bk_sky = { -10, -10, window_width + 20, (window_height + 20) / 2 };

    //SDL_RenderCopyExF(camera->m_renderer, ResourcesManager::getInstance()->queryTexture("background_sky"), nullptr, &bk_sky, 0.0f, nullptr, SDL_FLIP_NONE);
    //SDL_RenderCopyExF(camera->m_renderer, ResourcesManager::getInstance()->queryTexture("background_place"), nullptr, &bk_plc, 0.0f, nullptr, SDL_FLIP_NONE);
}

void GameScene::update(float delta)
{
	this->m_tab_setting->update(delta);

	this->m_btn_setting->update(delta);
}

void GameScene::input(SDL_Event& event)
{
	if (!this->is_input) return;
	if (!this->m_tab_setting->input(event)) return;

	this->m_btn_setting->input(event);
}