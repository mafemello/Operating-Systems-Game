#include "../include/timer.hpp"
#include <thread>
#include <iostream>

Timer::Timer(int starting_time, std::atomic<bool> *stop) {
    this->starting_time = starting_time;
    this->stop = stop;
    this->timeout_callback = []{};
    time_left = starting_time;
    timer_is_running = false;
    std::thread([=]{ 
        while(!(*stop)) {
            if (time_left > 0 && timer_is_running)
                time_left--;
            else {
                timer_is_running = false;
                timeout_callback();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}

void Timer::start(TimeoutCallback timeout_callback) {
    timer_is_running = true;
    time_left = starting_time;
    this->timeout_callback = timeout_callback;
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
