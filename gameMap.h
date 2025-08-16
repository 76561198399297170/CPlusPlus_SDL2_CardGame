#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <SDL.h>
#include "vector2.h"
#include "camera.h"
#include "animation.h"


class MapPlace
{
public:
	enum class PlaceType
	{
		None,	//Î´Öª
		Grass	//²ÝµØ
	};

public:
	MapPlace();
	~MapPlace() = default;

	void update(float delta);
	void render(const Camera* camera);
	void input(SDL_Event& event);

	void reloadPlace();

	void setPlaceType(PlaceType type) { this->m_type = type; this->reloadPlace(); }
	void setMapIndex(int x, int y);
	void setPosition(float x, float y) { this->m_x = x, this->m_y = y; }

public:
	const Vector2 base{ 150, 150 };

private:
	PlaceType m_type = PlaceType::None;

	float m_x, m_y;
	int m_w, m_h;
	Animation* m_ani_place;

	
};

class GameMap
{
public:
	GameMap();
	~GameMap() = default;

	bool createNewGame();

	bool loadMapInf();
	bool saveMapInf();


	void update(float delta);
	void render(SDL_Renderer* renderer, const Camera* camera);
	void input(SDL_Event& event);
private:
	bool is_first_start = true;

	Vector2 m_map_size;

	MapPlace** m_map;


};

#endif
