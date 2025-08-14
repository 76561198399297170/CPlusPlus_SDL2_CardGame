#ifndef _VIDEO_TABLE_H_
#define _VIDEO_TABLE_H_

#include "myTable.h"


class VideoTable : public Table
{
public:
	VideoTable();
	~VideoTable() = default;

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual bool input(SDL_Event& event);

private:
	Button* m_btn_screen_check_box;
	Button* m_btn_vsync_check_box;

	Animation* m_ani_icon_tips;
	Animation* m_ani_icon_full_screen;
	Animation* m_ani_icon_vsync;
	Animation* m_ani_bk_vsync_check_box;
	Animation* m_ani_bk_fullscreen_check_box;

};

#endif

