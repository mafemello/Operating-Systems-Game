#include "../../include/control/controllers.h"
#include <iostream>

static const std::vector<int> PRIZES({0, 50000, 75000, 250000, 1000000});

ResultsController::ResultsController(GameContext *context, int current_question) 
    : Controller(context, current_question) {}

ResultsController::~ResultsController() {}

bool ResultsController::is_last_controller() { return true; }

DisplayContext ResultsController::get_display_context() {
    std::string content;
    int prize = PRIZES[context->correct_answers / 5];
    if (prize == 1000000)
        content = "Parabéns!!! Você ganhou o jogo e agora é milionário!";
    else 
        content = "Fim de jogo. Você ganhou $" + std::to_string(prize) + "\n\n";
    content += "Pressione enter para sair...";
    return DisplayContext(content, &context->timer, true);
}

void ResultsController::handle_input() {
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *ResultsController::next() {
    return NULL;
}
