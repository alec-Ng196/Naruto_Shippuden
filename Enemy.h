//
// Created by Admin on 22/4/2024.
//

#ifndef NARUTOSHIPPUDEN_ENEMY_H
#define NARUTOSHIPPUDEN_ENEMY_H

#include "All_function.h"
#include "Base_code.h"
#include "Shuriken.h"
#include<bits/stdc++.h>
#define  Enemy_FRAME 8
#define Falling_SPEED 0.8
#define Enemy_MAX_FALL 10
#define Frame_Rate 60
#define ENEMY_SPEED 5
#define HP_OBITO 3


using namespace std;
const int FRAME_DURATION = 1000 / Frame_Rate;

class Enemy : public Object{
public:
    Enemy();
    ~Enemy();

    enum TypeMove{
        STATIC_OBJ = 0,
        MOVEABLE_OBJ = 1,
    };

    void SetX_value(const float& x_val_){x_val = x_val_;}
    void SetY_value(const float& y_val_){y_val = y_val_;}
    void SetX_pos(const float& x_pos_) {x_pos = x_pos_;}
    void SetY_pos(const float& y_pos_ ) {y_pos = y_pos_;}

    float getX_pos() const {return x_pos;}
    float getY_pos() const {return y_pos;}

    void Set_MapXY(const int& mpX, const int& mpY){
        map_x_ = mpX;
        map_y_ = mpY;
    }

    void set_clips();
    bool LoadingIMG(std::string path, SDL_Renderer* screen);
    void ShowEnemy(SDL_Renderer* des);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    SDL_Rect GetRectFRAME();

    void ENEMY_Action(Map& g_map);
    void check_MAP(Map& g_map);
    void InitEnemy();

    void set_type_Move(const int& genreMove){move_genre = genreMove;}
    void set_AnimationPos(const int& pos_A, const int& pos_B){
        animation_first = pos_A;
        animation_last = pos_B;
    }
    void set_input_LEFT(const int& ipLeft){
        input_type.left = ipLeft;
    }
    void ImpMoveType(SDL_Renderer* screen);
    void HealthDecrease(){health_enemy -= 1;}
    int get_enemy_hp() const {return health_enemy;}
    void Enemy_renderHP(SDL_Renderer* screen, Enemy* enemies);

    vector<Shuriken*> get_fire_list() {return Fire_ball_list;}
    void set_fire_list(const vector<Shuriken*>& bl_list) {Fire_ball_list = bl_list;}

    void InitFire(Shuriken* p_fire, SDL_Renderer* screen);
    void MakeFireJujutsu(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveFire(const int& idx);

    bool is_knocked = false;

private:
    int map_x_;
    int map_y_;
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    bool is_ground;
    int comeback_time;
    SDL_Rect frame_clips[Enemy_FRAME];
    int width_frame;
    int height_frame;
    int frame;
    int last_FRAME;

    //Doi tuong co the di chuyen
    int move_genre;
    int animation_first;
    int animation_last;
    int health_enemy;

    Input input_type;

    //Thêm đạn bắn cho enemy
    vector<Shuriken*> Fire_ball_list;
};
#endif //NARUTOSHIPPUDEN_ENEMY_H
