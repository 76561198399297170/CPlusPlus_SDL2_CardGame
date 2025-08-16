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
#include "dataManager.h"
#include "utils.h"


#define u8(x) u8##x

bool load_resources()
{
    std::ifstream file("./resources/setting.json");
    Json::CharReaderBuilder reader;
    Json::Value root;

    std::string errors;
    bool parseSuccess = Json::parseFromStream(reader, file, &root, &errors);
    if (!parseSuccess) return true;

    DataManager::getInstance()->is_shake = root["controls"]["vibration"].asBool();

    DataManager::getInstance()->window_width = root["video"]["width"].asInt();
    DataManager::getInstance()->window_height = root["video"]["height"].asInt();
    DataManager::getInstance()->is_vsync = root["video"]["vsync"].asBool();
    if (root["video"]["fullscreen"].asBool())
    {
        DataManager::getInstance()->is_full_screen = true;
        setFullScreen(DataManager::getInstance()->window, true);
    }

    setAllChannelsVolume(root["volume"]["music"].asInt());
    file.close();

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

    DataManager::getInstance()->window = SDL_CreateWindow(u8("你好，世界"), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DataManager::getInstance()->window_width, DataManager::getInstance()->window_height, SDL_WINDOW_SHOWN);

    if (load_resources()) return true;

    Uint32 flag = SDL_RENDERER_ACCELERATED;
    if (DataManager::getInstance()->is_vsync) flag |= SDL_RENDERER_PRESENTVSYNC;
    DataManager::getInstance()->renderer = SDL_CreateRenderer(DataManager::getInstance()->window, -1, flag);

    if (!DataManager::getInstance()->renderer) return true;

    SDL_ShowCursor(SDL_DISABLE);
    
    DataManager::getInstance()->res_mgr = ResourcesManager::getInstance();
    DataManager::getInstance()->res_mgr->getInstance()->loadResources(DataManager::getInstance()->renderer);

    DataManager::getInstance()->menu_scene = MenuScene::getInstance();
    DataManager::getInstance()->game_scene = GameScene::getInstance();

    DataManager::getInstance()->main_camera = new Camera(DataManager::getInstance()->renderer);

    DataManager::getInstance()->cur_mgr = CursorManager::getInstance();

    DataManager::getInstance()->scn_mgr = SceneManager::getInstance();
    DataManager::getInstance()->scn_mgr->getInstance()->setScene(DataManager::getInstance()->menu_scene);

    return false;
}

void deinit()
{
    delete_resources();

    delete DataManager::getInstance()->cur_mgr;
    delete DataManager::getInstance()->res_mgr;
    delete DataManager::getInstance()->main_camera;

    SDL_DestroyRenderer(DataManager::getInstance()->renderer);
    SDL_DestroyWindow(DataManager::getInstance()->window);

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
                DataManager::getInstance()->is_quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE) DataManager::getInstance()->main_camera->turnLight(3000);
            }

            DataManager::getInstance()->cur_mgr->getInstance()->input(event);
            DataManager::getInstance()->scn_mgr->getInstance()->input(event);
        }
        Uint64 current_counter = SDL_GetPerformanceCounter();
        double delta = (double)(current_counter - last_counter) / counter_freq;
        last_counter = current_counter;
        if (DataManager::getInstance()->is_quit) quit_timer.start();


        //数据处理
        if (DataManager::getInstance()->is_quit) quit_timer.update((float)delta * 1000.0);

        quit_timer.update((float)delta * 1000.0);
        DataManager::getInstance()->main_camera->update((float)delta * 1000.0);

        DataManager::getInstance()->scn_mgr->getInstance()->update((float)delta * 1000.0);


        //渲染绘制
        SDL_RenderClear(DataManager::getInstance()->renderer);
        SDL_SetRenderDrawColor(DataManager::getInstance()->renderer, 0, 0, 0, 255);

        DataManager::getInstance()->scn_mgr->getInstance()->render(DataManager::getInstance()->renderer, DataManager::getInstance()->main_camera);
        DataManager::getInstance()->main_camera->render();
        DataManager::getInstance()->cur_mgr->getInstance()->render(DataManager::getInstance()->renderer);

        SDL_RenderPresent(DataManager::getInstance()->renderer);


        //动态延时
        if (delta * 1000.0 < 1000.0 / DataManager::getInstance()->fps)
        {
            SDL_Delay((Uint32)(1000.0 / DataManager::getInstance()->fps - delta * 1000.0));
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
    videoSettings["width"] = DataManager::getInstance()->window_width;          //分辨率
    videoSettings["height"] = DataManager::getInstance()->window_height;        //分辨率
    videoSettings["fullscreen"] = DataManager::getInstance()->is_full_screen;   //是否全屏
    videoSettings["vsync"] = DataManager::getInstance()->is_vsync;              //垂直同步
    root["video"] = videoSettings;

    // 控制设置
    Json::Value controlSettings;
    controlSettings["vibration"] = DataManager::getInstance()->is_shake;        //振动反馈
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
    case CTRL_BREAK_EVENT:  // Ctrl+Break事件
        saveSetting();
        return TRUE;
    default:
        return FALSE;
    }
}

int main(int argc, char** argv)
{
    DataManager::getInstance();
    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) return 1;
    if (init()) return 1;

    mainloop();
    saveSetting();
    deinit();

    return 0;
}