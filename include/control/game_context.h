#ifndef GAME_CONTEXT
#define GAME_CONTEXT

#include "../questions_manager.h"
#include "../timer.h" 
#include <curses.h>

class GameContext {
    public:
        QuestionsManager questions_manager;
        Timer timer;
        int correct_answers;

        GameContext(const std::string questions_addr, int questions_timeout); 
};

#endif
