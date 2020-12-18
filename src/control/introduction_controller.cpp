#include "../../include/control/controllers.h"
#include <iostream>

IntroductionController::IntroductionController(
        GameContext *context, std::string username, int current_question) 
        : Controller(context, current_question + 1) {
    this->username = username;
}

IntroductionController::~IntroductionController() {}

bool IntroductionController::is_last_controller() { return false; }

DisplayContext IntroductionController::get_display_context() {
    std::string content = "Olá, " + username + ", vamos começar com as "
        "regras: Você tem 30 segundos para responder cada pergunta. Digite "
        "a alternativa (ex.: 'b'), e o temporizador para.\n"
        "Se o tempo acabar ou você responder errado, você perde tudo.\n"
        "\nA cada 5 alternativas corretas, você recebe uma pontuação. "
        "Caso não saiba uma pergunta, você sempre pode escolher a "
        "alternativa 'E', desse modo, você não é eliminado."
        "\nPressione enter para começar.";
    return DisplayContext(content, &context->timer, false);
}

void IntroductionController::handle_input() {
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *IntroductionController::next() {
    if (jump_to_last_page)
        return new ResultsController(context, current_question + 1);
    return new QuestionController(context, current_question + 1);
}

