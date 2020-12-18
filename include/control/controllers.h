#ifndef CONTROLLERS
#define CONTROLLERS

#include "../display/display_context.h"
#include "game_context.h"
#include <thread>

class Controller {
    public:
        Controller(GameContext *context, int current_question);

        virtual ~Controller();

        virtual bool is_last_controller();

        virtual DisplayContext get_display_context();
        
        virtual void handle_input();

        virtual Controller *next();

    protected:
        GameContext *context;
        int current_question;
        bool jump_to_last_page;
};

class StartingController : public Controller {
    public:
        StartingController(GameContext *context);

        ~StartingController();

        bool is_last_controller();

        DisplayContext get_display_context();
        
        void handle_input();

        Controller *next();

    private:
        std::string username;
};

class IntroductionController : public Controller {
    public:
        IntroductionController(GameContext *context, std::string username,
                int current_question);

        ~IntroductionController();

        bool is_last_controller();

        DisplayContext get_display_context();
        
        void handle_input();

        Controller *next();

    private:
        std::string username;
};

class QuestionController : public Controller {
    public:
        QuestionController(GameContext *context, int current_question);

        ~QuestionController();

        bool is_last_controller();

        DisplayContext get_display_context();
        
        void handle_input();

        Controller *next();
};

class ResultsController : public Controller {
    public:
        ResultsController(GameContext *context, int current_question);

        ~ResultsController();

        bool is_last_controller();

        DisplayContext get_display_context();
        
        void handle_input();

        Controller *next();
};

#endif
