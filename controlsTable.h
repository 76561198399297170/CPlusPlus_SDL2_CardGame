#ifndef _CONTROLS_TABLE_H_
#define _CONTROLS_TABLE_H_

#include "myTable.h"
class ControlsTable : public Table
{
public:
	ControlsTable();
	~ControlsTable() = default;

	void render(const Camera* camera);
	void update(float delta);
	bool input(SDL_Event& event);

private:
	Button* m_btn_shake_check_box;

	Animation* m_ani_icon_shake;

	Animation* m_ani_bk_shake_check_box;

};

#endif // !_CONTROLS_TABLE_H_


