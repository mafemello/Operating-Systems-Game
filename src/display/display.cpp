#include "../../include/display/display.h"

#include <iostream>
Display::Display(SharedBuffer<DisplayContext> *buffer) {
    display_thread = std::thread([=]{
        PagesManager pages_manager(buffer);
        while(!pages_manager.is_at_last_page()) {
            pages_manager.display_page();
            pages_manager.next_page();
        }
        pages_manager.display_page();
    });
}

Display::~Display() {}

void Display::start_detached() {
    display_thread.detach();
}

void Display::start_joined() {
    display_thread.join();
}
