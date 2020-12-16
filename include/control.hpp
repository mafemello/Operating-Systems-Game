#ifndef CONTROL
#define CONTROL

#include "display.hpp"
#include <atomic>

void control_loop(SharedBuffer<DisplayState> *buffer, std::atomic<bool> *stop);

#endif
