#ifndef _GAME_TABLE_H_
#define _GAME_TABLE_H_

#include "table.h"
#include "volumeTable.h"
#include "videoTable.h"
#include "controlsTable.h"


class GameTable : public Table
{
public:
	GameTable();
	~GameTable() = default;

	void render(const Camera* camera);
	void update(float delta);
	bool input(SDL_Event& event);
	void reload();

private:
	Button* m_btn_volume;
	Button* m_btn_video;
	Button* m_btn_control;
	Button* m_btn_exit;

	VolumeTable* m_tab_volume;
	VideoTable* m_tab_video;
	ControlsTable* m_tab_controls;

};

#endif

