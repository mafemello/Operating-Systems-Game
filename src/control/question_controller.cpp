#include "../../include/control/controllers.h"
#include "../../include/utils.h"
#include <iostream>

static const std::vector<int> PRIZES({0, 50000, 75000, 250000, 1000000});

QuestionController::QuestionController(GameContext *context, int current_question) 
    : Controller(context, current_question) { }

QuestionController::~QuestionController() {}

bool QuestionController::is_last_controller() { return false; }

DisplayContext QuestionController::get_display_context() {
    int prize = PRIZES[context->correct_answers / 5];
    std::string question = "Prêmio: $" + std::to_string(prize) + "\n\n"
        + context->questions_manager.get_next_question() + "\n";
    context->timer.start();
    return DisplayContext(question, &context->timer, false);
}

void QuestionController::handle_input() {
    char input = std::cin.get();
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    jump_to_last_page = !context->timer.is_running(); 
    if (!jump_to_last_page) {
        bool is_correct = context->questions_manager.answer_is_correct(input);
        bool is_ignore = context->questions_manager.answer_is_ignore(input);
        context->correct_answers += is_correct ? 1 : 0;
        context->timer.reset();
        jump_to_last_page = !is_correct && !is_ignore;
    }
}

Controller *QuestionController::next() {
    if (jump_to_last_page)
        return new ResultsController(context, current_question + 1);
    return new QuestionController(context, current_question + 1);
}
