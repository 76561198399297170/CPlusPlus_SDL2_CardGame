#ifndef _MENU_TABLE_H_
#define _MENU_TABLE_H_

#include "volumeTable.h"
#include "videoTable.h"
#include "controlsTable.h"


class MenuTable : public Table
{
public:
	MenuTable();
	~MenuTable() = default;

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual bool input(SDL_Event& event);

private:
	Button* m_btn_volume;
	Button* m_btn_video;
	Button* m_btn_control;

	VolumeTable* m_tab_volume;
	VideoTable* m_tab_video;
	ControlsTable* m_tab_controls;
};

#endif

