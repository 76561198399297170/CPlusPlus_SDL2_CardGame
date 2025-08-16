#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "scene.h"
#include "singleton.h"
#include "gameTable.h"
#include "game.h"


class GameScene : public Scene, public Singleton<GameScene>
{
	friend class Singleton<GameScene>;
private:
	GameScene();

public:
	GameScene(const GameScene&) = delete;
	GameScene(GameScene&&) = delete;
	GameScene operator=(const GameScene&) = delete;
	GameScene operator=(const GameScene&&) = delete;

	~GameScene() = default;

	virtual void enter();
	virtual void exit();

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual void input(SDL_Event& event);

private:
	Game* m_main_game;

	Button* m_btn_setting;

	GameTable* m_tab_setting;
};

#endif