#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "scene.h"
#include "singleton.h"


class GameScene : public Scene, public Singleton<GameScene>
{
	friend class Singleton<GameScene>;
public:
	GameScene() = default;
	~GameScene() = default;

	virtual void enter();
	virtual void exit();

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual void input(SDL_Event& event);

private:

};

#endif