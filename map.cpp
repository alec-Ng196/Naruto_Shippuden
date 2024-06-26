//
// Created by Admin on 14/4/2024.
//

#include "map.h"
#include <iostream>

void Game_Map::LoadMap(char* name){
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if(fp == NULL){
        return;
    }
    game_map_.end_x = 0;
    game_map_.end_y = 0;
    //0 0 0 0 1
    //1 1 1 1 1
    //2 1 1 2 1
    //1 1 2 2 2
    for(int i=0; i < MAX_MAP_Y; i++){
        for(int j=0; j < MAX_MAP_X; j++){
            fscanf(fp, "%d", &game_map_.tile[i][j]);
            int value = game_map_.tile[i][j];
            if(value > 0){
                if(j> game_map_.end_x){
                    game_map_.end_x = j;
                }
                if(i > game_map_.end_y){
                    game_map_.end_y = i;
                }
            }
        }
    }
    game_map_.end_x = (game_map_.end_x + 1)*TILE_SZ;
    game_map_.end_y = (game_map_.end_y + 1)*TILE_SZ;
}

void Game_Map::LoadingTiles(SDL_Renderer* screen){
    char file_img[30];
    FILE* fp =  nullptr;

    for(int i=0; i < MAX_TILE; i++){
        sprintf(file_img, "img\\%d.png", i);
        fopen_s(&fp, file_img, "rb");
        if(fp == nullptr){
            continue;
        }
        fclose(fp);
        tile_map[i].LoadingIMG(file_img, screen);

    }
}

void Game_Map::DrawingMap(SDL_Renderer* screen){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x= game_map_.begin_x/TILE_SZ;
    x1 = (game_map_.begin_x % TILE_SZ)* -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SZ);

    map_y = game_map_.begin_y/TILE_SZ;
    y1 = (game_map_.begin_y % TILE_SZ)* -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SZ);

    for(int i = y1; i <y2; i+= TILE_SZ){
        map_x = game_map_.begin_x/TILE_SZ;
        for(int j=x1; j < x2; j+= TILE_SZ){
            int value = game_map_.tile[map_y][map_x];
            if(value > 0){
                tile_map[value].setRect(j,i);
                tile_map[value].toRender(screen);
            }
            map_x++;
        }
        map_y++;
    }

}