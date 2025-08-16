#include "utils.h"
#include <algorithm>
#include <SDL_mixer.h>
#include "dataManager.h"

int setAllChannelsVolume(int volume, int per)
{
    volume /= per;

    volume = std::min(volume, MIX_MAX_VOLUME);
    volume = std::max(volume, 0);
    Mix_Volume(-1, volume);

    return volume;
}

void setFullScreen(SDL_Window* window, bool is_full)
{
    Uint32 flags = is_full ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    SDL_SetWindowFullscreen(window, flags);

    if (!is_full)
    {
        SDL_SetWindowSize(window, DataManager::getInstance()->window_width, DataManager::getInstance()->window_height);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
}

void resizeWindow(SDL_Window* window, SDL_Renderer* renderer, int width, int height)
{
    int newWidth = std::max(width, 320);
    int newHeight = std::max(height, 240);

    SDL_SetWindowSize(window, newWidth, newHeight);

    SDL_Rect viewport = { 0, 0, newWidth, newHeight };
    SDL_RenderSetViewport(renderer, &viewport);
}

void copyexRect(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int w, int h)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
