#include "utils.h"
#include <algorithm>
#include <SDL_mixer.h>

void setAllChannelsVolume(int volume, int per)
{
    volume /= per;

    volume = std::min(volume, MIX_MAX_VOLUME);
    volume = std::max(volume, 0);
    Mix_Volume(-1, volume);
}
