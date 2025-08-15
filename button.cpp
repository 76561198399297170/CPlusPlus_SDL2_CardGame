#include "button.h"
#include "resourcesManager.h"
#include "cursorManager.h"
#include "sceneManager.h"
#include "utils.h"

extern SDL_Window* window;
extern Camera* main_camera;

extern bool is_quit;
extern bool is_full_screen;
extern bool is_vsync;
extern bool is_shake;
extern bool is_vsync_change;

Button* ButtonFactory::create(std::string button_type, int x, int y, bool is_streaming)
{
	Button* button = new Button();
	if (button_type == "Menu_Start")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("menu_start_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h};
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("menu_start_n", "menu_start_f", "menu_start_k", 3, 3, 3, 60, 60, 60);

		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				SceneManager::getInstance()->switchTo(SceneManager::SceneType::Game, 3000);
				button->m_tex_float->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Menu_Setting")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("menu_setting_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("menu_setting_n", "menu_setting_f", "menu_setting_k", 3, 3, 3, 60, 60, 60);

		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Menu_Exit")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("menu_exit_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("menu_exit_n", "menu_exit_f", "menu_exit_k", 3, 3, 3, 60, 60, 60);

		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_tex_float->play();
				is_quit = true;
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Table_Exit")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("exit_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("exit_n", "exit_f", "exit_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Menu_Setting_Volume")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("width_volume_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("width_volume_n", "width_volume_f", "width_volume_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
		}
	else if (button_type == "Menu_Setting_Video")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("width_video_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("width_video_n", "width_video_f", "width_video_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Menu_Setting_Controls")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("width_controls_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("width_controls_n", "width_controls_f", "width_controls_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Menu_Setting_Volume_Music")
	{
		int w, h;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("slide_switch_n", false), nullptr, nullptr, &w, &h);

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		int volume = Mix_Volume(-1, -1) * 4;

		button->m_rect_dst = { (float)x + volume, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };
		button->m_flag = { (float)x + volume, (float)y };
		button->m_flag_nmv = { 0.0f + volume, 0.0f };
		button->m_flag_pmv = { 512.0f - volume, 0.0f };

		button->setTextureSheet("slide_switch_n", "slide_switch_f", "slide_switch_k", 1, 1, 1, 1, 1, 1);
		button->setOnFloatFunction([button]()
			{
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_type = Button::ButtonType::Normal;
			});
		CursorManager* cur_mgr = CursorManager::getInstance();
		button->addOnMoveFunction([cur_mgr, button]()
			{
				int move_x = cur_mgr->getPosCurr().x - button->getCurrentAnimation()->getCurrRect().w / 2;
				button->m_move_base.m_x = std::max((int)(button->m_flag.m_x - button->m_flag_nmv.m_x), (int)move_x);
				button->m_move_base.m_x = std::min((int)(button->m_flag.m_x + button->m_flag_pmv.m_x), (int)button->m_move_base.m_x);
				button->m_move_base.m_x -= button->getPosition().m_x;

				Vector2 pos = button->getPosition() + button->m_move_base;
				button->setPosition(pos.m_x, pos.m_y + button->m_move_base.m_y);
				button->m_move_base = { 0.0f, 0.0f };
				
				setAllChannelsVolume(button->m_rect_dst.x - (button->m_flag.m_x - button->m_flag_nmv.m_x), 4);
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Full_Screen_Check_Box")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_t", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };
		button->is_show = is_full_screen;

		button->setTextureSheet("check_box_t", "check_box_t", "check_box_t", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
			});
		button->setOnKeyupFunction([button]()
			{
				is_full_screen = !is_full_screen;
				setFullScreen(window, is_full_screen);
				button->is_show = !button->is_show;
			});
		button->m_tex_normal->play();
		button->m_tex_float->play();
	}
	else if (button_type == "Set_Vsync_Check_Box")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_t", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };
		button->is_show = (is_vsync && !is_vsync_change);

		button->setTextureSheet("check_box_t", "check_box_t", "check_box_t", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
			});
		button->setOnKeyupFunction([button]()
			{
				is_vsync = !is_vsync;
				is_vsync_change = !is_vsync_change;
				button->is_show = !button->is_show;
			});
		button->m_tex_normal->play();
		button->m_tex_float->play();
	}
	else if (button_type == "Set_Shake_Check_Box")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("check_box_t", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };
		button->is_show = is_shake;

		button->setTextureSheet("check_box_t", "check_box_t", "check_box_t", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
			});
		button->setOnKeyupFunction([button]()
			{
				is_shake = !is_shake;
				button->is_show = !button->is_show;
			});
		button->m_tex_normal->play();
		button->m_tex_float->play();
	}
	else if (button_type == "Game_Setting")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("game_setting_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("game_setting_n", "game_setting_f", "game_setting_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}
	else if (button_type == "Game_Setting_Exit")
	{
		int w, h, n = 3;
		SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("width_exit_n", false), nullptr, nullptr, &w, &h);
		w /= n;

		button->m_rect_center = { w / 2.0f, h / 2.0f };
		button->m_rect_dst = { (float)x, (float)y, (float)w, (float)h };
		button->m_rect_src = { 0, 0, w, h };

		button->setTextureSheet("width_exit_n", "width_exit_f", "width_exit_k", 3, 3, 3, 60, 60, 60);
		button->setOnFloatFunction([button]()
			{
				button->m_tex_normal->reset();
				Mix_PlayChannel(-1, ResourcesManager::getInstance()->queryAudio("yee"), 0);
				button->m_tex_float->play();
			});
		button->setOutFloatFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_normal->play();
			});
		button->setOnKeydownFunction([button]()
			{
				button->m_tex_float->reset();
				button->m_tex_keydown->play();
			});
		button->setOnKeyupFunction([button]()
			{
				button->m_tex_keydown->reset();
				button->m_type = Button::ButtonType::Normal;
				button->m_tex_normal->play();
			});
		button->m_tex_normal->play();
	}

    return button;
}

Button::Button()
{
	this->m_tex_float = new Animation();
	this->m_tex_keydown = new Animation();
	this->m_tex_normal = new Animation();

	this->m_tex_normal->play();
}

Button::~Button()
{
	delete this->m_tex_float;
	delete this->m_tex_keydown;
	delete this->m_tex_normal;
}

void Button::render(SDL_Renderer* renderer, SDL_RendererFlip flip) const
{
	if (!this->is_show) return;
	const SDL_Rect& rt = this->getCurrentAnimation()->getCurrRect();
	SDL_FRect dt = this->m_rect_dst;
	dt.x += this->m_move_base.m_x, dt.y += this->m_move_base.m_y;

	SDL_RenderCopyExF(renderer, this->getCurrentAnimation()->getCurrentTexture(), &rt, &dt, this->m_angle, &this->m_rect_center, flip);
}

void Button::update(float delta)
{
	this->getCurrentAnimation()->update(delta);
}

void Button::input(SDL_Event& event)
{
	int x, y;
	if (event.type == SDL_MOUSEMOTION) x = event.motion.x, y = event.motion.y;
	else x = event.button.x, y = event.button.y;
	bool is_onbutton = (this->is_streaming ? this->isOnButton_ex(Vector2{ (float)x, (float)y }) : this->isOnButton(Vector2{ (float)x, (float)y }));

	if (event.type == SDL_MOUSEMOTION)//移动
	{
		if (this->m_type == ButtonType::KeyDown)
		{
			if (this->on_move) on_move();
			return;
		}

		if (this->m_type == ButtonType::Normal && is_onbutton)//进入悬浮
		{
			this->m_type = ButtonType::Float;
			this->on_onfloat();
		}
		else if (m_type == ButtonType::Float && !is_onbutton)//离开悬浮
		{
			this->m_type = ButtonType::Normal;
			this->on_outfloat();
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)//左键按下
	{
		if (is_onbutton && this->m_type != ButtonType::KeyDown)//按钮上非按下
		{
			this->m_type = ButtonType::KeyDown;
			this->on_keydown();
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)//左键松开
	{
		if (this->m_type == ButtonType::KeyDown)//按下松开
		{
			if (is_onbutton)//松开按钮内
			{
				this->m_type = ButtonType::Float;
				this->on_keyup();
			}
			else//松开按钮外
			{
				this->m_type = ButtonType::Normal;
				this->on_outfloat();
			}
			this->on_everykeyup();
		}
	}
}

void Button::restart()
{
	this->m_type = Button::ButtonType::Normal;
	this->m_tex_normal->reset();
	this->m_tex_float->reset();
	this->m_tex_keydown->reset();

	this->m_tex_normal->play();
}

void Button::addOnKeyupFunction(std::function<void()> func)
{
	std::function<void()> old_action = this->on_keyup;
	this->on_keyup = [old_action, func]()
		{
			if (old_action) old_action();
			func();
		};
}

void Button::addOnMoveFunction(std::function<void()> func)
{
	std::function<void()> old_action = this->on_move;
	this->on_move = [old_action, func]()
		{
			if (old_action) old_action();
			func();
		};
}

void Button::addEveryKeyupFunction(std::function<void()> func)
{
	std::function<void()> old_action = this->on_everykeyup;
	this->on_everykeyup = [old_action, func]()
		{
			if (old_action) old_action();
			func();
		};
}

void Button::setPosition(int x, int y)
{
	this->m_rect_dst.x = x, this->m_rect_dst.y = y;
}

void Button::setTexture(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_duration, int f_duration, int k_duration)
{
	this->is_streaming = false;
	this->m_tex_normal->clearAndAddFrameFromResource(tex_normal, this->m_rect_src, n_duration), this->m_tex_float->clearAndAddFrameFromResource(tex_float, this->m_rect_src, f_duration), this->m_tex_keydown->clearAndAddFrameFromResource(tex_keydown, this->m_rect_src, k_duration);
}

void Button::setTextureSheet(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_num, int f_num, int k_num, int n_duration, int f_duration, int k_duration)
{
	this->is_streaming = false;
	this->m_tex_normal->addFramesFromSheetResource(tex_normal, n_num, n_duration, this->is_streaming), this->m_tex_float->addFramesFromSheetResource(tex_float, f_num, f_duration, this->is_streaming), this->m_tex_keydown->addFramesFromSheetResource(tex_keydown, k_num, k_duration, this->is_streaming);
}

void Button::setTexture_ex(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_duration, int f_duration, int k_duration)
{
	this->is_streaming = true;
	this->m_tex_normal->clearAndAddFrameFromResource(tex_normal, this->m_rect_src, n_duration, true), this->m_tex_float->clearAndAddFrameFromResource(tex_float, this->m_rect_src, f_duration, true), this->m_tex_keydown->clearAndAddFrameFromResource(tex_keydown, this->m_rect_src, k_duration, true);
}

void Button::setTextureSheet_ex(std::string tex_normal, std::string tex_float, std::string tex_keydown, int n_num, int f_num, int k_num, int n_duration, int f_duration, int k_duration)
{
	this->is_streaming = true;
	this->m_tex_normal->addFramesFromSheetResource(tex_normal, n_num, n_duration, this->is_streaming), this->m_tex_float->addFramesFromSheetResource(tex_float, f_num, f_duration, this->is_streaming), this->m_tex_keydown->addFramesFromSheetResource(tex_keydown, k_num, 100, this->is_streaming);

}

bool Button::isOnButton(const Vector2& pos) const
{
	return (pos.m_x >= m_rect_dst.x && pos.m_x <= m_rect_dst.x + m_rect_dst.w && pos.m_y >= m_rect_dst.y && pos.m_y <= m_rect_dst.y + m_rect_dst.h);
}

bool Button::isOnButton(const SDL_Point& pos) const
{
	return this->isOnButton(Vector2{ (float)pos.x, (float)pos.y });
}

bool Button::isOnButton_ex(const Vector2& pos) const
{
	// 1. 快速矩形范围判断
	if (pos.m_x < m_rect_dst.x || pos.m_x >= m_rect_dst.x + m_rect_dst.w ||
		pos.m_y < m_rect_dst.y || pos.m_y >= m_rect_dst.y + m_rect_dst.h)
	{
		return false;
	}

	// 2. 获取当前纹理
	SDL_Texture* tex = getCurrentAnimation()->getCurrentTexture();
	if (!tex) return false;

	// 3. 检查纹理是否为流模式
	int access;
	if (SDL_QueryTexture(tex, nullptr, &access, nullptr, nullptr) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_QueryTexture failed: %s", SDL_GetError());
		return false;
	}
	if (access != SDL_TEXTUREACCESS_STREAMING)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture is not streaming");
		return false;
	}

	// 4. 获取纹理尺寸和格式
	int w, h;
	Uint32 format;
	if (SDL_QueryTexture(tex, &format, nullptr, &w, &h) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_QueryTexture failed: %s", SDL_GetError());
		return false;
	}

	// 5. 计算纹理坐标
	float scaleX = static_cast<float>(w) / m_rect_dst.w;
	float scaleY = static_cast<float>(h) / m_rect_dst.h;
	int texX = static_cast<int>((pos.m_x - m_rect_dst.x) * scaleX + 0.5f);
	int texY = static_cast<int>((pos.m_y - m_rect_dst.y) * scaleY + 0.5f);

	if (texX < 0 || texX >= w || texY < 0 || texY >= h)
	{
		return false;
	}

	// 6. 锁定纹理
	void* pixels;
	int pitch;
	// 锁定整个纹理（pitch是行字节数，不是像素字节数）
	if (SDL_LockTexture(tex, nullptr, &pixels, &pitch) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_LockTexture failed: %s", SDL_GetError());
		return false;
	}

	// 7. 提取alpha值（核心修正）
	Uint8 alpha = 0;
	Uint8* pixelData = static_cast<Uint8*>(pixels);

	// 计算每个像素的字节数（根据纹理格式）
	int bytesPerPixel = 0;
	switch (format)
	{
	case SDL_PIXELFORMAT_ARGB8888:
	case SDL_PIXELFORMAT_RGBA8888:
	case SDL_PIXELFORMAT_BGRA8888:
	case SDL_PIXELFORMAT_ABGR8888:
		bytesPerPixel = 4; // 32位格式，4字节/像素
		break;
	default:
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unsupported pixel format: 0x%X", format);
		SDL_UnlockTexture(tex);
		return false;
	}

	// 计算目标像素的内存地址（修正版）
	size_t pixelOffset = texY * pitch + texX * bytesPerPixel;
	Uint32* pixel = reinterpret_cast<Uint32*>(&pixelData[pixelOffset]);

	// 提取alpha值
	switch (format)
	{
	case SDL_PIXELFORMAT_ARGB8888:
		alpha = (*pixel >> 24) & 0xFF;
		break;
	case SDL_PIXELFORMAT_RGBA8888:
		alpha = *pixel & 0xFF;
		break;
	case SDL_PIXELFORMAT_BGRA8888:
		alpha = *pixel & 0xFF;
		break;
	case SDL_PIXELFORMAT_ABGR8888:
		alpha = (*pixel >> 24) & 0xFF;
		break;
	}

	SDL_UnlockTexture(tex);
	return alpha > 0;
}

bool Button::isOnButton_ex(const SDL_Point& pos) const
{
	return this->isOnButton_ex(Vector2{(float)pos.x, (float)pos.y});
}


Animation* Button::getCurrentAnimation() const
{
	switch (this->m_type)
	{
	case ButtonType::Normal:
		return this->m_tex_normal;
	case ButtonType::Float:
		return this->m_tex_float;
	case ButtonType::KeyDown:
		return this->m_tex_keydown;
	}
	return this->m_tex_normal;
}
