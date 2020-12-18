#include <thread>
#include <atomic>
#include <iostream>
#include "../include/display/display.h"
#include "../include/control/engine.h"

const std::string questions_addr = "questions.txt";

#define WINDOW_HEIGHT 50
#define WINDOW_WIDTH 50

int main(void) {
    std::cout << "\e[?25l";
    SharedBuffer<DisplayContext> display_context;
    Display display(&display_context);
    Engine engine(&display_context, questions_addr);
    display.start_detached();
    engine.start_joined();
    std::cout << "\e[?25h";
    return 0;
}
