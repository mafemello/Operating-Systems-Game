#ifndef DISPLAY_CONTEXT
#define DISPLAY_CONTEXT

#include "../timer.h"

class DisplayContext {
    public:
        std::string content;
        Timer *timer;
        bool stop;

        DisplayContext();

        DisplayContext(std::string content, Timer *timer, bool stop);
};

#endif
