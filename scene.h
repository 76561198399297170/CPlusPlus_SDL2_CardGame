#ifndef _SCENE_H_
#define _SCENE_H_

#include <SDL.h>

#include "camera.h"
#include "animation.h"
#include "button.h"
#include "vector2.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	virtual void enter() {}
	virtual void exit() {}

	virtual void render(const Camera* camera) {}
	virtual void update(float delta) {}
	virtual void input(SDL_Event& event) {}

private:

};

#endif
