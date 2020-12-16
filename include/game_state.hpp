#ifndef GAME_STATE
#define GAME_STATE

#include <string>
#include "timer.hpp" 
#include <atomic>

class GameState {
    public:
        std::atomic<bool> *stop;
        int current_question;
        int correct_answers;
        Timer timer;

        GameState(std::atomic<bool> *stop); 
};

#endif
