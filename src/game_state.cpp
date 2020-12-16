#include "../include/game_state.hpp"

#define TIMEOUT 30

GameState::GameState(std::atomic<bool> *stop) : timer(TIMEOUT, stop){
    this->stop = stop;
    current_question = 0;
    correct_answers = 0;
}
