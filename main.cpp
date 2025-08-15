#define SDL_MAIN_HANDLED

#include <SDL.h>
//#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <json/json.h>

#include <fstream>
#include <windows.h>

#include "button.h"

#include "resourcesManager.h"
#include "cursorManager.h"
#include "sceneManager.h"

#include "camera.h"
#include "utils.h"
#include <iostream>


#define u8(x) u8##x


bool is_quit = false;
bool is_shake = true;
bool is_full_screen = false;
bool is_vsync = true;
bool is_vsync_change = false;

int fps = 60;
int font_size = 24;

int window_width = 1280;
int window_height = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Camera* main_camera = nullptr;

GameScene* game_scene = nullptr;
MenuScene* menu_scene = nullptr;

ResourcesManager* res_mgr = nullptr;
CursorManager* cur_mgr = nullptr;
SceneManager* scn_mgr = nullptr;

bool load_resources()
{
    std::ifstream file("./resources/setting.json");
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errors;
    bool parseSuccess = Json::parseFromStream(reader, file, &root, &errors);
    if (!parseSuccess) return true;

    window_width = root["video"]["width"].asInt();
    window_height = root["video"]["height"].asInt();

    is_shake = root["controls"]["vibration"].asBool();
    setAllChannelsVolume(root["volume"]["music"].asInt());

    is_vsync = root["video"]["vsync"].asBool();

    if (root["video"]["fullscreen"].asBool())
    {
        is_full_screen = true;
        setFullScreen(window, true);
    }

    return false;
}

void delete_resources()
{

}

bool init()
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

    if (load_resources()) return true;

    Uint32 flag = SDL_RENDERER_ACCELERATED;
    if (is_vsync) flag |= SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, flag);

    if (!renderer) return true;

    SDL_ShowCursor(SDL_DISABLE);
    
    res_mgr = ResourcesManager::getInstance();
    res_mgr->getInstance()->loadResources(renderer);

    menu_scene = MenuScene::getInstance();
    game_scene = GameScene::getInstance();

    main_camera = new Camera(renderer);

    cur_mgr = CursorManager::getInstance();

    scn_mgr = SceneManager::getInstance();
    scn_mgr->getInstance()->setScene(menu_scene);

    return false;
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
    bool main_loop = false;

    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 counter_freq = SDL_GetPerformanceFrequency();

    SDL_Event event;
    
    Timer quit_timer;
    quit_timer.setDuration(/*2250*/0);
    quit_timer.setAutoRestart(true);
    quit_timer.setCallback([&main_loop]()
        {
            main_loop = true;
        });

    while (!main_loop)
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
                if (event.key.keysym.sym == SDLK_SPACE) main_camera->turnLight(3000);
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
        main_camera->render();
        cur_mgr->getInstance()->render(renderer);

        SDL_RenderPresent(renderer);


        //动态延时
        if (delta * 1000.0 < 1000.0 / fps)
        {
            SDL_Delay((Uint32)(1000.0 / fps - delta * 1000.0));
        }
    }
}

void saveSetting()
{
    Json::Value root;

    // 音量设置
    Json::Value volumeSettings;
    volumeSettings["music"] = Mix_Volume(-1, -1);   //音量大小
    root["volume"] = volumeSettings;

    // 视频设置
    Json::Value videoSettings;
    videoSettings["width"] = window_width;          //分辨率
    videoSettings["height"] = window_height;        //分辨率
    videoSettings["fullscreen"] = is_full_screen;   //是否全屏
    videoSettings["vsync"] = is_vsync;              //垂直同步
    root["video"] = videoSettings;

    // 控制设置
    Json::Value controlSettings;
    controlSettings["vibration"] = is_shake;        //振动反馈
    root["controls"] = controlSettings;

    Json::StreamWriterBuilder writer;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    std::ofstream file("./resources/setting.json");
    jsonWriter->write(root, &file);
}

BOOL WINAPI ConsoleHandler(DWORD event)
{
    switch (event)
    {
    case CTRL_LOGOFF_EVENT: // 用户注销
    case CTRL_SHUTDOWN_EVENT: // 系统关机
    case CTRL_CLOSE_EVENT:  // 捕获控制台窗口关闭事件
    case CTRL_C_EVENT:      // Ctrl+C事件
    case CTRL_BREAK_EVENT:  // Ctrl+Break事件[
        saveSetting();
        return TRUE;
    default:
        return FALSE;
    }
}

int main(int argc, char** argv)
{
    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) return 1;
    if (init()) return 1;

    mainloop();
    saveSetting();
    deinit();

    return 0;
}