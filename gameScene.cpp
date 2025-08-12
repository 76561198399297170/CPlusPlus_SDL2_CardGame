#include "gameScene.h"
#include "resourcesManager.h"

extern int window_width;
extern int window_height;

void GameScene::enter()
{
}

void GameScene::exit()
{
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

}

void GameScene::input(SDL_Event& event)
{

}