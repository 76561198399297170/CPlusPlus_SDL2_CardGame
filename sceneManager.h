#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "singleton.h"
#include "timer.h"
#include "menuScene.h"
#include "gameScene.h"


class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
private:
	SceneManager() = default;

public:
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager operator=(const SceneManager&) = delete;
	SceneManager operator=(const SceneManager&&) = delete;

	~SceneManager() = default;

	enum class SceneType
	{
		None,		//无需	
		Menu,		//菜单
		Map,		//地图
		Game		//游戏
	};

	void setScene(Scene* scene) { this->m_scene = scene; this->m_scene->enter(); }

	void switchTo(SceneType switch_to, int sleep_time = 0);

	void update(float delta);
	void render(SDL_Renderer* renderer, const Camera* camera);
	void input(SDL_Event& event);

private:
	Timer m_timer_sleep;
	SceneType m_switch_to = SceneManager::SceneType::None;
	
	Scene* m_scene = nullptr;

};

#endif