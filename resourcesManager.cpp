#include "resourcesManager.h"

#include <SDL_image.h>
#include <filesystem>
#include "dataManager.h"

void ResourcesManager::loadResources(SDL_Renderer* renderer)
{
	using namespace std::filesystem;

	std::filesystem::recursive_directory_iterator iter("resources",	std::filesystem::directory_options::skip_permission_denied);
	for (const auto& entry : iter)
	{
		if (entry.is_regular_file())
		{
			const path& path = entry.path();
			if (path.extension() == ".png")
			{
				SDL_Surface* surface = IMG_Load(path.u8string().c_str());
				SDL_Surface* converted_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
				SDL_FreeSurface(surface);

				SDL_Texture* streaming_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, converted_surface->w, converted_surface->h);
				void* pixels;
				int pitch;
				SDL_LockTexture(streaming_tex, nullptr, &pixels, &pitch);
				for (int y = 0; y < converted_surface->h; y++) memcpy((Uint8*)pixels + y * pitch, (Uint8*)converted_surface->pixels + y * converted_surface->pitch, converted_surface->pitch);

				SDL_UnlockTexture(streaming_tex);
				SDL_SetTextureBlendMode(streaming_tex, SDL_BLENDMODE_BLEND);

				this->m_streaming_texture_pool[path.stem().u8string()] = streaming_tex;

				SDL_Texture* normal_tex = SDL_CreateTextureFromSurface(renderer, converted_surface);
				SDL_SetTextureBlendMode(normal_tex, SDL_BLENDMODE_BLEND);

				this->m_texture_pool[path.stem().u8string()] = normal_tex;

				SDL_FreeSurface(converted_surface);
			}
			else if (path.extension() == ".mp3")
			{
				Mix_Chunk* audio = Mix_LoadWAV(path.u8string().c_str());

				this->m_audio_pool[path.stem().u8string()] = audio;
			}
			else if (path.extension() == ".ttf")
			{
				TTF_Font* font = TTF_OpenFont(path.u8string().c_str(), DataManager::getInstance()->font_size);

				this->m_ttffont_pool[path.stem().u8string()] = font;
			}
		}
	}
}

Mix_Chunk* ResourcesManager::queryAudio(const std::string& name)
{
	return this->m_audio_pool[name];
}

SDL_Texture* ResourcesManager::queryTexture(const std::string& name, bool is_streaming)
{
	return (is_streaming ? this->m_streaming_texture_pool[name] : this->m_texture_pool[name]);
}
