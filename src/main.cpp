#include <thread>
#include <atomic>
#include "../include/display.hpp"
#include "../include/control.hpp"

int main(void) {
    std::atomic<bool> stop;
    stop = false;
    SharedBuffer<DisplayState> display_state;
    std::thread(control_loop, &display_state, &stop).detach();
    std::thread(display_loop, &display_state, &stop).join();
    return 0;
}
