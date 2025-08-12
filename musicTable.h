#ifndef _MUSIC_TABLE_H_
#define _MUSIC_TABLE_H_

#include "myTable.h"


class MusicTable : public Table
{
public:
	MusicTable();
	~MusicTable() = default;

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual bool input(SDL_Event& event);

private:
	Button* m_btn_volume_slide; //音量滑动拉条
	Animation* m_btn_background_silde; //音量滑动背景

};

#endif

