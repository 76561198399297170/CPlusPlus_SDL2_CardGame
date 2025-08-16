#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include <SDL.h>
#include "camera.h"

class GamePlayer
{
public:
	GamePlayer() = default;
	~GamePlayer() = default;

	void reload();

	void update(float delta);
	void render(SDL_Renderer* renderer, const Camera* camera);
	void input(SDL_Event& event);

private:

};

#endif

