#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "singleton.h"

#include "menuScene.h"
#include "gameScene.h"
#include "mapScene.h"


class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	SceneManager() = default;
	~SceneManager() = default;

	enum class SceneType
	{
		Menu,		//≤Àµ•
		Map,		//µÿÕº
		Game		//”Œœ∑
	};

	void switchTo(SceneType switch_to, bool is_exit = true);

	void update(float delta);

	void render(SDL_Renderer* renderer, const Camera* camera);

	void input(SDL_Event& event);

private:
	Scene* m_scene = nullptr;

};

#endif