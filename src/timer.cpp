#include "../include/timer.hpp"
#include <thread>
#include <iostream>

Timer::Timer(int starting_time, std::atomic<bool> *stop) {
    this->starting_time = starting_time;
    this->stop = stop;
    time_left = starting_time;
    timer_is_running = false;
}


void Timer::start() {
    std::thread([=]{ 
        time_left = starting_time;
        timer_is_running = true;
        while(time_left > 0 && !(*stop) && timer_is_running) {
            time_left--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        *stop = !timer_is_running;
        timer_is_running = false;
    }).detach();
}

std::string Timer::to_string() {
    std::string str = "Tempo remanescente: [";
    str.append(std::string(time_left, '#'));
    str.append(std::string(starting_time - time_left, ' '));
    str.append("]").append(std::to_string(time_left)).append("s");
    return str;
}
        
void Timer::reset() {
    timer_is_running = false;
    time_left = starting_time;     
}
        
bool Timer::timed_out() {
    return time_left == 0;
}
        
bool Timer::is_running() {
    return timer_is_running;
}
