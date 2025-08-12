#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <json/json.h>

#include <fstream>
#include <Windows.h>

#include "button.h"

#include "resourcesManager.h"
#include "cursorManager.h"
#include "sceneManager.h"

#include "camera.h"
#include "utils.h"


#define u8(x) u8##x


bool is_quit = false;
int fps = 60;

int volume_percentage = 80;

int window_width = 1280;
int window_height = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Camera* main_camera = nullptr;

GameScene* game_scene = nullptr;
MenuScene* menu_scene = nullptr;
MapScene* map_scene = nullptr;

ResourcesManager* res_mgr = nullptr;
CursorManager* cur_mgr = nullptr;
SceneManager* scn_mgr = nullptr;

ButtonFactory* button_factory;

void load_resources()
{
    menu_scene = MenuScene::getInstance();
    map_scene = MapScene::getInstance();
    game_scene = GameScene::getInstance();

    scn_mgr->getInstance()->switchTo(SceneManager::SceneType::Menu, false);
}

void delete_resources()
{
    delete button_factory;
}

void init()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(u8("你好，世界"), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_ShowCursor(SDL_DISABLE);

    main_camera = new Camera(renderer);
    
    res_mgr = ResourcesManager::getInstance();
    res_mgr->getInstance()->loadResources(renderer);
    cur_mgr = CursorManager::getInstance();
    scn_mgr = SceneManager::getInstance();

    button_factory = new ButtonFactory();

    load_resources();
}

void deinit()
{
    delete_resources();

    delete cur_mgr;
    delete res_mgr;
    delete main_camera;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void mainloop()
{
    bool quit_loop = false;

    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 counter_freq = SDL_GetPerformanceFrequency();

    SDL_Event event;
    
    Timer quit_timer;
    quit_timer.setDuration(2250);
    quit_timer.setCallback([&quit_loop]()
        {
            quit_loop = true;
        });

    while (!quit_loop)
    {
        //事件处理
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE) scn_mgr->switchTo(SceneManager::SceneType::Menu);
            }

            cur_mgr->getInstance()->input(event);
            scn_mgr->getInstance()->input(event);
        }
        Uint64 current_counter = SDL_GetPerformanceCounter();
        double delta = (double)(current_counter - last_counter) / counter_freq;
        last_counter = current_counter;
        if (is_quit) quit_timer.start();


        //数据处理
        if (is_quit) quit_timer.update((float)delta * 1000.0);

        quit_timer.update((float)delta * 1000.0);
        main_camera->update((float)delta * 1000.0);

        scn_mgr->getInstance()->update((float)delta * 1000.0);


        //渲染绘制
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        scn_mgr->getInstance()->render(renderer, main_camera);
        cur_mgr->getInstance()->render(renderer);

        SDL_RenderPresent(renderer);


        //动态延时
        if (delta * 1000.0 < 1000.0 / fps)
        {
            SDL_Delay((Uint32)(1000.0 / fps - delta * 1000.0));
        }
    }
}

int main(int argc, char** argv)
{
    init();
    mainloop();
    deinit();

    return 0;
}