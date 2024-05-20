//
// Created by Admin on 30/4/2024.
//

#ifndef NARUTOSHIPPUDEN_HEALTHBAR_H
#define NARUTOSHIPPUDEN_HEALTHBAR_H

#include "All_function.h"
#include "Base_code.h"

#define FRAME_HP 6

class HealthPower : public Object{
public:
    HealthPower();
    ~HealthPower();

    void Set_clips_();
    void Set_frame_hp(const int& fr){num_fr = fr;}
    virtual bool LoadingIMG(std::string path, SDL_Renderer* screen);
    void Show_HP(SDL_Renderer* screen);
    void reset();

private:
    int num_fr; //Bao nhiêu mạng
    int width_fr_;
    int height_fr_;
    SDL_Rect frame_clip_[FRAME_HP];
    std::vector<int> position_list;
};

class PlayerChakra : public Object{
public:
    PlayerChakra();
    ~PlayerChakra();

    void Init(SDL_Renderer* screen);
    void Show_Chakra(SDL_Renderer* screen);
    void SetPosition(const int& x, const int& y) {
        xp_ = x;
        yp_ = y;
    }

private:
    int xp_;
    int yp_;
};


#endif //NARUTOSHIPPUDEN_HEALTHBAR_H
