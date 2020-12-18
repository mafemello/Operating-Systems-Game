#include "../../include/control/controllers.h"
#include <iostream>

StartingController::StartingController(GameContext *context) 
    : Controller(context, -2) {}

StartingController::~StartingController() {}

bool StartingController::is_last_controller() { return false; }

DisplayContext StartingController::get_display_context() {
    std::string content = "Bem-vinde ao jogo 'Quem Quer Ser um Milionário?'.\n"
        "Você está pronte? Diga-nos seu nome:";
    return DisplayContext(content, &context->timer, false);
}

void StartingController::handle_input() {
    std::getline(std::cin, username);
}

Controller *StartingController::next() {
    if (jump_to_last_page)
        return new ResultsController(context, current_question + 1);
    return new IntroductionController(context, username, current_question + 1);
}

