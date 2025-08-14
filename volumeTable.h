#ifndef _VOLUME_TABLE_H_
#define _VOLUME_TABLE_H_

#include "myTable.h"


class VolumeTable : public Table
{
public:
	VolumeTable();
	~VolumeTable() = default;

	virtual void render(const Camera* camera);
	virtual void update(float delta);
	virtual bool input(SDL_Event& event);

private:
	Button* m_btn_volume_slide;

	Animation* m_ani_background_silde;
	Animation* m_ani_volume;

};

#endif

