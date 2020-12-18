#ifndef DISPLAY
#define DISPLAY

#include "display_context.h" 
#include "pages_manager.h" 
#include "../shared_buffer.h"
#include <thread>
#include <atomic>

class Display {
    public:
        Display(SharedBuffer<DisplayContext> *buffer);

        ~Display();

        void start_detached();
        
        void start_joined();

    private:
        SharedBuffer<DisplayContext> *buffer;
        std::thread display_thread;
};

#endif
