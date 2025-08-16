#include "menuTable.h"
#include "dataManager.h"

MenuTable::MenuTable()
{
	this->m_tab_volume = new VolumeTable();
	this->m_tab_video = new VideoTable();
	this->m_tab_controls = new ControlsTable();

	this->m_ani_background = new Animation();

	this->m_btn_close = ButtonFactory::getInstance()->create("Table_Exit", 850, 25);
	this->m_btn_close->addOnKeyupFunction([this]()
		{
			this->close();
		});

	this->m_btn_volume = ButtonFactory::getInstance()->create("Menu_Setting_Volume", 380, 120);
	this->m_btn_volume->addOnKeyupFunction([this]() { this->m_tab_volume->open(); });

	this->m_btn_video = ButtonFactory::getInstance()->create("Menu_Setting_Video", 380, 270);
	this->m_btn_video->addOnKeyupFunction([this]() { this->m_tab_video->open(); });

	this->m_btn_control = ButtonFactory::getInstance()->create("Menu_Setting_Controls", 380, 420);
	this->m_btn_control->addOnKeyupFunction([this]() {this->m_tab_controls->open(); });

	int w, h;

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("setting_table"), nullptr, nullptr, &w, &h);
	w /= 3;

	this->m_ani_background->setDstFRect({ (DataManager::getInstance()->window_width - w) / 2.0f, (DataManager::getInstance()->window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_background->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background->addFramesFromSheetResource("setting_table", 3, 60, false);
	this->m_ani_background->play();

}

void MenuTable::render(const Camera* camera)
{
	if (this->is_close) return;

	this->m_ani_background->render(camera);
	this->m_btn_close->render(camera->m_renderer);

	this->m_btn_volume->render(camera->m_renderer);
	this->m_btn_video->render(camera->m_renderer);
	this->m_btn_control->render(camera->m_renderer);

	this->m_tab_volume->render(camera);
	this->m_tab_video->render(camera);
	this->m_tab_controls->render(camera);
}

void MenuTable::update(float delta)
{
	if (this->is_close) return;

	this->m_btn_close->update(delta);
	this->m_ani_background->update(delta);

	this->m_btn_volume->update(delta);
	this->m_btn_video->update(delta);
	this->m_btn_control->update(delta);

	this->m_tab_volume->update(delta);
	this->m_tab_video->update(delta);
	this->m_tab_controls->update(delta);
}

bool MenuTable::input(SDL_Event& event)
{
	if (this->is_close) return true;
	if (!this->m_tab_volume->input(event)) return false;
	else if (!this->m_tab_video->input(event)) return false;
	else if (!this->m_tab_controls->input(event)) return false;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		this->close();
		return false;
	}

	this->m_btn_close->input(event);

	this->m_btn_volume->input(event);
	this->m_btn_video->input(event);
	this->m_btn_control->input(event);

	return false;
}

void MenuTable::reload()
{
	this->m_tab_controls->reload();
	this->m_tab_video->reload();
	this->m_tab_volume->reload();
}