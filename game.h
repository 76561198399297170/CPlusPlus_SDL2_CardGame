#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include "singleton.h"
#include "camera.h"
#include "gamePlayer.h"
#include "gameMap.h"


class Game : public Singleton<Game>
{
	friend class Singleton<Game>;
private:
	Game();

public:
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game operator=(const Game&) = delete;
	Game operator=(const Game&&) = delete;

	~Game() = default;

	void startGame();
	void moveCamera();

	void clearKey();

	void update(float delta);
	void render(SDL_Renderer* renderer, const Camera* camera);
	void input(SDL_Event& event);

private:
	GameMap* m_map = nullptr;
	GamePlayer* m_palyer = nullptr;

private:
	Camera* m_game_camera;

	int m_wheel = 0;

	bool is_ctrl = false;

	bool is_up = false;
	bool is_down = false;
	bool is_left = false;
	bool is_right = false;

};

#endif

