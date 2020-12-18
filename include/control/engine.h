#ifndef CONTROL
#define CONTROL

#include "../display/display_context.h"
#include "controllers.h"
#include "game_context.h"
#include <atomic>
#include <thread>

class Engine {
    public:
        Engine(SharedBuffer<DisplayContext> *buffer, 
                const std::string questions_addr);

        ~Engine();

        void start_detached();

        void start_joined();

    private:
        Controller *current_controller;
        GameContext context;
        std::thread engine_thread;
};

#endif
