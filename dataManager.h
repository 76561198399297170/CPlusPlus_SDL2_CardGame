#ifndef _SETTINGS_MANAGER_H_
#define _SETTINGS_MANAGER_H_

#include "singleton.h"
#include <SDL.h>
#include "camera.h"
#include "gameScene.h"
#include "menuScene.h"
#include "cursorManager.h"
#include "sceneManager.h"

class DataManager : public Singleton<DataManager>
{
	friend class Singleton<DataManager>;
private:
	DataManager() = default;

public:
	DataManager(const DataManager&) = delete;
	DataManager(DataManager&&) = delete;
	DataManager operator=(const DataManager&) = delete;
	DataManager operator=(const DataManager&&) = delete;

	~DataManager() = default;

	SDL_Window* window = nullptr;//窗口
	SDL_Renderer* renderer = nullptr;//渲染器

	Camera* main_camera = nullptr;//主摄像头(摇晃、渐变亮暗)

	GameScene* game_scene = nullptr;//游戏场景
	MenuScene* menu_scene = nullptr;//菜单场景

	ResourcesManager* res_mgr = nullptr;//资源管理器
	CursorManager* cur_mgr = nullptr;//鼠标管理器
	SceneManager* scn_mgr = nullptr;//场景管理器


	bool is_quit = false;//是否准备退出

	bool is_shake = true;//是否启用屏幕摇晃

	bool is_full_screen = false;//是否全屏

	bool is_vsync = true;//垂直同步是否开启
	bool is_vsync_change = false;//运行时垂直同步修改

	int fps = 60;//刷新频率
	int font_size = 24;//字体大小(重进后生效)

	int window_width = 1280;//屏幕宽
	int window_height = 720;//屏幕高

	int game_camera_move_speed = 8;//游戏中主摄像头移动速度
};

#endif