#ifndef TIMER
#define TIMER

#include <atomic>
#include <string>

class Timer {
    private: 
        std::atomic<bool> *stop;
        std::atomic<bool> timer_is_running;
        std::atomic<int> time_left; 
        int starting_time;

    public:
        Timer(int starting_time, std::atomic<bool> *stop);

        void start();

        std::string to_string();

        void reset();

        bool timed_out();

        bool is_running();
};

#endif
