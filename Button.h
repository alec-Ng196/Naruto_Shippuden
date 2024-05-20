//
// Created by Admin on 9/5/2024.
//

#ifndef NARUTOSHIPPUDEN_BUTTON_H
#define NARUTOSHIPPUDEN_BUTTON_H

#include "Base_code.h"
#include "All_function.h"

enum BUTTON_STATUS{
    MOUSE_OUT = 80,
    MOUSE_IN = 81,
    MOUSE_DOWN = 82,
    MOUSE_UP = 83,
};

class Button : public Object{
public:
    Button();
    ~Button();

    void setPosition(int x, int y) { x_pos_ = x; y_pos_ = y; }
    bool LoadingIMG(std::string path, SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    void handleEvent(SDL_Event* e);
    bool click();
    void freeB() { Object::FreeObject();}

private:
    int x_pos_, y_pos_, currentStatus;
    int width_frame_;
    int height_frame_;
};
#endif //NARUTOSHIPPUDEN_BUTTON_H
