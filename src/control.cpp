#include "../include/control.hpp"
#include "../include/questions.hpp"
#include "../include/game_state.hpp"
#include "../include/utils.hpp"
#include <iostream>

const std::vector<int> PRIZES({0, 50000, 75000, 250000, 1000000});

static void handle_username(SharedBuffer<DisplayState> *buffer);
static void provide_question(SharedBuffer<DisplayState> *buffer, 
                             QuestionsManager *questions_manager,
                             GameState *game_state);
static void handle_answer(GameState *state, QuestionsManager *questions_manager);
static void provide_results(SharedBuffer<DisplayState> *buffer, GameState *game_state);


void control_loop(SharedBuffer<DisplayState> *buffer, std::atomic<bool> *stop) {
    std::string questions_address = "questions.txt";
    QuestionsManager questions_manager(questions_address, stop);
    GameState state(stop);
    handle_username(buffer);
    std::cin.ignore();
    std::cin.get();
    while(!(*state.stop)) {
        provide_question(buffer, &questions_manager, &state);
        handle_answer(&state, &questions_manager);
        state.current_question++;
        *state.stop = *state.stop || state.current_question >= 20;
    }
    provide_question(buffer, &questions_manager, &state);
    provide_results(buffer, &state);
}

static void handle_username(SharedBuffer<DisplayState> *buffer) {
    std::string input;
    std::cin >> input;
    DisplayState new_state;
    new_state.text_content = input;
    new_state.prize = 0;
    new_state.current_timer = NULL;
    buffer->write(new_state);
    buffer->allow_read();
}

static void provide_question(SharedBuffer<DisplayState> *buffer, 
                             QuestionsManager *questions_manager,
                             GameState *game_state) {
    DisplayState new_state;
    new_state.text_content = questions_manager->get_next_question();
    new_state.prize = PRIZES[game_state->correct_answers / 5];
    new_state.current_timer = &game_state->timer;
    buffer->write(new_state);
    buffer->allow_read();
    game_state->timer.start(write_any_input);
}

static void handle_answer(GameState *state, QuestionsManager *questions_manager) {
    char input;
    std::cin >> input;
    if (state->timer.is_running()) {
        if (questions_manager->answer_is_correct(input)) {
            std::cout << "Answer is correct" << std::endl;
            state->correct_answers++;
            state->timer.reset();
        } else if(questions_manager->answer_is_ignore(input)) {
            std::cout << "Answer is skip" << std::endl;
            state->timer.reset();
        } else {
            std::cout << "Answer is wrong" << std::endl;
            *(state->stop) = true;
        }
    } else {
        *(state->stop) = true;
    }
    std::cin.clear();
}

static void provide_results(SharedBuffer<DisplayState> *buffer, GameState *game_state) {
    DisplayState new_state;
    new_state.text_content = "";
    new_state.prize = PRIZES[game_state->correct_answers / 5];
    new_state.current_timer = &game_state->timer;
    buffer->write(new_state);
    buffer->allow_read();
    //game_state->timer.start();
}
