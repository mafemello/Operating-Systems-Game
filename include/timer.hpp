#ifndef TIMER
#define TIMER

#include "shared_buffer.hpp"
#include <atomic>
#include <string>
#include <functional>

typedef void (*TimeoutCallback)();

class Timer {
    private: 
        std::atomic<bool> *stop;
        std::atomic<bool> timer_is_running;
        std::atomic<int> time_left; 
        TimeoutCallback timeout_callback;
        int starting_time;

    public:
        Timer(int starting_time, std::atomic<bool> *stop);

        void start(TimeoutCallback timeout_callback);

        std::string to_string();

        void reset();

        bool timed_out();

        bool is_running();
};

#endif
