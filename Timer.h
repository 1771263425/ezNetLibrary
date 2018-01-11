//
// Created by Binliu on 2017/11/21.
//

#ifndef TEST2_TIMER_H
#define TEST2_TIMER_H

#include <stdint.h>

extern "C" {

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#endif
}
class Timer {
public:
    Timer(){};
    ~Timer();
Timer(uint16_t ms);
    void init(uint16_t ms);
    virtual void onTimer();

private:
#ifdef _WIN32
  static void CALLBACK onCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
    unsigned int id;
#else
    void onCallback(int arg)
#endif
};


#endif //TEST2_TIMER_H
