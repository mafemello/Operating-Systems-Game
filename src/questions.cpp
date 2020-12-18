#include "../include/questions_manager.h"
#include <fstream>
#include <thread>
#include <ctype.h>

#define NUMBER_OF_QUESTIONS 20
#define NUMBER_OF_ALTERNATIVES 4
#define REFUSE_TO_ANSWER "E - Não responder"

using namespace std;

const std::vector<char> CORRECT_ANSWERS({
    'A', 'C', 'D', 'C', 'B', 'D', 'A', 'A', 'A', 'C',
    'B', 'B', 'A', 'D', 'D', 'B', 'D', 'A', 'C', 'B'
});

void QuestionsManager::read_next_question() {
    if (is_running) {
        std::string next_question;
        std::getline(questions_file, next_question);
        std::string aux;
        for (int i = 0; i < NUMBER_OF_ALTERNATIVES; i++) {
            std::getline(questions_file, aux);
            next_question.append("\n").append(aux);
        }
        std::getline(questions_file, aux);
        next_question.append("\n").append(std::string(REFUSE_TO_ANSWER));
        next_question_buffer.write(next_question);
    }
}

QuestionsManager::QuestionsManager(const std::string &questions_address) {
    questions_file.open(questions_address);
    current_question = -1;
    is_running = true;
    sem_init(&stop, 0, 0);
    thread([=]{
        while(is_running) {
            read_next_question();
        }
        sem_post(&stop);
    }).detach();
}

QuestionsManager::~QuestionsManager() {
    is_running = false;
    get_next_question();
    sem_wait(&stop);
    questions_file.close();
}

std::string QuestionsManager::get_next_question() {
    if (current_question >= NUMBER_OF_QUESTIONS)
        return string("");
    std::string question = next_question_buffer.read();
    current_question++;
    return question;
}

bool QuestionsManager::answer_is_correct(char answer) {
    return toupper(answer) == CORRECT_ANSWERS[current_question];
}

bool QuestionsManager::answer_is_ignore(char answer) {
    return toupper(answer) == 'E';
}
