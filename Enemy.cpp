//
// Created by Admin on 22/4/2024.
//

#include "Enemy.h"
#include<algorithm>
#include<iostream>

using namespace std;

Enemy::Enemy() {
    width_frame = 0;
    height_frame = 0;
    x_val = 0.0;
    y_val = 0.0;
    x_pos = 0.0;
    y_pos = 0.0;
    is_ground = false;
    comeback_time = 0;
    frame = 0;
    last_FRAME = 0;
    animation_first = 0;
    animation_last = 0;
    input_type.left = 0;
    health_enemy = 3;
    move_genre = STATIC_OBJ; // Obj ban dau la dung yen

}
Enemy::~Enemy() {

}

bool Enemy::LoadingIMG(std::string path, SDL_Renderer *screen) {
    bool ret = Object::LoadingIMG(path, screen);
    if(ret){
        width_frame = g_rect.w/Enemy_FRAME;
        height_frame = g_rect.h;
    }
    return ret;
}

SDL_Rect Enemy::GetRectFRAME() {
    SDL_Rect rect;
    rect.x = g_rect.x;
    rect.y = g_rect.y;
    rect.w = width_frame; // dùng luôn width_frame vì sau LoadingIMG đã lấy được width_frame
    rect.h = height_frame;

    return rect;
}

void Enemy::set_clips() {
    if(width_frame > 0 && height_frame > 0 ){
        for(int i = 0; i < 8; i++){
            frame_clips[i].x = width_frame*i;
            frame_clips[i].y = 0;
            frame_clips[i].w = width_frame;
            frame_clips[i].h = height_frame;
        }
    }
}

void Enemy::ShowEnemy(SDL_Renderer *des) {
    if(is_knocked && input_type.left == 1 ){
        if (frame >= 8) frame = 0;
        LoadingIMG("img\\Obito_knocked_left.png" ,des);
    }
    else if(is_knocked && input_type.right == 1){
        if (frame >= 8) frame = 0;
        LoadingIMG("img\\Obito_knocked_right.png" ,des);
    }
    if(comeback_time == 0){
        g_rect.x = x_pos - map_x_;
        g_rect.y = y_pos - map_y_;
        int frameDelay = 3000 / FRAME_PER_SECOND;

        Uint32 currentFrameTime = SDL_GetTicks() - last_FRAME;
        if (currentFrameTime >= frameDelay) {
            frame++;
            if (frame >= 8) frame = 0;
            last_FRAME = SDL_GetTicks();
        }
        SDL_Rect* currentClip = &frame_clips[frame];
        SDL_Rect renderQuad = {g_rect.x, g_rect.y, width_frame, height_frame};
        //SDL_Delay(100);
        SDL_RenderCopy(des, g_object, currentClip, &renderQuad);
    }
}

void Enemy::Enemy_renderHP(SDL_Renderer *screen, Enemy *enemies) {
    int current_hp = enemies->get_enemy_hp();
    int maxHP = HP_OBITO;
    float ratioHealth = (float)current_hp/(float)maxHP;
    int healthBarLen = (int)(MAX_HP_LENGTH * ratioHealth);

    SDL_Rect HP_Bar = {enemies->GetRectFRAME().x +25, enemies->GetRectFRAME().y - 20, healthBarLen, 10};

    SDL_SetRenderDrawColor(screen, 0, 0, 255, 255); // Blue bar
    SDL_RenderFillRect(screen, &HP_Bar);
}

void Enemy::ENEMY_Action(Map &g_map) {
    if(comeback_time == 0){
        x_val = 0;
        y_val += Falling_SPEED;
        if(y_val >= Enemy_MAX_FALL){
            y_val = Enemy_MAX_FALL;
        }
        if(input_type.left == 1){
            x_val -= ENEMY_SPEED;
        }
        else if(input_type.right == 1){
            x_val += ENEMY_SPEED;
        }
        if(is_knocked && input_type.left == 1){
            x_val += (7*ENEMY_SPEED);
        }
        else if(is_knocked && input_type.right == 1){
            x_val -= (7*ENEMY_SPEED);
        }
        check_MAP(g_map);

    }
    else if(comeback_time > 0){
        comeback_time--;
        if(comeback_time == 0){
            InitEnemy();
        }
    }
}

void Enemy::InitEnemy() {
    x_val = 0;
    y_val = 0;
    if(x_pos > 256){
        x_pos -= 256;
        animation_first -= 256;
        animation_last -= 256;
    }
    else{
        x_pos = 0;
    }
    y_pos = 0;
    comeback_time = 0;
    input_type.left = 1;
}

void Enemy::RemoveFire(const int &idx) {
    int size = Fire_ball_list.size();
    if(size > 0 && idx < size){
        Shuriken* p_fire = Fire_ball_list.at(idx);
        Fire_ball_list.erase(Fire_ball_list.begin() + idx);

        if(p_fire){
            delete p_fire;
            p_fire = NULL;
        }
    }
}


void Enemy::check_MAP(Map &g_map) {
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
            int val1 = g_map.tile[y1][x2];
            int val2 = g_map.tile[y2][x2];
            if((val1 != BLANK && val1 != Ramen)||(val2 != BLANK && val2 != Ramen)){
                x_pos = x2*TILE_SZ;
                x_pos -= width_frame + 1;
                x_val = 0; // Bằng 0 để ko di chuyển được
            }
        }
        else if(x_val < 0){
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y2][x1];
            if((val1 != BLANK && val1 != Ramen)||(val2 != BLANK && val2 != Ramen)){
                x_pos = (x1 + 1)*TILE_SZ;
                x_val = 0;
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
            int val1 = g_map.tile[y2][x1];
            int val2 = g_map.tile[y2][x2];
            if((val1 != BLANK && val1 != Ramen) || (val2 != BLANK && val2 != Ramen)){
                y_pos = y2 * TILE_SZ;
                y_pos -= height_frame + 1;
                y_val = 0;
                is_ground = true;
            }
        }
        else if(y_val < 0){
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y1][x2];
            if((val1 != BLANK && val1 != Ramen)  || (val2 != BLANK && val2 != Ramen)) //check nhảy lên có va chạm không
            {
                y_pos = (y1 + 1) * TILE_SZ;
                y_val = 0;
            }


        }
    }
    //Nếu không va chạm gì hết thì đi bình thường

    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0){
        x_pos = 0; //Nếu nó lùi quá sâu, quá vị trí bản đồ
    }
    else if(x_pos + width_frame > g_map.end_x){
        x_pos = g_map.end_x - width_frame -1; //Nếu nó đi quá bản đồ(kịch cỡ)
    }
    if(y_pos > g_map.end_y){
        comeback_time = 45; //Độ trễ để nvat trở lại khung hình khi rơi xuống vực
    }

}

void Enemy::ImpMoveType(SDL_Renderer *screen) {
    if(move_genre == STATIC_OBJ){
        ;//Ko lam gi ca
    }
    else{
        if(is_ground && !is_knocked){
            if(x_pos > animation_last){
                input_type.left = 1;
                input_type.right = 0;
                LoadingIMG("img\\Obito_left.png" ,screen);
            }
            else if(x_pos < animation_first){
                input_type.left = 0;
                input_type.right = 1;
                LoadingIMG("img\\Obito_right.png" ,screen);
            }
        }
        //Dang roi tren khong trung
        else{
            if(input_type.left == 1){
                LoadingIMG("img\\Obito_left.png" ,screen);
            }
        }
    }
}

void Enemy::InitFire(Shuriken *p_fire, SDL_Renderer *screen) {
    if(p_fire != NULL){
        p_fire->set_bullet_type(Shuriken::BALL_FIRE);
        p_fire->LoadingIMGBullet(screen);
        p_fire->set_is_darted(true);
        p_fire->set_shuri_dir(Shuriken::Dir_left);
        p_fire->setRect(x_pos - 10, g_rect.y + 10);
        p_fire->set_x_value(10);
        Fire_ball_list.push_back(p_fire);
    }
}

void Enemy::MakeFireJujutsu(SDL_Renderer *screen, const int &x_limit, const int &y_limit) {
    for(int i =0; i < Fire_ball_list.size(); i++){
        Shuriken* p_fire = Fire_ball_list.at(i);
        if(p_fire != NULL){
            if(p_fire->get_is_darted()){
                int fire_distance = g_rect.x + width_frame - p_fire->GetRect().x;
                if(fire_distance < 300 && fire_distance > 0){
                    p_fire->Throw_Shuri(x_limit, y_limit);
                    p_fire->toRender(screen);
                }
                else{
                    p_fire->set_is_darted(false);
                }
            }
            else{
                p_fire->set_is_darted(true);
                p_fire->setRect(g_rect.x - 10, g_rect.y + 10);
            }
        }
    }
}