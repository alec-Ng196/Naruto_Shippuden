//
// Created by Admin on 14/4/2024.
//

#ifndef NARUTOSHIPPUDEN_MAP_H
#define NARUTOSHIPPUDEN_MAP_H

#include "All_function.h"
#include "Base_code.h"

#define MAX_TILE 40
//Kế thừa từ Object
class TileMap : public Object{
public:
    TileMap() {;}
    ~TileMap() {;}
};
class Game_Map{
public:
    Game_Map() {;}
    ~Game_Map() {;}
    void LoadMap(char* name);
    void LoadingTiles(SDL_Renderer* screen);
    void DrawingMap(SDL_Renderer* screen);
    Map GetMap() {return game_map_;}
    void SetMap(Map& map_data) {game_map_ = map_data;}

private:
    Map game_map_;
    TileMap tile_map[MAX_TILE];

};

#endif //NARUTOSHIPPUDEN_MAP_H
