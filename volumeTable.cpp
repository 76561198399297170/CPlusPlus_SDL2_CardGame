#include "volumeTable.h"
#include "resourcesManager.h"
#include "cursorManager.h"
#include "utils.h"

extern ButtonFactory* button_factory;

extern int window_width;
extern int window_height;

VolumeTable::VolumeTable()
{
	this->m_ani_background = new Animation();
	this->m_ani_background_silde = new Animation();
	this->m_ani_volume = new Animation();

	this->m_btn_close = button_factory->create("Table_Exit", 950, 165);
	this->m_btn_close->addOnKeyupFunction([this]()
		{
			this->close();
		});

	this->m_btn_volume_slide = button_factory->create("Menu_Setting_Volume_Music", 385, 225);

	int w, h;

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("music_table"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_background->setDstFRect({ (window_width - w) / 2.0f, (window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_background->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background->addFramesFromSheetResource("music_table", 3, 60, false);
	this->m_ani_background->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("slide_background"), nullptr, nullptr, &w, &h);
	this->m_ani_background_silde->setDstFRect({ 340, 220, (float)w, (float)h });
	this->m_ani_background_silde->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background_silde->addFramesFromSheetResource("slide_background", 1, 1, false);
	this->m_ani_background_silde->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("volume_icon"), nullptr, nullptr, &w, &h);
	w /= 4;
	this->m_ani_volume->setDstFRect({ 290, 230, (float)w, (float)h });
	this->m_ani_volume->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_volume->addFramesFromSheetResource("volume_icon", 4, 60, false);
	this->m_ani_volume->play();
}

void VolumeTable::render(const Camera* camera)
{
	if (this->is_close) return;

	this->m_ani_background->render(camera);

	this->m_ani_volume->render(camera);
	this->m_ani_background_silde->render(camera);
	this->m_btn_volume_slide->render(camera->m_renderer);

	this->m_btn_close->render(camera->m_renderer);
}

void VolumeTable::update(float delta)
{
	if (this->is_close) return;

	this->m_ani_background_silde->update(delta);
	this->m_ani_volume->update(delta);
	this->m_btn_volume_slide->update(delta);

	this->m_btn_close->update(delta);
	this->m_ani_background->update(delta);
}

bool VolumeTable::input(SDL_Event& event)
{
	if (this->is_close) return true;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
	{
		this->close();
		return false;
	}
	this->m_btn_volume_slide->input(event);
	this->m_btn_close->input(event);

	return false;
}