#ifndef DISPLAY
#define DISPLAY

#include "shared_buffer.hpp"
#include "timer.hpp"
#include <string>
#include <atomic>

class DisplayState {
    public:
        std::string text_content;
        Timer *current_timer;
        int prize;
};

void display_loop(SharedBuffer<DisplayState> *buffer, std::atomic<bool> *stop); 

#endif
