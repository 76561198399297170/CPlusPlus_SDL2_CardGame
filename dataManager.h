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

	SDL_Window* window = nullptr;//����
	SDL_Renderer* renderer = nullptr;//��Ⱦ��

	Camera* main_camera = nullptr;//������ͷ(ҡ�Ρ���������)

	GameScene* game_scene = nullptr;//��Ϸ����
	MenuScene* menu_scene = nullptr;//�˵�����

	ResourcesManager* res_mgr = nullptr;//��Դ������
	CursorManager* cur_mgr = nullptr;//��������
	SceneManager* scn_mgr = nullptr;//����������


	bool is_quit = false;//�Ƿ�׼���˳�

	bool is_shake = true;//�Ƿ�������Ļҡ��

	bool is_full_screen = false;//�Ƿ�ȫ��

	bool is_vsync = true;//��ֱͬ���Ƿ���
	bool is_vsync_change = false;//����ʱ��ֱͬ���޸�

	int fps = 60;//ˢ��Ƶ��
	int font_size = 24;//�����С(�ؽ�����Ч)

	int window_width = 1280;//��Ļ��
	int window_height = 720;//��Ļ��

	int game_camera_move_speed = 8;//��Ϸ��������ͷ�ƶ��ٶ�
};

#endif