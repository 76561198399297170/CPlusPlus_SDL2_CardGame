#include "menuScene.h"
#include "resourcesManager.h"
#include "cursorManager.h"

#include <SDL_mixer.h>
#include "table.h"

extern int window_width;
extern int window_height;

extern Camera* main_camera;

MenuScene::MenuScene()
{
    this->m_tab_setting = new MenuTable();

    this->m_bk_sky = new Animation();
    this->m_bk_sun = new Animation();
    this->m_bk_plc = new Animation();

    this->m_btn_start = ButtonFactory::getInstance()->create("Menu_Start", 100, 100, true);
    this->m_btn_start->addOnKeyupFunction([this]()
        {
            MenuScene::getInstance()->setInput(false);
        });

    this->m_btn_setting = ButtonFactory::getInstance()->create("Menu_Setting", 100, 300, true);
    this->m_btn_setting->addOnKeyupFunction([this]()
        {
            this->m_tab_setting->open();
        });

    this->m_btn_exit = ButtonFactory::getInstance()->create("Menu_Exit", 100, 500, true);

    int w, h;

    SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("background_menu_sky"), nullptr, nullptr, &w, &h);
    this->m_bk_sky->setPlayMode(Animation::PlayMode::LOOP);
    this->m_bk_sky->setDstFRect({ 0.0f, 0.0f, (float)window_width, (float)window_height });
    this->m_bk_sky->addFrame(ResourcesManager::getInstance()->queryTexture("background_menu_sky"), { 0, 0, w, h }, 1.0f);
    
    this->m_bk_sky->setPosition(0, -800);
    this->m_bk_sky->setScale(Vector2{ 3.5, 3.5f });
    this->m_bk_sky->addFrameChangedAction([this]()
        {
            static int move_pos = 20;
            static int dir = -1;
            this->m_bk_sky->m_dst_rect.x += dir, move_pos -= dir;
            if (move_pos == 10 || move_pos == 2500) dir *= -1;
        });
    this->m_bk_sky->play();


    SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("background_menu_sun"), nullptr, nullptr, &w, &h);
    this->m_bk_sun->setPlayMode(Animation::PlayMode::LOOP);
    this->m_bk_sun->setOrigin({ 1116.0f, 110.0f });
    this->m_bk_sun->setDstFRect({ 0.0f, 0.0f, (float)window_width, (float)window_height });
    this->m_bk_sun->addFrame(ResourcesManager::getInstance()->queryTexture("background_menu_sun"), { 0, 0, w, h }, 1.0f);

    this->m_bk_sun->addFrameChangedAction([this]()
        {
            this->m_bk_sun->addRotation(6);
        });
    this->m_bk_sun->play();


    SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("background_menu_grass"), nullptr, nullptr, &w, &h);
    this->m_bk_plc->setPlayMode(Animation::PlayMode::LOOP);
    this->m_bk_plc->setDstFRect({ 0.0f, 0.0f, (float)window_width, (float)window_height });
    this->m_bk_plc->addFrame(ResourcesManager::getInstance()->queryTexture("background_menu_grass"), { 0, 0, w, h }, 1.0f);
}

void MenuScene::enter()
{
    this->is_input = true;

    this->m_tab_setting->reload();
    this->m_btn_start->restart();
    this->m_btn_setting->restart();
    this->m_btn_exit->restart();

    this->m_tab_setting->close();

    main_camera->turnLight(2000);
    this->m_music_cannel = Mix_FadeInChannel(-1, ResourcesManager::getInstance()->queryAudio("background_music"), -1, 3500);
}

void MenuScene::exit()
{
    main_camera->turnLight(2000);
    Mix_FadeOutChannel(MenuScene::getInstance()->m_music_cannel, 2500);
}

void MenuScene::render(const Camera* camera)
{
    this->m_bk_sky->render(camera);
    this->m_bk_sun->render(camera);
    this->m_bk_plc->render(camera);

    this->m_btn_start->render(camera->m_renderer);
    this->m_btn_setting->render(camera->m_renderer);
    this->m_btn_exit->render(camera->m_renderer);

    this->m_tab_setting->render(camera);
}

void MenuScene::update(float delta)
{
    this->m_bk_sky->update(delta);
    this->m_bk_sun->update(delta);
    this->m_bk_plc->update(delta);

    this->m_btn_start->update(delta);
    this->m_btn_setting->update(delta);
    this->m_btn_exit->update(delta);

    this->m_tab_setting->update(delta);
}

void MenuScene::input(SDL_Event& event)
{
    if (!this->is_input) return;

    if (!this->m_tab_setting->input(event)) return;

    this->m_btn_start->input(event);
    this->m_btn_setting->input(event);
    this->m_btn_exit->input(event);
}