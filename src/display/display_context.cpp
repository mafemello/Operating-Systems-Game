#include "../../include/display/display_context.h"

DisplayContext::DisplayContext() {
    content = "";
    timer = NULL;
    stop = false;
}

DisplayContext::DisplayContext(std::string content, Timer *timer, bool stop) {
    this->content = content;
    this->timer = timer;
    this->stop = stop;
}
