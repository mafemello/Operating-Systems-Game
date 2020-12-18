#include "../include/timer.h"
#include <thread>

Timer::Timer(int starting_time) {
    this->starting_time = starting_time;
    time_left = starting_time;
    timer_is_running = false;
    sem_init(&stop, 0, 0);
}

Timer::~Timer() {
    reset();
}

void Timer::start() {
    if (is_running() || timed_out())
        reset();
    timer_is_running = true;
    time_left = starting_time;
    std::thread([=]{ 
        while(time_left > 0 && timer_is_running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            time_left--;
        }
        if (!timer_is_running)
            sem_post(&stop);
        timer_is_running = false;
    }).detach();
}
        
void Timer::reset() {
    if (timer_is_running) {
        timer_is_running = false;
        sem_wait(&stop);
        time_left = starting_time;     
    }
}

std::string Timer::to_string() {
    std::string str = "Tempo remanescente: [";
    str.append(std::string(time_left, '#'));
    str.append(std::string(starting_time - time_left, ' '));
    str.append("]").append(std::to_string(time_left)).append("s");
    return str;
}
        
bool Timer::timed_out() {
    return time_left == 0;
}
        
bool Timer::is_running() {
    return timer_is_running;
}
