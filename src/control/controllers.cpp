#include "../../include/control/controllers.h"

Controller::Controller(GameContext *context, int current_question) {
    this->context = context;
    this->current_question = current_question;
    jump_to_last_page = false;
}

Controller::~Controller() {}

bool Controller::is_last_controller() { return false; }

DisplayContext Controller::get_display_context() { return DisplayContext(); }

void Controller::handle_input() {}

Controller *Controller::next() { return NULL; }
