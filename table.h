#ifndef _TABLE_H_
#define _TABLE_H_

#include<SDL_mixer.h>

#include "button.h"
#include "animation.h"
#include "resourcesManager.h"


class Table
{
public:
	Table() = default;
	~Table() = default;

	virtual void render(const Camera* camera) {}
	virtual void update(float delta) {}
	virtual bool input(SDL_Event& event) { return this->is_close; }
	virtual void reload() {};

	void open() { this->is_close = false; }
	void close() { this->is_close = true; }

	bool isClose() { return this->is_close; }

protected:
	bool is_close = true;

	Animation* m_ani_background;
	Button* m_btn_close;

};

#endif

