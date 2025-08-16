#include "gameMap.h"
#include "dataManager.h"
#include "resourcesManager.h"
#include <fstream>
#include <json/json.h>

MapPlace::MapPlace()
{
    this->m_ani_place = new Animation();

    this->m_ani_place->play();

}

void MapPlace::update(float delta)
{
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

void MapPlace::setMapIndex(int x, int y)
{
    if (x & 1)
    {
        x = (x - 1) / 2;
        this->m_x = 225 + x * this->base.m_x + x * this->m_w;
        this->m_y = y * this->m_h;
    }
    else
    {
        x /= 2;
        this->m_x = x * this->base.m_x + x * this->m_w;
        this->m_y = this->base.m_y + y * this->m_h;
    }

    this->m_ani_place->setDstFRect({ this->m_x, this->m_y, (float)this->m_w, (float)this->m_h });
}

/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */

GameMap::GameMap()
{
    if (this->loadMapInf())
    {
        //创建地图
        if (this->saveMapInf())
        {
            //存储失败
            return;
        }
        //存储成功
        return;
    }
    //读取地图


}

bool GameMap::loadMapInf()
{
    this->is_first_start = false;

    std::ifstream file("./save/save.json");
    Json::CharReaderBuilder reader;
    Json::Value root;

    std::string errors;
    bool parseSuccess = Json::parseFromStream(reader, file, &root, &errors);
    if (!parseSuccess || true)//==========tips==========
    {
        this->m_map_size = { 3, 5 };
        if (this->createNewGame()) return true;
        return false;
    }
    system("pause");
    this->m_map_size = { (float)root["map"]["width"].asInt(), (float)root["map"]["height"].asInt() };
    return false;
}

bool GameMap::saveMapInf()
{
    return true;
}

bool GameMap::createNewGame()
{
    this->is_first_start = true;

    this->m_map = new MapPlace * [this->m_map_size.m_y];
    for (int y = 0; y < this->m_map_size.m_y; y++)
    {
        this->m_map[y] = new MapPlace[this->m_map_size.m_x];
        for (int x = 0; x < this->m_map_size.m_x; x++)
        {
            this->m_map[y][x].setPlaceType(MapPlace::PlaceType::Grass);
            this->m_map[y][x].setMapIndex(x, y);
        }
    }

    return true;
}

void GameMap::update(float delta)
{
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