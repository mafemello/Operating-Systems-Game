#ifndef TIMER
#define TIMER

#include "shared_buffer.h"
#include "semaphore.h"
#include <atomic>
#include <string>

class Timer {
    private: 
        sem_t stop;
        std::atomic<bool> timer_is_running;
        std::atomic<int> time_left; 
        int starting_time;

    public:
        Timer(int starting_time);

        ~Timer();

        void start();

        void reset();
        
        std::string to_string();

        bool timed_out();

        bool is_running();
};

#endif
