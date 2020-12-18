#ifndef QUESTION
#define QUESTION

#include "shared_buffer.h"
#include <semaphore.h>
#include <string>
#include <fstream>
#include <vector>
#include <atomic>

class QuestionsManager {
    private:
        sem_t stop;
        std::atomic<bool> is_running;
        std::ifstream questions_file;
        SharedBuffer<std::string> next_question_buffer;
        int current_question;

        void read_next_question();

    public:
        QuestionsManager(const std::string &questions_adderess);

        ~QuestionsManager();

        std::string get_next_question();

        bool answer_is_correct(char answer);
        
        bool answer_is_ignore(char answer);
};

#endif
