//
// Created by Admin on 20/4/2024.
//

#ifndef NARUTOSHIPPUDEN_SHURIKEN_H
#define NARUTOSHIPPUDEN_SHURIKEN_H

#include "All_function.h"
#include "Base_code.h"

class Shuriken : public Object{
public:
    Shuriken();
    ~Shuriken();
    enum ShuriDir{
        Dir_right = 19,
        Dir_left = 20,
        Dir_up = 21,
        Dir_right_up = 22,
        Dir_left_up = 23,
        Dir_right_down = 24,
        Dir_left_down = 25,
    };
    enum BulletType{
        SHURIKEN = 49,
        BALL_FIRE = 50,
    };

    void set_x_value(const int& x_val_){x_val = x_val_;}
    void set_y_value(const int& y_val_){y_val = y_val_;}
    int get_x_value() const {return x_val;}
    int get_y_value() const {return y_val;}

    void set_is_darted(const bool& is_darted_){is_darted = is_darted_;}
    bool get_is_darted() const {return is_darted;}

    void set_shuri_dir(const unsigned int& shuri_dir_) {shuri_dir = shuri_dir_;}
    unsigned int get_shuri_dir() const {return shuri_dir;}

    void set_bullet_type(const unsigned int& bullettype){bullet_type = bullettype;}
    unsigned int get_bullet_type() const {return bullet_type;}

    void Throw_Shuri(const int& x_border, const int& y_border);
    bool LoadingIMGBullet(SDL_Renderer* des);

private:
    int x_val;
    int y_val;
    bool is_darted;
    unsigned int shuri_dir;
    unsigned int bullet_type;
};

#endif //NARUTOSHIPPUDEN_SHURIKEN_H
