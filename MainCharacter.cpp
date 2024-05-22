//
// Created by Admin on 14/4/2024.
//

#include "MainCharacter.h"
#include "All_function.h"
#include "Shuriken.h"
#include <iostream>
#include <algorithm>
using namespace std;


MainObject::MainObject(){
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = Fall_reset;
    map_x_ = 0;
    map_y_ = 0;
    revive_time = 0;
    chakra = 0;
    health_naruto = 5;
    Option = PLAY;
    naruto_fall = 0;
    bullet_mana = 35;
}


MainObject::~MainObject(){

}

void MainObject::reset() {
    input_type.left = 0;
    input_type.right = 0;
    is_dashing = false;
    input_type.attack = 0;
    input_type.throwing = 0;
    input_type.stance = 1;
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    status = Fall_reset;
    map_x_ = 0;
    map_y_ = 0;
    revive_time = 0;
    chakra = 0;
    Option = PLAY;
    naruto_fall = 0;
    bullet_mana = 35;
}

bool MainObject::LoadingIMG(std::string path, SDL_Renderer* screen){
    bool check = Object::LoadingIMG(path,screen);
    if(check){
        width_frame = g_rect.w/8;
        height_frame = g_rect.h;
        return check;
    }
}

SDL_Rect MainObject::GetRectFRAME() {
    SDL_Rect rect;
    rect.x = g_rect.x;
    rect.y = g_rect.y;
    rect.w = width_frame; // dùng luôn width_frame vì sau LoadingIMG đã lấy được width_frame
    rect.h = height_frame;

    return rect;
 }

void MainObject::set_clips(){
    if(width_frame > 0 && height_frame > 0){
        for(int i = 0; i < 8; i++){
            frame_clip[i].x = width_frame*i;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void MainObject::ShowMain(SDL_Renderer* des){
    UpdateStats(des);
    if (input_type.left == 1 || input_type.right == 1 || input_type.guard == 1){
        frame++;
    }
    else if(input_type.attack == 1){
        frame++;

    }
    if(is_damaged){
        frame++;
        UpdateStats(des);
        //is_damaged = false;
    }
    if(is_dashing){
        frame++;
        UpdateStats(des);
    }
    else{
        frame++;
        if(frame >= 8) frame = 0;
        UpdateStats(des);
    }

    /*else if(status == Idle && input_type.right == 0 && input_type.left == 0){
        frame++;
        if(frame >= 8) frame = 0;
        LoadingIMG("idle_right.png", des);

    } */
    if(frame >= 8){
        frame = 0;
    }
    if(revive_time == 0){
        g_rect.x = x_pos - map_x_;
        g_rect.y = y_pos - map_y_;

        SDL_Rect* current_clip = &frame_clip[frame];

        SDL_Rect renderMain = {g_rect.x, g_rect.y, width_frame, height_frame};
        SDL_RenderCopy(des, g_object, current_clip, &renderMain);
    }
}

void MainObject::Set_first_move() {
    status = Idle;
}

void MainObject::Handle(SDL_Event events, SDL_Renderer* screen){
    if(events.type == SDL_KEYDOWN){
        switch(events.key.keysym.sym){
            case SDLK_RIGHT:
            {
                status = Walk_right;
                input_type.right = 1;
                input_type.left = 0;
                right_pressed = true;
                left_pressed = false;
                UpdateStats(screen);
            }
                break;
            case SDLK_LEFT:
            {
                status = Walk_left;
                input_type.left = 1;
                input_type.right = 0; // Đề phòng TH nguoi chơi ấn cả 2 phím trái - phải
                left_pressed = true;
                right_pressed = false;
                UpdateStats(screen);
            }
                break;
            case SDLK_UP:
            {
                is_jump = true;
                input_type.jump = 1;
                UpdateStats(screen);
            }
                break;
            case SDLK_DOWN:
            {
                status = Guarding;
                input_type.guard = 1;
                is_guarding = true;
                is_damaged = false;
                UpdateStats(screen);
            }
                break;
            case SDLK_a:
            {
                input_type.attack = 1;
                is_attacking = true;
                is_damaged = false;
                UpdateStats(screen);
            }
                break;
            case SDLK_s:
            {
                if(bullet_mana>0){
                    input_type.throwing = 1;

                    Shuriken* g_shuri = new Shuriken();
                    g_shuri->set_bullet_type(Shuriken::SHURIKEN);
                    g_shuri->LoadingIMGBullet(screen);


                    if(left_pressed && is_ground){
                        g_shuri->set_shuri_dir(Shuriken::Dir_left);
                        g_shuri->setRect(this->g_rect.x - width_frame - 25, g_rect.y + height_frame*0.3 - 10);
                    }
                    else if(right_pressed && is_ground){
                        g_shuri->set_shuri_dir(Shuriken::Dir_right);
                        g_shuri->setRect(this->g_rect.x + width_frame - 15, g_rect.y + height_frame*0.3 - 10);
                    }
                    else if((status == Idle && left_pressed) || (!right_pressed && left_pressed && input_type.throwing == 1)){
                        g_shuri->set_shuri_dir(Shuriken::Dir_left_down);
                        g_shuri->setRect(this->g_rect.x - width_frame - 25, g_rect.y + height_frame*0.3 - 10);
                    }
                    else if((status == Idle) || (!left_pressed && right_pressed && input_type.throwing == 1)){
                        g_shuri->set_shuri_dir(Shuriken::Dir_right_down);
                        g_shuri->setRect(this->g_rect.x + width_frame - 15, g_rect.y + height_frame*0.3 - 10);
                    }


                    g_shuri->set_y_value(20);
                    g_shuri->set_x_value(20);
                    g_shuri->set_is_darted(true);

                    rasen_shuri.push_back(g_shuri);
                }
                bullet_mana--;
                if(bullet_mana < 0) bullet_mana = 0;

            }
                break;
            case SDLK_f:
            {
                input_type.dash = 1;
                is_dashing = true;
                UpdateStats(screen);
            }
                break;
            case SDLK_p:
            {
                Option = PAUSE;
                break;
            }

        }
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym){
            case SDLK_RIGHT:
            {
                input_type.right = 0;
                input_type.stance = 1;
            }
                break;
            case SDLK_LEFT:
            {
                input_type.left = 0;
                input_type.stance = 1;
            }
                break;
            case SDLK_UP:
            {
                input_type.jump = 0;
                input_type.stance = 1;
            }
                break;
            case SDLK_DOWN:
            {
                input_type.guard = 0;
                input_type.stance = 1;
                is_guarding = false;
            }
            case SDLK_a:
            {
                input_type.attack = 0;
                input_type.stance = 1;
                is_attacking = false;
            }
                break;
            case SDLK_s:
            {
                input_type.throwing = 0;
                input_type.stance = 1;
            }
                break;
            case SDLK_f:
            {
                input_type.dash = 0;
                input_type.stance = 1;
                is_dashing = false;
            }

        }
    }
    /*else {
        if (input_type.right == 0 && input_type.left == 0) {
            status = Idle;
            input_type.stance = 1;

        }
    } */

}
void MainObject::Throw_Shuri(SDL_Renderer* des) {
    for(int i = 0; i<rasen_shuri.size(); i++){
        Shuriken* g_shuri = rasen_shuri.at(i);
        if(g_shuri != NULL){
            if(g_shuri->get_is_darted() == true){
                g_shuri->Throw_Shuri(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_shuri->toRender(des);
            }
            else{
                rasen_shuri.erase(rasen_shuri.begin() + i);
                if(g_shuri != NULL){
                    //delete g_shuri;
                    //g_shuri = NULL;
                    g_shuri->FreeObject();
                }
            }
        }
    }
}

void MainObject::RemoveShuri(const int &index) {
    int size = rasen_shuri.size();
    if(size > 0 && index < size){
        Shuriken* p_shuri = rasen_shuri.at(index);
        rasen_shuri.erase(rasen_shuri.begin() + index);

        if(p_shuri){
            delete p_shuri;
            p_shuri = NULL;
        }
    }
}

void MainObject::Player_action(Map &map_data){
    if(revive_time == 0){
        x_val = 0;
        y_val += 0.9; //Lượng rơi - Tốc độ rơi
        if(y_val >= MAX_FALL_SPEED){
            y_val = MAX_FALL_SPEED;
        }
        if(!is_damaged && input_type.guard == 0 && input_type.left == 1 && input_type.attack == 0){
            x_val -= PLAYER_SPEED; // Lùi đi 1 khoảng PLAYER_SPEED
        }
        else if (!is_damaged && input_type.guard == 0 && input_type.right == 1 && input_type.attack == 0)
            x_val += PLAYER_SPEED; //tiến lên 1 khoảng PLAYER_SPEED
        if(!is_damaged && !is_attacking && input_type.guard == 0 && right_pressed && is_dashing && is_ground){
            x_val += 10*PLAYER_SPEED;
        }
        if(!is_damaged && !is_attacking && input_type.guard == 0 && left_pressed && is_dashing && is_ground){
            x_val -= 10*PLAYER_SPEED;
        }
        if(is_damaged && right_pressed && !left_pressed){
            x_val -= (PLAYER_SPEED*4);
        }
        else if(is_damaged && left_pressed && !right_pressed){
            x_val += (PLAYER_SPEED*4);
        }
        if(input_type.jump == 1){
            if (is_ground){
                y_val = (-PLAYER_JUMP);
            }
            is_ground = false;
            input_type.jump = 0;
        }
        if(input_type.attack == 1 && right_pressed && !is_dashing){
            if (is_ground){
                x_val += (PLAYER_SPEED - 2);
            }
        }
        else if(input_type.attack == 1 && left_pressed && !is_dashing){
            if(is_ground){
                x_val -= (PLAYER_SPEED - 2);
            }
        }

        check_map(map_data);
        SET_Mapvision(map_data);
    }
    else if(revive_time > 0){
        revive_time--;
        if(revive_time == 0){ // reset lại trạng thái
            is_ground = false;
            if(x_pos > 256){
                x_pos -= 256;
            }else{
                x_pos = 0;
            }
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}

void MainObject::SET_Mapvision(Map &map_data)  {
    //Set tọa độ màn hình di chuyển cho phương Ox
    map_data.begin_x = (int) x_pos - (SCREEN_WIDTH/2);
    if(map_data.begin_x < 0){
        map_data.begin_x = 0;
    }
    else if(map_data.begin_x + (SCREEN_WIDTH) >= map_data.end_x){
        map_data.begin_x = map_data.end_x - SCREEN_WIDTH;
    }

    //Set tọa độ màn hình di chuyển cho phương Oy
    map_data.begin_y = (int) y_pos - (SCREEN_HEIGHT/2);
    if(map_data.begin_y < 0){
        map_data.begin_y = 0;
    }
    else if(map_data.begin_y + (SCREEN_HEIGHT) >= map_data.end_y){
        map_data.begin_y = map_data.end_y - SCREEN_HEIGHT;
    }

}

void MainObject::check_map(Map &map_data) {
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Kiểm tra chiều ngang
    int height_min = min(height_frame, TILE_SZ);
    //Xem x1 là ô thứ bao nhieu

    x1 = (x_pos + x_val)/TILE_SZ;
    x2 = (x_pos + x_val + width_frame -1)/TILE_SZ;

    y1 = (y_pos)/TILE_SZ;
    y2 = (y_pos + height_min -1)/TILE_SZ;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(x_val > 0)// Đang di chuyển sang phải
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if(val1 == Ramen || val2 == Ramen || val1 == WINNER || val2 == WINNER){
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                Chakra_Recovery();
            }
            else{
                if(val1 != BLANK || val2 != BLANK){
                    x_pos = x2*TILE_SZ;
                    x_pos -= width_frame + 1;
                    x_val = 0; // Bằng 0 để ko di chuyển được
                }
            }

        }
        else if(x_val < 0){
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(val1 == Ramen || val2 == Ramen || val1 == WINNER || val2 == WINNER){
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                Chakra_Recovery();
            }
            else{
                if(val1 != BLANK || val2 != BLANK){
                    x_pos = (x1 + 1)*TILE_SZ;
                    x_val = 0;
                }
            }

        }
    }


    //Kiểm tra chiều dọc
    int width_min = min(width_frame, TILE_SZ);
    x1 = (x_pos)/TILE_SZ;
    x2 = (x_pos + width_min)/TILE_SZ;

    y1 = (y_pos + y_val)/TILE_SZ;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SZ;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(y_val > 0){
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == Ramen || val2 == Ramen || val1 == WINNER || val2 == WINNER){
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                Chakra_Recovery();
            }
            else{
                if(val1 != BLANK || val2 != BLANK){
                    y_pos = y2 * TILE_SZ;
                    y_pos -= height_frame + 1;
                    y_val = 0;
                    is_ground = true;
                    if(status == Fall_reset){
                        status = Jumping;
                    }
                }
            }

        }
        else if(y_val < 0){
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == Ramen || val2 == Ramen || val1 == WINNER || val2 == WINNER){
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                Chakra_Recovery();
            }
            else{
                if(map_data.tile[y1][x1] != BLANK || map_data.tile[y1][x2] != BLANK) //check nhảy lên có va chạm không
                {
                    y_pos = (y1 + 1) * TILE_SZ;
                    y_val = 0;
                }
            }

        }
    }
    //Nếu không va chạm gì hết thì đi bình thường

    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0){
        x_pos = 0; //Nếu nó lùi quá sâu, quá vị trí bản đồ
    }
    else if(x_pos + width_frame > map_data.end_x){
        x_pos = map_data.end_x - width_frame -1; //Nếu nó đi quá bản đồ(kịch cỡ)
    }
    if(y_pos > map_data.end_y){
        naruto_fall = 1;
        revive_time = 45; //Độ trễ để nvat trở lại khung hình khi rơi xuống vực
    }

}

void MainObject::Chakra_Recovery() { //Tính số lượng Ramen đã ăn được và chuyển hóa chakra
    chakra++;
    bullet_mana++;
    if(bullet_mana > 35) bullet_mana = 35;

}

void MainObject::Naruto_renderMANA(SDL_Renderer *screen, MainObject *naruto) {
    int current_mana = naruto->get_Naruto_bullet();
    int maxMana = MAX_MANA;
    float ratioMana = (float)current_mana/(float)maxMana;
    int healthBarLen = (int)(MAX_MANA_LEN * ratioMana);

    SDL_Rect HP_Bar = {75, 92, healthBarLen, 12};

    SDL_SetRenderDrawColor(screen, 0, 250, 154, 255); // green bar
    SDL_RenderFillRect(screen, &HP_Bar);
}

bool MainObject::Check_WIN() {
    if(chakra >= 38){
        return true;
    }
    return false;
}

void MainObject::UpdateStats(SDL_Renderer *des) {
    if(is_ground){
        if(input_type.left == 1){
            LoadingIMG("img\\left_move.png", des);
        }
        else if(input_type.right == 1){
            LoadingIMG("img\\right_move.png", des);
        }
        else if(input_type.stance == 1 && left_pressed && !right_pressed){
            LoadingIMG("img\\idle_left.png", des);
        }
        else if(input_type.stance == 1 && right_pressed && !left_pressed){
            LoadingIMG("img\\idle_right.png", des);
        }
        if(input_type.guard == 1 && right_pressed && !left_pressed){
            LoadingIMG("img\\guard_right.png", des);
        }
        else if(input_type.guard == 1 && left_pressed && !right_pressed){
            LoadingIMG("img\\guard_left.png", des);
        }
        else if(is_damaged && right_pressed && !left_pressed){
            LoadingIMG("img\\naruto_knocked_left.png", des);
        }
        else if(is_damaged && !right_pressed && left_pressed){
            LoadingIMG("img\\naruto_knocked_right.png", des);
        }
        if(right_pressed && !left_pressed && is_dashing){
            LoadingIMG("img\\Dash_right.png",des);
        }
        else if(left_pressed && !right_pressed && is_dashing){
            LoadingIMG("img\\Dash_left.png", des);
        }
        if(input_type.attack == 1 && right_pressed && !left_pressed){
            LoadingIMG("img\\attack_right.png", des);
        }
        if(input_type.attack == 1 && !right_pressed && left_pressed){
            LoadingIMG("img\\attack_left.png", des);
        }
        if(input_type.throwing == 1 && !right_pressed && left_pressed){
            LoadingIMG("img\\left_throw.png", des);
        }
        else if(input_type.throwing == 1 && !left_pressed && right_pressed){
            LoadingIMG("img\\right_throw.png", des);
        }

    }
    else{
        if(is_jump && left_pressed && !right_pressed){
            LoadingIMG("img\\left_jump.png", des);
        }
        else if(is_jump && right_pressed && !left_pressed) LoadingIMG("img\\right_jump.png", des);
        /*if(status == Jumping && left_pressed && !right_pressed && input_type.throwing == 1){
            LoadingIMG("")
        } */
    }

}

