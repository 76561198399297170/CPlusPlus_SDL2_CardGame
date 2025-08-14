#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL.h>
#include <cmath>

//设置所有通道音量
int setAllChannelsVolume(int volume, int per = 1);

//设置是否全屏
void setFullScreen(SDL_Window* window, bool is_full);

//设置屏幕分辨率
void resizeWindow(SDL_Window* window, SDL_Renderer* renderer, int width, int height);

//渲染指定矩形
void copyexRect(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h);

#endif