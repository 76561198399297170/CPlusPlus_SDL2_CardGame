#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL.h>
#include <cmath>

//��������ͨ������
int setAllChannelsVolume(int volume, int per = 1);

//�����Ƿ�ȫ��
void setFullScreen(SDL_Window* window, bool is_full);

//������Ļ�ֱ���
void resizeWindow(SDL_Window* window, SDL_Renderer* renderer, int width, int height);

//��Ⱦָ������
void copyexRect(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h);

#endif