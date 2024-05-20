//
// Created by Admin on 30/4/2024.
//

#ifndef NARUTOSHIPPUDEN_BOSS_H
#define NARUTOSHIPPUDEN_BOSS_H

#include "Base_code.h"
#include "All_function.h"
#include "Shuriken.h"

#define Gravity_Boss 1.0
#define MAX_FALL_SPEED 10
#define Boss_SPEED 2
#define BOSS_HIGH_VAL 18 //Toc do roi xuong
#define SUSANO_BOSS_HP 9
#define BOSS_FRAME_NUM 20


class BossObj : public Object{
public:
    BossObj();
    ~BossObj();
    void set_Xval(float x_val_){x_val = x_val_;}
    void set_Yval(float y_val_){y_val = y_val_;}

    void set_Xpos(const int& xp_){ Xpos = xp_;}
    void set_Ypos(const int& yp_) {Ypos = yp_;}

    void Show_BOSS(SDL_Renderer* des);
    bool LoadingIMG(std::string path, SDL_Renderer* screen);
    void set_clips_();
    void reset();

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    SDL_Rect GetRectFRAME();
    void Map_vision(const int map_x, const int map_y){
        map_x_ = map_x;
        map_y_ = map_y;
    }

    void Check_toMap(Map& g_map);
    void CenterEntityOnMap(Map& g_map);
    void Boss_Action(Map& g_map);
    void InitBOSS();
    void HP_BOSS_Decrease() {health_boss -= 1;}
    int get_boss_HP() const {return health_boss;}
    void boss_renderHP(SDL_Renderer* des, BossObj* bosses);

    std::vector<Shuriken*> get_bullet_list() const {return bullet_list;}
    void set_bullet_list(const std::vector<Shuriken*>& bl_list){bullet_list = bl_list;}

    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);


private:
    int map_x_;
    int map_y_;
    float x_val;
    float y_val;
    int Xpos;
    int Ypos;
    int width_frame_;
    int height_frame_;
    int on_ground;
    int think_time;
    int frame;
    SDL_Rect frame_clip_[BOSS_FRAME_NUM];
    std::vector<Shuriken*> bullet_list;
    Input input_type;
    int last_fr_;
    int health_boss;

};
#endif //NARUTOSHIPPUDEN_BOSS_H
