#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "scene.h"
#include "singleton.h"
#include "animation.h"

#include "menuTable.h"


class MenuScene : public Scene, public Singleton<MenuScene>
{
	friend class Singleton<MenuScene>;
public:
	MenuScene();
	~MenuScene() = default;

	virtual void enter();
	virtual void exit();

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual void input(SDL_Event& event);

private:
	int m_music_cannel;

	Animation* m_bk_sky;
	Animation* m_bk_sun;
	Animation* m_bk_plc;

	Button* m_btn_start;
	Button* m_btn_setting;
	Button* m_btn_exit;

	MenuTable* m_tab_setting;

};

#endif