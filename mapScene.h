#ifndef _MAPSCENE_H_
#define _MAPSCENE_H_

#include "scene.h"
#include "singleton.h"


class MapScene : public Scene, public Singleton<MapScene>
{
	friend class Singleton<MapScene>;
public:
	MapScene() = default;
	~MapScene() = default;

	virtual void enter();
	virtual void exit();

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual void input(SDL_Event& event);

private:

};

#endif