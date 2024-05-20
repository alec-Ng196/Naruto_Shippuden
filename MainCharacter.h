//
// Created by Admin on 14/4/2024.
//

#ifndef NARUTOSHIPPUDEN_MAINCHARACTER_H
#define NARUTOSHIPPUDEN_MAINCHARACTER_H

#include <vector>
#include "All_function.h"
#include "Base_code.h"
#include "Shuriken.h"

#define MAX_FALL_SPEED 12
#define PLAYER_SPEED 8
#define PLAYER_JUMP 20
#define MAX_MANA 35

using namespace std;
class MainObject : public Object{
public:
    MainObject();
    ~MainObject();
    enum WalkType{
        Fall_reset = 0,
        Walk_right = 1,
        Walk_left = 2,
        Jumping = 3,
        Idle = 4,
        Attack = 5,
        Guarding = 6,
    };
    void reset();
    bool LoadingIMG(std::string path, SDL_Renderer* screen);
    void ShowMain(SDL_Renderer* des);
    void Handle(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
    void Player_action(Map& map_data);
    void check_map(Map& map_data);
    void Map_vision(const int map_x, const int map_y){
        map_x_ = map_x;
        map_y_ = map_y;
    }
    void SET_Mapvision(Map& map_data);
    void UpdateStats(SDL_Renderer* des); // Liên tục cập nhật hinh anh cho nhan vat
    void Set_first_move();

    SDL_Rect GetRectFRAME();
    int get_naruto_hp() const {return health_naruto;}

    vector<Shuriken*> get_Shuri_packages() const {return rasen_shuri;}
    void Throw_Shuri(SDL_Renderer* des);

    void RemoveShuri(const int& index);
    void Chakra_Recovery();
    int Get_Chakra() const {return chakra;}
    int get_Naruto_bullet() const {return bullet_mana;}
    void Naruto_renderMANA(SDL_Renderer* screen, MainObject* naruto);
    bool Check_WIN();

    void set_comeback_time(const int& cb_time){revive_time = cb_time;}

    void set_is_guarding(const bool& is_guard){is_guarding = is_guard;}
    bool get_is_guarding() const {return is_guarding;}
    bool is_damaged = false;

    void set_is_attacking(const bool& is_attack_){is_attacking = is_attack_;}
    bool get_is_attacking() const {return is_attacking;}
    bool get_is_dashing() const {return is_dashing;}

    void set_option(const int& option_){Option = option_;}
    int get_option() const { return Option;}

    bool get_is_falling() const {return naruto_fall;}
    void reset_fall() {naruto_fall = 0;}
    int health_naruto;

private:
    int chakra;

    vector<Shuriken*> rasen_shuri;

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame;
    int status;
    bool is_ground = false; //check xem đã đứng trên đất chưa

    //check_map
    int map_x_;
    int map_y_;


    //All bool status
    bool is_jump = false;
    bool left_pressed = false;
    bool right_pressed = false;
    bool is_guarding = false;
    bool is_attacking = false;
    bool is_dashing = false;

    //Option & time
    int Option;
    int naruto_fall;
    int revive_time;

    int bullet_mana; //Count Mana
};
#endif //NARUTOSHIPPUDEN_MAINCHARACTER_H
