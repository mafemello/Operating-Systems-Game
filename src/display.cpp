#include "../include/display.hpp"
#include <iostream>
#include <thread>

static void display_introduction();
static void display_greetings(SharedBuffer<DisplayState> *buffer);
static void display_question(SharedBuffer<DisplayState> *buffer);
static void display_results(SharedBuffer<DisplayState> *buffer);
static std::string build_starting_page();
static std::string build_introduction_page(std::string username);
static std::string build_question_page(std::string question, int prize);
static std::string build_results_page(int prize);

void display_loop(SharedBuffer<DisplayState> *buffer, std::atomic<bool> *stop) {
    display_introduction();
    display_greetings(buffer);
    while(!(*stop))
        display_question(buffer);
    display_results(buffer);
}

static void display_introduction() {
    std::system("tput reset");
    std::cout << build_starting_page() << std::endl;
}

static void display_greetings(SharedBuffer<DisplayState> *buffer) {
    buffer->allow_write();
    std::string username = buffer->read().text_content;
    std::system("tput reset");
    std::cout << build_introduction_page(username) << std::endl;
}

static void display_question(SharedBuffer<DisplayState> *buffer) {
    buffer->allow_write();
    DisplayState state = buffer->read();
    std::system("tput reset");
    std::cout << build_question_page(state.text_content, state.prize) << std::endl;
    std::thread([=]{
        while(state.current_timer->is_running()) {
            std::cout << "\r" << state.current_timer->to_string() 
                << std::string(50, ' ') << "Resposta: " << std::flush;
        }
    }).detach();
}

static void display_results(SharedBuffer<DisplayState> *buffer) {
    buffer->allow_write();
    DisplayState state = buffer->read();
    std::system("tput reset");
    std::cout << build_results_page(state.prize) << std::endl;
    std::cout << "Pressione enter para sair..." << std::endl;
}

std::string build_starting_page() {
    return std::string("Bem-vinde ao jogo 'Quem Quer Ser um Milionário?'.\n"
                "Você está pronte? Diga-nos seu nome:");
}

std::string build_introduction_page(std::string username) {
	return std::string("\nOlá, " + username + ", vamos começar com as regras: "
        "Você tem 30 segundos para responder cada pergunta. Digite "
        "a alternativa (ex.: 'b'), e o temporizador para.\n"
        "Se o tempo acabar ou você responder errado, você perde tudo.\n"
        "\nA cada 5 alternativas corretas, você recebe uma pontuação. "
        "Caso não saiba uma pergunta, você sempre pode escolher a "
        "alternativa 'E', desse modo, você não é eliminado."
        "\nPressione enter para começar.");
}

std::string build_question_page(std::string question, int prize) {
    return std::string("Prêmio: " + std::to_string(prize) + "\n" + question);
}

std::string build_results_page(int prize) {
    return std::string((prize == 1000000 ? 
        "Parabéns!!! Você ganhou o jogo e agora é milionário!"
        : ("Fim de jogo. Você ganhou $" + std::to_string(prize))));
}
