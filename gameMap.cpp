#include "gameMap.h"
#include "dataManager.h"
#include "resourcesManager.h"
#include <json/json.h>
#include <cmath>
#include <iostream>

MapPlace::MapPlace()
{
    this->m_ani_place = new Animation();

    this->m_ani_place->play();

}

void MapPlace::update(float delta)
{
    if (this->m_logic_x == 0 && this->m_logic_y == 0) std::cout << this->m_ani_place->getPosRect().x << "  " << this->m_ani_place->getPosRect().y << "\n";
    this->m_ani_place->update(delta);
}

void MapPlace::render(const Camera* camera)
{
    if (this->m_type == PlaceType::None) return;
    this->m_ani_place->render(camera, base);
}

void MapPlace::input(SDL_Event& event)
{
    //未完成
}

void MapPlace::reloadPlace()
{
    switch (this->m_type)
    {
    case PlaceType::Grass:
    {
        SDL_QueryTexture(ResourcesManager::getInstance()->queryTexture("game_place_grass"), nullptr, nullptr, &this->m_w, &this->m_h);
        this->m_w /= 2;
        this->m_ani_place->setDstFRect({ this->m_x, this->m_y, (float)this->m_w, (float)this->m_h });
        this->m_ani_place->setPlayMode(Animation::PlayMode::LOOP);
        this->m_ani_place->addFramesFromSheetResource("game_place_grass", 2, 60, false);
    }
    break;
    default:
    break;
    }
    this->m_ani_place->play();
}

void MapPlace::applyScale(float scale)
{
    this->m_current_scale = scale;
    this->m_ani_place->setScale(Vector2{ scale, scale });

    this->updateScaledPosition();
}

void MapPlace::setMapIndex(int x, int y)
{
    this->m_logic_x = x, this->m_logic_y = y;
    
    float scaled_base_x = this->base.m_x * this->m_current_scale;
    float scaled_base_y = this->base.m_y * this->m_current_scale;
    float scaled_w = this->m_w * this->m_current_scale;
    float scaled_h = this->m_h * this->m_current_scale;

    float scaled_offset_225 = 225 * this->m_current_scale;
    float scaled_offset_75 = 75 * this->m_current_scale;

    if (x & 1)
    {
        int adjusted_x = (x - 1) / 2;
        this->m_x = scaled_offset_225 + adjusted_x * scaled_w + adjusted_x * scaled_base_x;
        this->m_y = y * scaled_h;
    }
    else
    {
        int adjusted_x = x / 2;
        this->m_x = adjusted_x * scaled_w + adjusted_x * scaled_base_x;
        this->m_y = scaled_base_y + y * scaled_h;
    }
    this->m_ani_place->setDstFRect({ this->m_x, this->m_y, (float)this->m_w, (float)this->m_h });
}

void MapPlace::updateScaledPosition()
{
    setMapIndex(m_logic_x, m_logic_y);
}

/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */

bool GameMap::loadMapInf(Json::Value root_map)
{
    //读取游戏信息
    this->m_map_size = { (float)root_map["map"]["width"].asInt(), (float)root_map["map"]["height"].asInt() };
    this->m_map_scale = root_map["map"]["origin"].asFloat();
    
    //读取地图信息

    //读取玩家信息


    return false;
}

bool GameMap::saveMapInf()
{
    //未编写，需补充暂时设定为存储正确
    return false;
}

bool GameMap::createNewGame()
{
    this->m_map_size = { 30,15 };
    this->is_first_start = true;
    this->m_map_scale = 0.16f;

    this->m_map = new MapPlace * [this->m_map_size.m_y];
    for (int y = 0; y < this->m_map_size.m_y; y++)
    {
        this->m_map[y] = new MapPlace[this->m_map_size.m_x];
        for (int x = 0; x < this->m_map_size.m_x; x++)
        {
            this->m_map[y][x].setPlaceType(MapPlace::PlaceType::Grass);
            this->m_map[y][x].applyScale(this->m_map_scale);
            this->m_map[y][x].setMapIndex(x, y);
        }
    }

    return false;
}

void GameMap::update(float delta)
{
    std::cout << "scale: " << this->m_map_scale << "\n";
    for (int y = 0; y < this->m_map_size.m_y; y++)
    {
        for (int x = 0; x < this->m_map_size.m_x; x++)
        {
            this->m_map[y][x].update(delta);
        }
    }
}

void GameMap::render(SDL_Renderer* renderer, const Camera* camera)
{
    for (int y = 0; y < this->m_map_size.m_y; y++)
    {
        for (int x = 0; x < this->m_map_size.m_x; x++)
        {
            this->m_map[y][x].render(camera);
        }
    }

}

void GameMap::input(SDL_Event& event)
{
    for (int y = 0; y < this->m_map_size.m_y; y++)
    {
        for (int x = 0; x < this->m_map_size.m_x; x++)
        {
            this->m_map[y][x].input(event);
        }
    }
}

void GameMap::setScale(float scale)
{
    if (this->m_map_scale == scale) return;

    this->m_map_scale = scale;
    for (int y = 0; y < m_map_size.m_y; y++)
    {
        for (int x = 0; x < m_map_size.m_x; x++)
        {
            m_map[y][x].applyScale(m_map_scale);
        }
    }
}
