#include "videoTable.h"

extern int window_width;
extern int window_height;

extern bool is_full_screen;
extern bool is_vsync;
extern bool is_vsync_change;

VideoTable::VideoTable()
{
	this->m_ani_icon_vsync = new Animation();
	this->m_ani_background = new Animation();
	this->m_ani_bk_fullscreen_check_box = new Animation();
	this->m_ani_bk_vsync_check_box = new Animation();
	this->m_ani_icon_full_screen = new Animation();
	this->m_ani_icon_tips = new Animation();

	this->m_btn_screen_check_box = ButtonFactory::getInstance()->create("Full_Screen_Check_Box", 800, 500);

	this->m_btn_close = ButtonFactory::getInstance()->create("Table_Exit", 950, 165);
	this->m_btn_close->addOnKeyupFunction([this]()
		{
			this->close();
		});

	this->m_ani_icon_tips->is_show = is_vsync_change;
	this->m_btn_vsync_check_box = ButtonFactory::getInstance()->create("Set_Vsync_Check_Box", 800, 400);
	this->m_btn_vsync_check_box->addOnKeyupFunction([this]()
		{
			//this->m_ani_icon_tips->is_show = !this->m_ani_icon_tips->is_show;
			this->m_ani_icon_tips->is_show = is_vsync_change;
		});

	int w, h;

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("music_table"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_background->setDstFRect({ (window_width - w) / 2.0f, (window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_background->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_background->addFramesFromSheetResource("music_table", 3, 60, false);
	this->m_ani_background->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("full_screen_icon"), nullptr, nullptr, &w, &h);
	this->m_ani_icon_full_screen->setDstFRect({ 500, 500, (float)w, (float)h });
	this->m_ani_icon_full_screen->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_icon_full_screen->addFramesFromSheetResource("full_screen_icon", 1, 1, false);
	this->m_ani_icon_full_screen->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("vsync_icon"), nullptr, nullptr, &w, &h);
	this->m_ani_icon_vsync->setDstFRect({ 500, 400, (float)w, (float)h });
	this->m_ani_icon_vsync->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_icon_vsync->addFramesFromSheetResource("vsync_icon", 1, 1, false);
	this->m_ani_icon_vsync->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("setting_change_tips"), nullptr, nullptr, &w, &h);
	this->m_ani_icon_tips->setDstFRect({ (window_width - w) / 2.0f, (window_height - h) / 2.0f, (float)w, (float)h });
	this->m_ani_icon_tips->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_icon_tips->addFramesFromSheetResource("setting_change_tips", 1, 1, false);
	this->m_ani_icon_tips->is_show = false;
	this->m_ani_icon_tips->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_f"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_bk_fullscreen_check_box->setDstFRect({ 800, 500, (float)w, (float)h });
	this->m_ani_bk_fullscreen_check_box->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_bk_fullscreen_check_box->addFramesFromSheetResource("check_box_f", 3, 60, false);
	this->m_ani_bk_fullscreen_check_box->play();

	SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_f"), nullptr, nullptr, &w, &h);
	w /= 3;
	this->m_ani_bk_vsync_check_box->setDstFRect({ 800, 400, (float)w, (float)h });
	this->m_ani_bk_vsync_check_box->setPlayMode(Animation::PlayMode::LOOP);
	this->m_ani_bk_vsync_check_box->addFramesFromSheetResource("check_box_f", 3, 60, false);
	this->m_ani_bk_vsync_check_box->play();
}

void VideoTable::render(const Camera* camera)
{
	if (this->is_close) return;

	this->m_ani_background->render(camera);
	
	this->m_ani_bk_fullscreen_check_box->render(camera);
	this->m_ani_bk_vsync_check_box->render(camera);
	this->m_ani_icon_full_screen->render(camera);
	this->m_ani_icon_vsync->render(camera);
	this->m_ani_icon_tips->render(camera);
	this->m_btn_screen_check_box->render(camera->m_renderer);
	this->m_btn_vsync_check_box->render(camera->m_renderer);

	this->m_btn_close->render(camera->m_renderer);
}

void VideoTable::update(float delta)
{
	if (this->is_close) return;

	this->m_btn_screen_check_box->update(delta);
	this->m_btn_vsync_check_box->update(delta);
	this->m_ani_icon_full_screen->update(delta);
	this->m_ani_icon_vsync->update(delta);
	this->m_ani_icon_tips->update(delta);
	this->m_ani_bk_fullscreen_check_box->update(delta);
	this->m_ani_bk_vsync_check_box->update(delta);

	this->m_btn_close->update(delta);
	this->m_ani_background->update(delta);
}

bool VideoTable::input(SDL_Event& event)
{
	if (this->is_close) return true;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		this->close();
		return false;
	}
	this->m_btn_vsync_check_box->input(event);
	this->m_btn_screen_check_box->input(event);
	this->m_btn_close->input(event);

	return false;
}

void VideoTable::reload()
{
	this->m_btn_screen_check_box->is_show = is_full_screen;
	this->m_btn_vsync_check_box->is_show = is_vsync;

	this->m_ani_icon_tips->is_show = is_vsync_change;
}