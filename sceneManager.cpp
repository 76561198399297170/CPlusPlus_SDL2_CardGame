#include "sceneManager.h"
#include "dataManager.h"

void SceneManager::switchTo(SceneType switch_to, int sleep_time)
{
	this->m_scene->exit();

	this->m_timer_sleep.reset();
	this->m_timer_sleep.setDuration(sleep_time);
	this->m_timer_sleep.start();

	this->m_switch_to = switch_to;
}

void SceneManager::update(float delta)
{
	this->m_timer_sleep.update(delta);
	this->m_scene->update(delta);

	if (this->m_timer_sleep.isReached() && this->m_switch_to != SceneType::None)
	{

		switch (this->m_switch_to)
		{
		case SceneType::Menu:
			this->m_scene = DataManager::getInstance()->menu_scene->getInstance();
			break;
		case SceneType::Game:
			this->m_scene = DataManager::getInstance()->game_scene->getInstance();
			break;
		default:
			break;
		}
		this->m_scene->enter();
		this->m_switch_to = SceneType::None;
	}
}

void SceneManager::render(SDL_Renderer* renderer, const Camera* camera)
{
	this->m_scene->render(camera);
}

void SceneManager::input(SDL_Event& event)
{
	this->m_scene->input(event);
}
