#include "../../include/control/game_context.h"

GameContext::GameContext(const std::string questions_addr, int questions_timeout)
    :  questions_manager(questions_addr), timer(questions_timeout) {
    correct_answers = 0;
}

