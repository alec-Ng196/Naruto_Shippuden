//
// Created by Admin on 16/4/2024.
//

#ifndef NARUTOSHIPPUDEN_TIMEHANDLE_H
#define NARUTOSHIPPUDEN_TIMEHANDLE_H

class Timer{
public:
    Timer();
    ~Timer();
    void start();
    int get_ticks();

private:
    int start_tick;
    int pause_tick;
    bool is_paused_;
    bool is_start_;

};
#endif //NARUTOSHIPPUDEN_TIMEHANDLE_H
