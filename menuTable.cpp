#include "menuTable.h"

extern ButtonFactory* button_factory;

extern int window_width;
extern int window_height;

MenuTable::MenuTable()
{
	this->m_tab_music = new MusicTable();

	this->m_ani_background = new Animation();

	this->m_btn_close = button_factory->create("Table_Exit", 850, 25);
	this->m_btn_close->addOnKeyupFunction([this]()
		{
			this->close();
		});

	this->m_btn_music = button_factory->create("Menu_Setting_Music", 380, 120);
	this->m_btn_music->addOnKeyupFunction([this]()
		{
			this->m_tab_music->open();
		});

	int w, h;

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("setting_table"), nullptr, nullptr, &w, &h);
	w /= 3;

	this->m_ani_background->setDstFRect({ (window_width - w) / 2.0f, (window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_background->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background->addFramesFromSheetResource("setting_table", 3, 60, false);
	this->m_ani_background->play();

}

void MenuTable::render(const Camera* camera)
{
	if (this->is_close) return;

	this->m_ani_background->render(camera);
	this->m_btn_music->render(camera->m_renderer);
	this->m_btn_close->render(camera->m_renderer);

	this->m_tab_music->render(camera);
}

void MenuTable::update(float delta)
{
	if (this->is_close) return;
	this->m_tab_music->update(delta);
	this->m_btn_music->update(delta);
	this->m_btn_close->update(delta);
	this->m_ani_background->update(delta);
}

bool MenuTable::input(SDL_Event& event)
{
	if (this->is_close) return true;
	if (!this->m_tab_music->input(event)) return false;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		this->close();
		return false;
	}

	this->m_btn_close->input(event);
	this->m_btn_music->input(event);

	return false;
}