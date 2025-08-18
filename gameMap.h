#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <SDL.h>
#include "vector2.h"
#include "camera.h"
#include "animation.h"
#include <json/json.h>


class MapPlace
{
public:
	enum class PlaceType
	{
		None,	//未知
		Grass	//草地
	};

public:
	MapPlace();
	~MapPlace() = default;

	void update(float delta);
	void render(const Camera* camera);
	void input(SDL_Event& event);

	void reloadPlace();

	void applyScale(float scale);

	void setPlaceType(PlaceType type) { this->m_type = type; this->reloadPlace(); }
	void setMapIndex(int x, int y);
	void setPosition(float x, float y) { this->m_logic_x = x, this->m_logic_y = y; }

	void updateScaledPosition();

public:
	const Vector2 base{ 150, 150 };//六边形地块边长

	int m_w, m_h;

private:
	PlaceType m_type = PlaceType::None;

	float m_current_scale = 1.0f;

	int m_logic_x = 0;
	int m_logic_y = 0;
	float m_x = 0;
	float m_y = 0;
	Animation* m_ani_place;

	
};

class GameMap
{
public:
	GameMap() = default;
	~GameMap() = default;

	bool createNewGame();

	bool loadMapInf(Json::Value root_map);
	bool saveMapInf();

	void update(float delta);
	void render(SDL_Renderer* renderer, const Camera* camera);
	void input(SDL_Event& event);

	float getMapMid_x() { return this->m_map_size.m_x * this->m_map[0][0].m_w * this->m_map_scale; }
	float getMapMid_y() { return this->m_map_size.m_y * this->m_map[0][0].m_h * this->m_map_scale; }

	void setScale(float scale);

	float getScale() { return this->m_map_scale; }

private:
	bool is_first_start = false;

	float m_map_scale = 1.0;
	Vector2 m_map_size = { 0.0f, 0.0f };

	MapPlace** m_map = nullptr;

};

#endif
