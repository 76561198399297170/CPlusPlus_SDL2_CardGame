#ifndef _MENU_TABLE_H_
#define _MENU_TABLE_H_

#include "musicTable.h"


class MenuTable : public Table
{
public:
	MenuTable();
	~MenuTable() = default;

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual bool input(SDL_Event& event);

private:
	Button* m_btn_music;

	MusicTable* m_tab_music;

};

#endif

