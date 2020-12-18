#include "../../include/display/pages_manager.h"
#include <iostream>

PagesManager::PagesManager(SharedBuffer<DisplayContext> *buffer) {
    this->buffer = buffer;
    next_page();
}

PagesManager::~PagesManager() {}

void PagesManager::display_page() {
    std::system("tput reset");
    std::cout << context.content << std::endl;
    bool clear_after = context.timer->is_running();
    while(context.timer->is_running()) {
        std::cout << "\r" << context.timer->to_string() 
            << std::string(50, ' ') << "Resposta: " << std::flush;
    }
    if (clear_after) {
        std::system("tput reset");
        if (context.timer->timed_out())
            std::cout << "Aperte enter para ver os resultados..." << std::endl;
    }
}

bool PagesManager::is_at_last_page() {
    return context.stop;
}

void PagesManager::next_page() {
    if (!context.stop)
        context = buffer->read();
}
