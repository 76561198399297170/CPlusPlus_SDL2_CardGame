#include "controlsTable.h"

extern int window_width;
extern int window_height;

extern bool is_shake;

ControlsTable::ControlsTable()
{
	this->m_ani_background = new Animation();
	this->m_ani_bk_shake_check_box = new Animation();
	this->m_ani_icon_shake = new Animation();

	this->m_btn_close = ButtonFactory::getInstance()->create("Table_Exit", 950, 165);
	this->m_btn_close->addOnKeyupFunction([this]()
		{
			this->close();
		});

	this->m_btn_shake_check_box = ButtonFactory::getInstance()->create("Set_Shake_Check_Box", 800, 500);

	int w, h;

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("music_table"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_background->setDstFRect({ (window_width - w) / 2.0f, (window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_background->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background->addFramesFromSheetResource("music_table", 3, 60, false);
	this->m_ani_background->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("shake_icon"), nullptr, nullptr, &w, &h);
	this->m_ani_icon_shake->setDstFRect({ 500, 500, (float)w, (float)h });
	this->m_ani_icon_shake->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_icon_shake->addFramesFromSheetResource("shake_icon", 1, 1, false);
	this->m_ani_icon_shake->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_f"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_bk_shake_check_box->setDstFRect({ 800, 500, (float)w, (float)h });
	this->m_ani_bk_shake_check_box->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_bk_shake_check_box->addFramesFromSheetResource("check_box_f", 3, 60, false);
	this->m_ani_bk_shake_check_box->play();
}

void ControlsTable::render(const Camera* camera)
{
	if (this->is_close) return;

	this->m_ani_background->render(camera);

	this->m_btn_shake_check_box->render(camera->m_renderer);
	this->m_ani_bk_shake_check_box->render(camera);
	this->m_ani_icon_shake->render(camera);

	this->m_btn_close->render(camera->m_renderer);
}

void ControlsTable::update(float delta)
{
	if (this->is_close) return;

	this->m_btn_close->update(delta);
	this->m_btn_shake_check_box->update(delta);
	this->m_ani_background->update(delta);
	this->m_ani_bk_shake_check_box->update(delta);
	this->m_ani_icon_shake->update(delta);
}

bool ControlsTable::input(SDL_Event& event)
{
	if (this->is_close) return true;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		this->close();
		return false;
	}
	
	this->m_btn_shake_check_box->input(event);
	this->m_btn_close->input(event);
	return false;
}

void ControlsTable::reload()
{
	this->m_btn_shake_check_box->is_show = is_shake;
}