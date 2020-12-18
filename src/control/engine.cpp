#include "../../include/control/engine.h"
#include "../../include/utils.h"
#include <iostream>

#define TIMER_TIMEOUT 30

Engine::Engine(SharedBuffer<DisplayContext> *buffer, std::string questions_address) 
        : context(questions_address, TIMER_TIMEOUT){
    current_controller = new StartingController(&context);
    engine_thread = std::thread([=] {
            while(!current_controller->is_last_controller()) {
                buffer->write(current_controller->get_display_context());
                current_controller->handle_input();
                delete_and_assign(&current_controller, current_controller->next());
            }
            buffer->write(current_controller->get_display_context());
            current_controller->handle_input();
    });
}

Engine::~Engine() {
    delete current_controller;
}

void Engine::start_detached() {
    engine_thread.detach();
}

void Engine::start_joined() {
    engine_thread.join();
}
