#include <iostream>
#include "All_function.h"
#include "Base_code.h"
#include "MainCharacter.h"
#include "map.h"
#include "TimeHandle.h"
#include "Enemy.h"
#include "Shuriken.h"
#include "ExplosionObj.h"
#include "TextObj.h"
#include "HealthBar.h"
#include "Boss.h"
#include "Button.h"

using namespace std;

void logErrorAndExit(const char* msg, const char* error);
void init();
void resetGame(MainObject& g_player, Game_Map& good_map, vector<Enemy*>& threats_list, BossObj& bossObject, HealthPower& player_hp, PlayerChakra& player_chakra);
bool loading_Media();
vector<Enemy*> MakeThread_LIST();
void close();


Object g_background, g_pauseBackground, g_menuBackground, g_helpBackground, g_loseBackground, g_winBackground, g_nextStage;
Button startButton, helpButton, backButton, exitButton, resumeButton, nextButton;
TTF_Font* font_time = NULL;
int option = START;
Mix_Music* g_start = NULL;
Mix_Music * g_winBoss = NULL;
static bool musicPlayed1 = false; // Biến static để giữ trạng thái của âm thanh đã được phát hay chưa
static bool musicPlayed2 = false;

void playMusic(Mix_Music *gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if( Mix_PausedMusic() == 1 ) {
        Mix_ResumeMusic();
    }
}


int main(int argc, char* argv[]){
    Timer FPS;
    static bool Back_check = false;
    init();
    if (!loading_Media()) return -1;

    Game_Map good_map; //Bắt đầu init Tile_map
    good_map.LoadMap("map_matrix.txt");
    good_map.LoadingTiles(g_screen);

    MainObject g_player; //Init nhân vật Naruto
    g_player.LoadingIMG("img\\Idle_right.png", g_screen);
    g_player.set_clips();


    /*
    Mix_Music * g_music = SDLAllFunction::loadMusic("Sample 11.wav");
    if (g_music != nullptr ) {
        Mix_PlayMusic(g_music, 0); // Tham số thứ hai là số lần lặp lại, 1 để phát một lần.
         // Giải phóng bộ nhớ sau khi đã phát xong.
    }
    */

    //if (g_music != nullptr) Mix_FreeMusic( g_music );
    //HealthPower
    HealthPower player_hp;
    bool check_hp1 = player_hp.LoadingIMG("img\\HP_bars.png", g_screen);
    if(!check_hp1) return -1;
    player_hp.Set_clips_();



    /*
    HealthPower boss_hp;
    bool check_hp2 = boss_hp.LoadingIMG("Picture20.png",g_screen);
    if(!check_hp2) return -1;
    boss_hp.Set_clips_();
    */

    //Công đoạn hiển thị chi số chakra
    PlayerChakra player_chakra;
    player_chakra.Init(g_screen);
    player_chakra.SetPosition(SCREEN_WIDTH*0.5, 10);

    vector<Enemy *> threats_list = MakeThread_LIST(); // Tạo quái, nhân vật phản diện

    //Start init BOSS
    BossObj bossObject;
    bool ret = bossObject.LoadingIMG("img\\Boss(1).png",g_screen);
    bossObject.set_clips_();
    int XposBOSS = MAX_MAP_X * TILE_SZ - SCREEN_WIDTH*0.2;
    //int XposBOSS = 500;
    bossObject.set_Xpos(XposBOSS);
    bossObject.set_Ypos(30);


    //Xử lý hiệu ứng enemy bị tấn công
    Explosion exp_threat;
    bool ret1 = exp_threat.LoadingIMG("img\\Explosion.png", g_screen);
    if(!ret1) return -1;
    exp_threat.set_clips();

    Explosion exp_threat2;
    bool ret4 = exp_threat2.LoadingIMG("img\\exp_damage.png", g_screen);
    if(!ret4) return -1;
    exp_threat2.set_clips();

    Explosion exp_main;
    bool ret2 = exp_main.LoadingIMG("img\\guard_damage.png", g_screen);
    if(!ret2) return -1;
    exp_main.set_clips();

    Explosion exp_boss;
    bool ret3 = exp_boss.LoadingIMG("img\\Picture19.png", g_screen);
    if(!ret3) return -1;
    exp_boss.set_clips();

    int hp = g_player.get_naruto_hp(); //Sau mỗi lần nvat chạm vào người quái/ trúng đạn thì sẽ mất máu


    //Xu lý time text
    //TextObject time_game;
    //time_game.Set_Color(TextObject::WHITE_TEXT);

    //Xu ly mark_game
    //TextObject mark_game;
    //mark_game.Set_Color(TextObject::WHITE_TEXT);
    //UINT mark_val = 0;

    TextObject chakra; //Từ việc ăn ramen sẽ tích thêm
    chakra.Set_Color(TextObject::BLUE_TEXT);
    TextObject Intro;
    Intro.Set_Color(TextObject::WHITE_TEXT);

    bool is_quit = false;

    while(!is_quit) {

        switch (option) {
            case START: //Menu
                while (SDL_PollEvent(&g_event) != 0) {
                    startButton.handleEvent(&g_event);
                    helpButton.handleEvent(&g_event);
                    exitButton.handleEvent(&g_event);
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                        break;
                    }
                    if (startButton.click()) {

                        resetGame(g_player, good_map, threats_list, bossObject, player_hp, player_chakra);
                        hp = 5;
                        g_player.set_option(PLAY);
                        option = PLAY;
                        break;
                    } else if (helpButton.click()) {
                        option = HELP;
                        break;

                    } else if (exitButton.click()) {
                        is_quit = true;
                        break;
                    }
                }
                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_menuBackground.toRender(g_screen, NULL);

                startButton.setPosition(317, 487);
                startButton.Show(g_screen);
                helpButton.setPosition(519, 487);
                helpButton.Show(g_screen);
                exitButton.setPosition(720, 487);
                exitButton.Show(g_screen);

                SDL_RenderPresent(g_screen);
                break;

            case HELP:
                while (SDL_PollEvent(&g_event) != 0) {
                    backButton.handleEvent(&g_event);
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                    }
                    if (backButton.click()) {
                        option = START;
                        break;
                    }
                }
                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_helpBackground.toRender(g_screen, NULL);
                backButton.setPosition(1080, 540);
                backButton.Show(g_screen);

                SDL_RenderPresent(g_screen);
                break;

            case PLAY: {

                //static bool textShown = false;

                if (!musicPlayed1) { // Nếu âm thanh chưa được phát
                    if (Mix_PlayingMusic() == 0) {
                        g_start = Mix_LoadMUS("assets\\Sample 11.wav");
                        Mix_PlayMusic(g_start, 0);
                    }
                    musicPlayed1 = true; // Đánh dấu rằng âm thanh đã được phát
                }
                FPS.start();

                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                    }
                    g_player.Handle(g_event, g_screen); //Thao tác game: trái - phải
                    option = g_player.get_option();
                }

                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_background.toRender(g_screen, nullptr);

                Map map_data = good_map.GetMap();

                g_player.Set_first_move();
                g_player.Throw_Shuri(g_screen);
                g_player.Map_vision(map_data.begin_x, map_data.begin_y);
                g_player.Player_action(map_data);
                g_player.ShowMain(g_screen); //Vẽ nhân vật Naruto

                good_map.SetMap(map_data);
                good_map.DrawingMap(g_screen); //Vẽ bản đồ game

                player_hp.Show_HP(g_screen);

                g_player.Naruto_renderMANA(g_screen, &g_player);


                //Tạm thời xử lý máu boss ở đây


                player_chakra.Show_Chakra(g_screen);
                for (int i = 0; i < threats_list.size(); i++) {
                    Enemy *g_threat = threats_list.at(i);
                    if (g_threat != NULL) {
                        g_threat->Set_MapXY(map_data.begin_x, map_data.begin_y);
                        g_threat->ImpMoveType(g_screen); // Check xem là nvat đứng yên(itachi), di chuyển(obito)
                        g_threat->ENEMY_Action(map_data); // Check trạng thái enemy và va chạm với map
                        //g_threat->MakeFireJujutsu(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                        g_threat->ShowEnemy(g_screen);
                        //g_threat->Enemy_renderHP(g_screen, g_threat, enemy_hp);
                        int enemy_hp_temp = g_threat->get_enemy_hp();
                        g_threat->Enemy_renderHP(g_screen, g_threat);

                        //Kiểm tra va chạm giữa naruto và lửa itachi

                        SDL_Rect Player_rect = g_player.GetRectFRAME();
                        /*
                        bool Collide1 = false;
                        vector<Shuriken *> enemy_bullets = g_threat->get_fire_list();
                        for (int c = 0; c < enemy_bullets.size(); ++c) {
                            Shuriken *threat_bullet = enemy_bullets.at(c);
                            if (threat_bullet) {
                                Collide1 = SDLAllFunction::CheckCollision(threat_bullet->GetRect(), Player_rect);
                                if (Collide1) {
                                    if(g_player.get_is_guarding()){
                                        for(int t = 0; t < FRAME_NUM ; t++){

                                            int x_pos = Player_rect.x + 20;
                                            int y_pos = Player_rect.y - 60;

                                            exp_main.set_frame(t); //frame thứ bao nhiêu
                                            exp_main.setRect(x_pos, y_pos);
                                            exp_main.ShowEffect(g_screen);

                                        }
                                        break;
                                    }
                                    else{
                                        g_player.is_damaged = true;
                                        g_player.Player_action(map_data);
                                        g_player.ShowMain(g_screen);
                                    }
                                }

                            }
                            g_player.is_damaged = false;

                        }
                        */
                        // Kiểm tra va chạm giữa naruto và các enemies
                        SDL_Rect Enemy_rect = g_threat->GetRectFRAME();
                        bool Collide2 = SDLAllFunction::CheckCollision(Player_rect, Enemy_rect);
                        int fall1 = g_player.get_is_falling();

                        if (Collide2 || fall1 > 0) {
                            g_player.reset_fall();
                            if (enemy_hp_temp > 0) {
                                if (g_player.get_is_attacking()) {
                                    g_threat->HealthDecrease();
                                    g_threat->Enemy_renderHP(g_screen, g_threat);

                                    g_threat->is_knocked = true;
                                    g_threat->ENEMY_Action(map_data);
                                    g_threat->ShowEnemy(g_screen);

                                    for (int t = 0; t < FRAME_NUM; t++) {

                                        int x_pos = Enemy_rect.x + 5;
                                        int y_pos = Enemy_rect.y - 50;

                                        exp_threat2.set_frame(t); //frame thứ bao nhiêu
                                        exp_threat2.setRect(x_pos, y_pos);
                                        exp_threat2.ShowEffect(g_screen);
                                    }
                                    continue;

                                }
                                else if(g_player.get_is_dashing()){
                                    break;
                                }
                                else if (g_player.get_is_guarding()) {
                                    for (int t = 0; t < FRAME_NUM; t++) {

                                        int x_pos = Player_rect.x + 20;
                                        int y_pos = Player_rect.y - 60;

                                        exp_main.set_frame(t); //frame thứ bao nhiêu
                                        exp_main.setRect(x_pos, y_pos);
                                        exp_main.ShowEffect(g_screen);

                                    }
                                    break;
                                } else if (!g_player.get_is_guarding()) {
                                    hp--; //Naruto có 5 mạng tất cả
                                    if (hp > 0) {
                                        g_player.is_damaged = true;
                                        g_player.Player_action(map_data);
                                        g_player.ShowMain(g_screen);

                                        player_hp.Set_frame_hp(5-hp);
                                        player_hp.setRect(20, 0);
                                        player_hp.Show_HP(g_screen);

                                        SDL_Delay(500);
                                        continue;
                                    } else {
                                        g_threat->FreeObject();
                                        option = END;
                                    }
                                }
                            }

                        }
                        if (enemy_hp_temp == 0) {
                            g_threat->FreeObject();
                            threats_list.erase(threats_list.begin() + i);
                        }

                    }
                    g_threat->is_knocked = false;
                    g_player.is_damaged = false;
                }

                vector<Shuriken *> bullet_arr = g_player.get_Shuri_packages();
                for (int a = 0; a < bullet_arr.size(); a++) {
                    Shuriken *bullet = bullet_arr.at(a);
                    if (bullet != NULL) {
                        for (int b = 0; b < threats_list.size(); b++) {
                            Enemy *obj_threat = threats_list.at(b);
                            int hp_temp = obj_threat->get_enemy_hp();//Khởi tạo máu cho quái

                            if (obj_threat != NULL) {
                                SDL_Rect rect1;
                                rect1.x = obj_threat->GetRect().x;
                                rect1.y = obj_threat->GetRect().y;
                                rect1.w = obj_threat->get_width_frame();
                                rect1.h = obj_threat->get_height_frame();

                                SDL_Rect rect2 = bullet->GetRect();

                                bool Collide = SDLAllFunction::CheckCollision(rect1, rect2);

                                if (Collide) {
                                    if (hp_temp > 0) {
                                        obj_threat->HealthDecrease();
                                        obj_threat->Enemy_renderHP(g_screen, obj_threat);

                                        //mark_val += 100;

                                        //Hiệu ứng chạy truoc

                                        for (int k = 0; k < FRAME_NUM; k++) {

                                            int x_pos = rect1.x;
                                            int y_pos = rect1.y;

                                            exp_threat.set_frame(k); //frame thứ bao nhiêu
                                            exp_threat.setRect(x_pos, y_pos);
                                            exp_threat.ShowEffect(g_screen);
                                        }
                                        g_player.RemoveShuri(a);
                                        continue;

                                    }
                                }
                                if (hp_temp == 0) {
                                    g_player.RemoveShuri(a);
                                    obj_threat->FreeObject();
                                    threats_list.erase(threats_list.begin() + b);
                                    break;
                                }
                            }

                        }
                    }
                }
                //Show game_time
                /*
                string time = "TIME: ";
                Uint32 time_value = SDL_GetTicks()/1000;
                Uint32 val_time = 300 - time_value;
                if(val_time <= 0){
                    if(MessageBox(NULL, reinterpret_cast<LPCSTR>("Game over"), reinterpret_cast<LPCSTR>("Info"), MB_OK | MB_ICONSTOP) == IDOK){

                        is_quit = true;
                        break;
                    }
                }
                else{
                    string str_val = to_string(val_time);
                    time += str_val;

                    time_game.Set_TEXT(time);
                    time_game.LoadFromRenderTEXT(font_time, g_screen);
                    time_game.RenderTEXT(g_screen, SCREEN_WIDTH - 200, 15);
                }
                 */

                /*
                string val_mark = to_string(mark_val);
                string strMark = "Mark: ";
                strMark += val_mark;

                mark_game.Set_TEXT(strMark);
                mark_game.LoadFromRenderTEXT(font_time, g_screen);
                mark_game.RenderTEXT(g_screen, SCREEN_WIDTH*0.5 - 50, 15);
                */


                int Chakra_ = g_player.Get_Chakra();
                string str_chakra = to_string(Chakra_) + "/" + "38";

                chakra.Set_TEXT(str_chakra);
                chakra.LoadFromRenderTEXT(font_time, g_screen);
                chakra.RenderTEXT(g_screen, SCREEN_WIDTH * 0.5 + 100, 25);




                //Load Boss in game

                int val = MAX_MAP_X * TILE_SZ - (map_data.begin_x + g_player.GetRect().x);
                if (val <= SCREEN_WIDTH) {
                    int temp_bossHP = bossObject.get_boss_HP();
                    bossObject.boss_renderHP(g_screen, &bossObject);
                    if (temp_bossHP > 0) {
                        bossObject.Map_vision(map_data.begin_x, map_data.begin_y);
                        bossObject.Boss_Action(map_data);
                        bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                        bossObject.Show_BOSS(g_screen);
                    }
                    //Check va chạm giữa bullet_boss và Naruto
                    vector<Shuriken *> bullet_boss_list = bossObject.get_bullet_list();
                    for (int b = 0; b < bullet_boss_list.size(); b++) {
                        Shuriken *bl_boss = bullet_boss_list.at(b);
                        if (bl_boss != NULL) {
                            SDL_Rect Naruto_rect = g_player.GetRectFRAME();
                            bool Collide3 = SDLAllFunction::CheckCollision(bl_boss->GetRect(), Naruto_rect);
                            if (Collide3) {
                                if (g_player.get_is_guarding()) {
                                    for (int t = 0; t < FRAME_NUM; t++) {

                                        int x_pos = Naruto_rect.x + 20;
                                        int y_pos = Naruto_rect.y - 60;

                                        exp_main.set_frame(t); //frame thứ bao nhiêu
                                        exp_main.setRect(x_pos, y_pos);
                                        exp_main.ShowEffect(g_screen);
                                    }

                                } else {
                                    hp--; //Naruto có 5 mạng tất cả
                                    if (hp > 0) {
                                        g_player.setRect(0, 0);
                                        g_player.set_comeback_time(50);

                                        player_hp.Set_frame_hp(5-hp);
                                        player_hp.setRect(20, 0);
                                        player_hp.Show_HP(g_screen);

                                        SDL_Delay(500);


                                        continue;
                                    } else {
                                        //bl_boss->FreeObject();
                                        option = END;
                                    }
                                }
                                bossObject.RemoveBullet(b);
                                break;
                            }

                        }
                    }

                    //Check va chạm giua boss VS shuriken
                    vector<Shuriken *> shuri_packs = g_player.get_Shuri_packages();
                    for (int x = 0; x < shuri_packs.size(); x++) {
                        Shuriken *shuri_shuri = shuri_packs.at(x);
                        if (shuri_shuri) {
                            SDL_Rect boss_rect = bossObject.GetRect();
                            bool Collide4 = SDLAllFunction::CheckCollision(boss_rect, shuri_shuri->GetRect());
                            if (Collide4) {
                                bossObject.HP_BOSS_Decrease();
                                bossObject.boss_renderHP(g_screen, &bossObject);
                                if (temp_bossHP > 0) {
                                    for (int t = 0; t < FRAME_NUM; t++) {

                                        int x_pos = boss_rect.x - 40;
                                        int y_pos = boss_rect.y + 60;

                                        exp_boss.set_frame(t); //frame thứ bao nhiêu
                                        exp_boss.setRect(x_pos, y_pos);
                                        exp_boss.ShowEffect(g_screen);

                                    }
                                    g_player.RemoveShuri(x);
                                    continue;

                                }
                                else if (temp_bossHP == 0) {

                                    bossObject.FreeObject();

                                    for (Shuriken *shuriken: bullet_boss_list) {
                                        delete shuriken;
                                    }
                                    bullet_boss_list.clear();
                                }
                            }
                        }
                    }
                    if(temp_bossHP == 0){
                        if (!musicPlayed2) { // Nếu âm thanh chưa được phát
                            if (Mix_PlayingMusic() == 0) {
                                g_start = Mix_LoadMUS("assets\\Sample 12.wav");
                                Mix_PlayMusic(g_start, 0);
                            }
                            musicPlayed2 = true; // Đánh dấu rằng âm thanh đã được phát
                        }
                    }

                }


                //boss_hp.Show_HP(g_screen);
                /*
                if(!textShown){
                    string intro1 = "Chapter 1: Infinite Tsukuyomi";
                    Intro.Set_TEXT(intro1);
                    Intro.LoadFromRenderTEXT(font_time, g_screen);

                    Intro.RenderTEXT(g_screen, 340 ,100);

                    //SDL_Delay(1000);
                    //textShown = true;
                }
                */
                SDL_RenderPresent(g_screen);

                if (map_data.tile[2][399] == 0 && g_player.Check_WIN()) {
                    g_player.FreeObject();
                    option = WIN;
                }

                int real_time = FPS.get_ticks();
                int time_per_frame = 1000 / FRAME_PER_SECOND; //Tính xem 1s thì chạy được bnh frame với 1000ms

                if (real_time < time_per_frame) {
                    int delay_time = time_per_frame - real_time;
                    if (delay_time > 0) {
                        SDL_Delay(delay_time);
                    }
                }

                break;
            }

            case PAUSE: {
                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                        break;
                    }
                    resumeButton.handleEvent(&g_event);
                    backButton.handleEvent(&g_event);
                    if (resumeButton.click()) {
                        g_player.set_option(PLAY);
                        option = PLAY;
                        break;
                    } else if (backButton.click()) {
                        option = START;
                        break;
                    }
                }
                SDL_SetRenderDrawColor(g_screen, 255, 255, 204, 0);
                SDL_RenderClear(g_screen);

                g_pauseBackground.toRender(g_screen, NULL);
                resumeButton.setPosition(350, 320);
                resumeButton.Show(g_screen);
                backButton.setPosition(350, 185);
                backButton.Show(g_screen);

                SDL_RenderPresent(g_screen);
                break;
            }

            case END: {
                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                        break;
                    }
                    backButton.handleEvent(&g_event);
                    if(backButton.click()){
                        option = START;
                        break;
                    }
                }

                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);
                g_loseBackground.toRender(g_screen, NULL);
                backButton.setPosition(560, 485);
                backButton.Show(g_screen);

                SDL_RenderPresent(g_screen);
                break;
            }

            case WIN: {
                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                        break;
                    }
                    nextButton.handleEvent(&g_event);
                    backButton.handleEvent(&g_event);
                    if(nextButton.click()){
                        option = NEXT_STAGE;
                        break;
                    }
                    if(backButton.click()){
                        option = START;
                        break;
                    }
                }
                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_winBackground.toRender(g_screen, NULL);
                backButton.setPosition(430, 450);
                backButton.Show(g_screen);
                nextButton.setPosition(610, 450);
                nextButton.Show(g_screen);

                SDL_RenderPresent(g_screen);
                break;
            }
            case NEXT_STAGE:
            {
                while (SDL_PollEvent(&g_event) != 0) {
                    if (g_event.type == SDL_QUIT) {
                        is_quit = true;
                        break;
                    }
                }
                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_nextStage.toRender(g_screen, NULL);

                SDL_RenderPresent(g_screen);
                break;
            }


        }
    }


    //if (g_music != nullptr) Mix_FreeMusic( g_music );

    //Hủy bỏ các trạng thái không cần thiết, dọn dẹp bộ nhớ
    for(int i = 0; i < threats_list.size(); i++){
        Enemy* g_threat = threats_list.at(i);
        if(g_threat){
            g_threat->FreeObject();
            g_threat = NULL;
        }
    }
    threats_list.clear();

    close();
    return 0;
}

//Bắt đầu định nghĩa hàm
void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

//Khởi tạo
void init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    g_window = SDL_CreateWindow("GAME CREATED BY DUC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (g_window == nullptr){
        logErrorAndExit("CreateWindow", SDL_GetError());
    }else{
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED|
                                                    SDL_RENDERER_PRESENTVSYNC);
        if (g_screen == nullptr){
            logErrorAndExit("CreateRenderer", SDL_GetError());
        }else{
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
            //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        }
    }
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    if(TTF_Init() == -1){
        logErrorAndExit("TTF_Init", TTF_GetError());
    }
    font_time = TTF_OpenFont("assets\\njnaruto.ttf", 40);
    if(font_time != NULL){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError() );
    }

}

//Load toàn bộ ảnh, âm thanh
bool loading_Media(){
    bool check1 = g_background.LoadingIMG("img\\Full_forest2.png", g_screen);
    bool check2 = g_pauseBackground.LoadingIMG("img\\Pause_background.png", g_screen);
    bool check3 = g_menuBackground.LoadingIMG("img\\Menu.png", g_screen);
    g_helpBackground.LoadingIMG("img\\Help_background.png", g_screen);
    g_loseBackground.LoadingIMG("img\\Game_over.png", g_screen);
    g_winBackground.LoadingIMG("img\\Game_winner.png", g_screen);
    g_nextStage.LoadingIMG("img\\Thank_you.png", g_screen);
    startButton.LoadingIMG("img\\Start_button.png", g_screen);
    exitButton.LoadingIMG("img\\Exit_button.png", g_screen);
    backButton.LoadingIMG("img\\Back_button.png", g_screen);
    helpButton.LoadingIMG("img\\Help_button.png", g_screen);
    resumeButton.LoadingIMG("img\\Resume_button.png", g_screen);
    nextButton.LoadingIMG("img\\Next_button.png", g_screen);

    if(!check1 || !check2 || !check3){
        return false;
    }
    return true;
}

void resetGame(MainObject& g_player, Game_Map& good_map, vector<Enemy*>& threats_list, BossObj& bossObject, HealthPower& player_hp, PlayerChakra& player_chakra){


    g_player.reset();


    good_map.LoadMap("map_matrix.txt");
    good_map.LoadingTiles(g_screen);

    // Reset danh sách quái vật

    threats_list = MakeThread_LIST();

    // Reset Boss
    bossObject.reset();
    bossObject.set_Xpos(MAX_MAP_X * TILE_SZ - SCREEN_WIDTH * 0.2);
    bossObject.set_Ypos(30);

    // Reset thanh máu

    player_hp.reset();
    player_hp.Set_clips_();

    // Reset chakra

    player_chakra.Init(g_screen);
    player_chakra.SetPosition(SCREEN_WIDTH * 0.5, 10);

    // Đặt lại các biến âm thanh
    musicPlayed1 = false;
    musicPlayed2 = false;

}

//Tạo quái
vector<Enemy*> MakeThread_LIST(){
    vector<Enemy*> list_enemies;
    Enemy* dynamic_threats = new Enemy [25];
    for(int i = 0; i < 25; i++){
        Enemy* g_threat = (dynamic_threats+i);
        if(g_threat != NULL){
            g_threat->LoadingIMG("img\\Obito_left.png" ,g_screen);
            g_threat->set_clips();
            g_threat->set_type_Move(Enemy::MOVEABLE_OBJ);
            g_threat->SetX_pos(900 + i*600);
            g_threat->SetY_pos(350);

            int pos1 = g_threat->getX_pos() - 50;
            int pos2 = g_threat->getX_pos() + 50;
            g_threat->set_AnimationPos(pos1,pos2);
            g_threat->set_input_LEFT(1);
            list_enemies.push_back(g_threat);
        }
    }
    /*
    Enemy* threats_obj = new Enemy [20];

    for(int i = 0 ; i< 20; i++){
        Enemy* g_threat = (threats_obj+i);
        if(g_threat != NULL){
            g_threat->LoadingIMG("itachi_LEFT.png", g_screen);
            g_threat->set_clips();
            g_threat->SetX_pos(400 + i*1200);
            g_threat->SetY_pos(260);
            g_threat->set_type_Move(Enemy::STATIC_OBJ);

            Shuriken* p_fire = new Shuriken();
            g_threat->InitFire(p_fire, g_screen); //Itachi đã khởi tạo fire ball nên hàm main có thể sử dụng Jujutsu

            list_enemies.push_back(g_threat);
        }
    }
    */
    return list_enemies;
}

//Đóng game
void close(){
    g_background.FreeObject();
    g_winBackground.FreeObject();
    g_loseBackground.FreeObject();
    g_menuBackground.FreeObject();
    g_helpBackground.FreeObject();
    g_pauseBackground.FreeObject();
    startButton.freeB();
    exitButton.freeB();
    backButton.freeB();
    resumeButton.freeB();
    helpButton.freeB();

    g_background.FreeObject();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_FreeMusic(g_start);
    g_start = NULL;
    Mix_FreeMusic(g_winBoss);
    g_window = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}