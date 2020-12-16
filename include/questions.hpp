#ifndef QUESTION
#define QUESTION

#include "shared_buffer.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <atomic>

class QuestionsManager {
    private:
        std::ifstream questions_file;
        SharedBuffer<std::string> next_question_buffer;
        int current_question;
        std::atomic<bool> *should_stop;

        void read_next_question();

    public:
        QuestionsManager(std::string &questions_adderess, 
                         std::atomic<bool> *should_stop);

        ~QuestionsManager();

        std::string get_next_question();

        bool answer_is_correct(char answer);
        
        bool answer_is_ignore(char answer);
};

#endif
