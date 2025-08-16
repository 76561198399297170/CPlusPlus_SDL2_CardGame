#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>

#include "singleton.h"


class ResourcesManager : public Singleton<ResourcesManager>
{
	friend class Singleton<ResourcesManager>;
private:
	ResourcesManager() = default;

public:
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	ResourcesManager operator=(const ResourcesManager&) = delete;
	ResourcesManager operator=(const ResourcesManager&&) = delete;

	~ResourcesManager() = default;

	void loadResources(SDL_Renderer* renderer);

	Mix_Chunk* queryAudio(const std::string& name);
	SDL_Texture* queryTexture(const std::string& name, bool is_streaming = false);

private:
	std::unordered_map<std::string, Mix_Chunk*> m_audio_pool;
	std::unordered_map<std::string, SDL_Texture*> m_texture_pool;
	std::unordered_map<std::string, TTF_Font*> m_ttffont_pool;
	std::unordered_map<std::string, SDL_Texture*>m_streaming_texture_pool;

};

#endif

