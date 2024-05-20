//
// Created by Admin on 30/4/2024.
//

#include "Boss.h"
using namespace std;

BossObj::BossObj() {
    frame = 0;
    x_val = 0.0;
    y_val = 0.0;
    Xpos = 0;
    Ypos = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    think_time = 0;
    map_y_ = 0;
    map_x_ = 0;
    on_ground = 0;
    last_fr_ = 0;
    health_boss = 9;

}

BossObj::~BossObj(){

}

void BossObj::reset() {
    frame = 0;
    think_time = 0;
    map_y_ = 0;
    map_x_ = 0;
    on_ground = 0;
    last_fr_ = 0;
    health_boss = 9;
}

bool BossObj::LoadingIMG(std::string path, SDL_Renderer *screen) {
    bool ret = Object::LoadingIMG(path, screen);
    if(ret){
        width_frame_ = g_rect.w/BOSS_FRAME_NUM;
        height_frame_ = g_rect.h;
    }
    return ret;
}

SDL_Rect BossObj::GetRectFRAME() {
    SDL_Rect rect;
    rect.x = g_rect.x;
    rect.y = g_rect.y;
    rect.w = width_frame_; // dùng luôn width_frame vì sau LoadingIMG đã lấy được width_frame
    rect.h = height_frame_;

    return rect;
}

void BossObj::set_clips_() {
    if(width_frame_ > 0 && height_frame_ > 0){
        for(int i = 0; i < BOSS_FRAME_NUM; i++){
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void BossObj::Show_BOSS(SDL_Renderer *des) {
    if(think_time == 0){
        g_rect.x = Xpos - map_x_;
        g_rect.y = Ypos - map_y_;

        int frameDelay = 5000 / FRAME_PER_SECOND;

        Uint32 currentFrameTime = SDL_GetTicks() - last_fr_;
        if (currentFrameTime >= frameDelay) {
            frame++;
            if (frame >= 20) frame = 0;
            last_fr_ = SDL_GetTicks();
        }

        SDL_Rect* current_clip = &frame_clip_[frame];

        SDL_Rect renderQuad = {g_rect.x, g_rect.y, width_frame_, height_frame_};
        if(current_clip != NULL){
            renderQuad.w = current_clip->w;
            renderQuad.h = current_clip->h;
        }

        SDL_RenderCopy(des, g_object, current_clip, &renderQuad);
    }
}

void BossObj::Boss_Action(Map &g_map) {
    if(think_time == 0){
        x_val = 0;
        y_val += Gravity_Boss; //Lượng rơi - Tốc độ rơi
        if(y_val >= MAX_FALL_SPEED){
            y_val = MAX_FALL_SPEED;
        }
        if(input_type.guard == 0 && input_type.left == 1){
            x_val -= Boss_SPEED; // Lùi đi 1 khoảng PLAYER_SPEED
        }
        else if (input_type.guard == 0 && input_type.right == 1)
            x_val += Boss_SPEED; //tiến lên 1 khoảng PLAYER_SPEED
        if(input_type.jump == 1){
            if (on_ground == 1){
                y_val = (-BOSS_HIGH_VAL);
            }
            input_type.jump = 0;
        }

        Check_toMap(g_map);
        //CenterEntityOnMap(g_map);
    }
    else if(think_time > 0){
        think_time--;
        if(think_time == 0){ // reset lại trạng thái
            InitBOSS();
        }
    }
}

void BossObj::InitBOSS() {
    x_val = 0;
    y_val = 0;
    if(Xpos > 256){
        Xpos -= 256;
    }
    else{
        Xpos = 0;
    }
    Ypos = 0;
    think_time = 0;
    input_type.left = 1;
}

void BossObj::boss_renderHP(SDL_Renderer *des, BossObj *bosses) {
    int current_hp = bosses->get_boss_HP();
    int maxHP = SUSANO_BOSS_HP;
    if(current_hp >= 0){
        float ratioHealth = (float)current_hp/(float)maxHP;
        int healthBarLen = (int)(MAX_HP_BOSSLEN * ratioHealth);

        SDL_Rect HP_Bar = {bosses->GetRectFRAME().x + 25, bosses->GetRectFRAME().y - 25, healthBarLen, 30};

        SDL_SetRenderDrawColor(des, 255, 0, 0, 255); // Red bar
        SDL_RenderFillRect(des, &HP_Bar);
    }

}

void BossObj::CenterEntityOnMap(Map &g_map) {
    //Set tọa độ màn hình di chuyển cho phương Ox
    g_map.begin_x = (int) Xpos - (SCREEN_WIDTH/2);
    if(g_map.begin_x < 0){
        g_map.begin_x = 0;
    }
    else if(g_map.begin_x + (SCREEN_WIDTH) >= g_map.end_x){
        g_map.begin_x = g_map.end_x - SCREEN_WIDTH;
    }

    //Set tọa độ màn hình di chuyển cho phương Oy
    g_map.begin_y = (int) Ypos - (SCREEN_HEIGHT/2);
    if(g_map.begin_y < 0){
        g_map.begin_y = 0;
    }
    else if(g_map.begin_y + (SCREEN_HEIGHT) >= g_map.end_y){
        g_map.begin_y = g_map.end_y - SCREEN_HEIGHT;
    }
}

void BossObj::Check_toMap(Map &g_map) {
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Kiểm tra chiều ngang
    int height_min = min(height_frame_, TILE_SZ);
    //Xem x1 là ô thứ bao nhieu

    x1 = (Xpos + x_val)/TILE_SZ;
    x2 = (Xpos + x_val + width_frame_ -1)/TILE_SZ;

    y1 = (Ypos)/TILE_SZ;
    y2 = (Ypos + height_min -1)/TILE_SZ;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(x_val > 0)// Đang di chuyển sang phải
        {
            int val1 = g_map.tile[y1][x2];
            int val2 = g_map.tile[y2][x2];
            if(val1 != BLANK || val2 != BLANK){
                Xpos = x2*TILE_SZ;
                Xpos -= width_frame_ + 1;
                x_val = 0; // Bằng 0 để ko di chuyển được
            }


        }
        else if(x_val < 0){
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y2][x1];
            if(val1 != BLANK || val2 != BLANK){
                Xpos = (x1 + 1)*TILE_SZ;
                x_val = 0;
            }
        }
    }


    //Kiểm tra chiều dọc
    int width_min = min(width_frame_, TILE_SZ);
    x1 = (Xpos)/TILE_SZ;
    x2 = (Xpos + width_min)/TILE_SZ;

    y1 = (Ypos + y_val)/TILE_SZ;
    y2 = (Ypos + y_val + height_frame_ - 1)/TILE_SZ;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(y_val > 0){
            int val1 = g_map.tile[y2][x1];
            int val2 = g_map.tile[y2][x2];
            if(val1 != BLANK || val2 != BLANK){
                Ypos = y2 * TILE_SZ;
                Ypos -= height_frame_ + 1;
                y_val = 0;

                on_ground = 1;
                }
        }
        else if(y_val < 0){
            int val1 = g_map.tile[y1][x1];
            int val2 = g_map.tile[y1][x2];

            if(g_map.tile[y1][x1] != BLANK || g_map.tile[y1][x2] != BLANK) //check nhảy lên có va chạm không
             {
                Ypos = (y1 + 1) * TILE_SZ;
                y_val = 0;
             }


        }
    }
    //Nếu không va chạm gì hết thì đi bình thường

    Xpos += x_val;
    Ypos += y_val;
    if(Xpos < 0){
        Xpos = 0; //Nếu nó lùi quá sâu, quá vị trí bản đồ
    }
    else if(Xpos + width_frame_ > g_map.end_x){
        Xpos = g_map.end_x - width_frame_ -1; //Nếu nó đi quá bản đồ(kịch cỡ)
    }
    if(Ypos > g_map.end_y){
        think_time = 60; //Độ trễ để nvat trở lại khung hình khi rơi xuống vực
    }
}

void BossObj::InitBullet(SDL_Renderer* screen) {
    Shuriken* p_bullet = new Shuriken();

    bool ret = p_bullet->LoadingIMG("img\\Boss_bullet.png", screen);
    if(ret){
        p_bullet->set_shuri_dir(Shuriken::Dir_left);
        p_bullet->set_is_darted(true);
        p_bullet->setRect(g_rect.x - 50, g_rect.y + 100);
        p_bullet->set_x_value(15);
        bullet_list.push_back(p_bullet);
    }
}

void BossObj::MakeBullet(SDL_Renderer *des, const int &x_limit, const int &y_limit) {
    if(frame == 16){
        InitBullet(des);
    }
    for(int i = 0; i < bullet_list.size(); i++){
        Shuriken* p_bullet = bullet_list.at(i);
        if(p_bullet != NULL){
            if(p_bullet->get_is_darted()){
                p_bullet->Throw_Shuri(x_limit, y_limit);
                p_bullet->toRender(des);
            }
            else{
                p_bullet->FreeObject();
                bullet_list.erase(bullet_list.begin() + i);
            }
        }
    }

}

void BossObj::RemoveBullet(const int &idx) {
    int size = bullet_list.size();
    if(size > 0 && idx < size){
        Shuriken* b_susano = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);

        if(b_susano){
            delete b_susano;
            b_susano = NULL;
        }
    }
}
