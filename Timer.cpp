//
// Created by Binliu on 2017/11/21.
//

#include "Timer.h"


void Timer::init(uint16_t ms) {
#ifdef _WIN32
    id=timeSetEvent(ms, 0, onCallback, (DWORD_PTR)this, TIME_PERIODIC);
#else
    struct itimerval tick;
	signal(SIGALRM, onCallback);
	tick.it_value.tv_sec = 0;  // sec
	tick.it_value.tv_usec = ms*1000; // micro sec.
								  // Interval time to run function
	tick.it_interval.tv_sec = 0;
	tick.it_interval.tv_usec = ms*1000;
	int res = setitimer(ITIMER_REAL, &tick, NULL);
	if (res) {
		printf("Set timer failed!!\n");
	}
#endif
}

Timer::Timer(uint16_t ms) {
    init(ms);
}

#ifdef _WIN32
void CALLBACK Timer::onCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser,
                                DWORD_PTR dw1, DWORD_PTR dw2)
{
  Timer*timer=(Timer*)dwUser;
    timer->onTimer();
}

Timer::~Timer() {
    timeKillEvent(id);
}
#endif

void Timer::onTimer() {}
