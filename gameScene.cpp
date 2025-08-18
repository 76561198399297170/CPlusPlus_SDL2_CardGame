#include "gameScene.h"
#include "resourcesManager.h"
#include "sceneManager.h"
#include "dataManager.h"
#include <iostream>

GameScene::GameScene()
{
	this->m_main_game = Game::getInstance();

	this->m_tab_setting = new GameTable();

	this->m_btn_setting = ButtonFactory::getInstance()->create("Game_Setting", 1200, 10);
	this->m_btn_setting->addOnKeyupFunction([this]() { this->m_tab_setting->open(); this->m_main_game->clearKey(); });

}

void GameScene::enter()
{
	this->m_main_game->startGame();

	this->is_input = true;

	this->m_tab_setting->reload();
	this->m_tab_setting->close();

	this->m_btn_setting->restart();

	DataManager::getInstance()->main_camera->turnLight(2000);
}

void GameScene::exit()
{
	this->is_input = false;
	this->m_main_game->saveGame();
	DataManager::getInstance()->main_camera->turnLight(2000);
}

void GameScene::render(const Camera* camera)
{
	this->m_main_game->render(DataManager::getInstance()->renderer, camera);
	this->m_btn_setting->render(camera->m_renderer);
	this->m_tab_setting->render(camera);
}

void GameScene::update(float delta)
{
	if (!this->is_input)
	{
		this->m_main_game->clearKey();
	}

	this->m_tab_setting->update(delta);
	this->m_main_game->update(delta);
	this->m_btn_setting->update(delta);
}

void GameScene::input(SDL_Event& event)
{
	if (!this->is_input) return;
	if (!this->m_tab_setting->input(event)) return;

	this->m_main_game->input(event);
	this->m_btn_setting->input(event);
}