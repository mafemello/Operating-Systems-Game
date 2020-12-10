/*
	Who Wants to be a Bilionaire? - The Game
	SSC0140 - Operating Systems I
	Profª Kalinka Regina Castelo Branco

	Group: 
		Cesar Guibo - nUSP:
		Leonardo Fonseca Pinheiro - nUSP:
		Maria Fernanda Lucio de Mello - nUSP: 11320860
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>
#include <fstream>
#include <functional>
#include <semaphore.h>
#include <ctype.h>
#include <atomic>

#include <time.h>

#define NUMBER_OF_QUESTIONS 20
#define NUMBER_OF_ALTERNATIVES 4
#define REFUSE_TO_ANSWER "E - Não responder"
#define NUMBER_OF_PRIZES 5
#define MAX_PRIZE 1000000

using namespace std;

const int PRIZES[NUMBER_OF_PRIZES] = {0, 50000, 75000, 250000, 1000000};

const char ANSWERS[NUMBER_OF_QUESTIONS] = {
    'A', 'C', 'D', 'C', 'B', 'D', 'A', 'A', 'A', 'C',
    'B', 'B', 'A', 'D', 'D', 'B', 'D', 'A', 'C', 'B'
};

template <class T> class SharedBuffer {
    private:
        sem_t can_read;
        sem_t can_write;
        T content;
    public: 
        SharedBuffer() {
            sem_init(&this->can_read, 0, 0);
            sem_init(&this->can_write, 0, 0);
        }

        void allow_read() {
            sem_post(&this->can_read);
        }

        void allow_write() {
            sem_post(&this->can_write); 
        }

        T read() {
            sem_wait(&this->can_read);
            return this->content;
        }

        void write(T data) {
            sem_wait(&this->can_write);
            this->content = T();
            this->content = data;
        }
};

class Game {
    private:
        SharedBuffer<string> *str_buffer;
        SharedBuffer<char> *char_buffer;
        atomic<bool> *game_ended;
        atomic<bool> question_answered;
        thread reader;
        bool lost;
        int current_question;
        int points;

    public:
        Game(SharedBuffer<string> *str_buffer, SharedBuffer<char> *char_buffer,
                atomic<bool> *game_ended) {
            this->str_buffer = str_buffer;
            this->char_buffer = char_buffer;
            this->current_question = 0;
            this->points = 0;
            this->lost = false;
            this->game_ended = game_ended;
        }

        void display_home() {
            system("tput reset");
            cout << "Bem-vinde ao jogo 'Quem Quer Ser um Milionário?'.\n"
                "Você está pronte? Diga-nos seu nome:" << endl;
        }
        void display_greetings() {
            this->str_buffer->allow_write();
            string name  = this->str_buffer->read();
            system("tput reset");
	        cout << "\nOlá, " << name << ", vamos começar com as regras: "
                "Você tem 30 segundos para responder cada pergunta. Digite "
                "a alternativa (ex.: 'b'), e o temporizador para.\n"
                "Se o tempo acabar ou você responder errado, você perde tudo.\n"
                "\nA cada 5 alternativas corretas, você recebe uma pontuação. "
                "Caso não saiba uma pergunta, você sempre pode escolher a "
                "alternativa 'E', desse modo, você não é eliminado."
                "\nPressione 'E' para começar." << endl;
        }

        void display_timer(int limit) {
            for (int i = limit; i >= 1 && !question_answered; i--) {
                cout << "\rTempo remanescente: [" 
                    << string(i, '#') << string(30 - i, ' ') << "] " 
                    << i << "s" << string(50, ' ')
                    << "Resposta: " << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            lost = !question_answered;
            if (lost)
                cin.putback('a');
        }

        void display_question(bool save_point_reached, int prize) {
            this->str_buffer->allow_write();
            string question = this->str_buffer->read();
            system("tput reset");
            if (save_point_reached)
                cout << "Parabéns. Você ganhou $" << prize << "\n";
            cout << "\n" << question << "\n";
            thread([=]{this->display_timer(30);}).detach();
        }

        bool game_started() {
            char_buffer->allow_write();
            return toupper(char_buffer->read()) == 'E';
        }

        void verify_answer() {
            char_buffer->allow_write();
            char answer = toupper(char_buffer->read());
            question_answered = true;
            bool is_correct = answer == ANSWERS[this->current_question++];
            bool skipped = answer == 'E';
            if (is_correct && !skipped)
                points++;
            lost = !is_correct && !skipped;
        }

        void display_results(int prize) {
            system("tput reset");
            if (prize == MAX_PRIZE) cout << "Parabéns!!! Você ganhou o jogo e agora é milionário!" << endl;
            else cout << "Fim de jogo. Você ganhou $" << prize << endl;
        }

        void start() {
            this->display_home();
            this->display_greetings();
            while(!game_started());
            for (int i = 1; i <= NUMBER_OF_QUESTIONS && !lost; i++) {
                question_answered = false;
                display_question(points % 5 == 0, PRIZES[points / 5]);
                verify_answer();
            }
            display_results(PRIZES[points / 5]);
            *game_ended = true;
            this->char_buffer->allow_write();
            this->str_buffer->allow_write();
            cin.putback('a');
        }
};

class Reader {
    private:
        SharedBuffer<string> *str_buffer;
        SharedBuffer<char> *char_buffer;
        atomic<bool> *game_ended;
        ifstream questions;
    public:
        Reader(SharedBuffer<string> *str_buffer, SharedBuffer<char> *char_buffer,
                string questions_address, atomic<bool> *game_ended) {
            this->questions.open(questions_address);
            this->str_buffer = str_buffer;
            this->char_buffer = char_buffer;
            this->game_ended = game_ended;
        }
        ~Reader() {
            questions.close();
        }

        void read_question() {
            string aux1;
            string aux2 = "";
            for (int i = 0; i < NUMBER_OF_ALTERNATIVES + 1; i++)  {
                getline(this->questions, aux1);
                aux2.append(aux1).append("\n");
            }
            getline(this->questions, aux1);
            aux2.append(REFUSE_TO_ANSWER).append("\n");
            this->str_buffer->write(aux2);
            this->str_buffer->allow_read();
        }

        void read_name() {
            string name;
            cin >> name;
            this->str_buffer->write(name);
            this->str_buffer->allow_read();
        }

        char read_char() {
            char ch;
            if (!(cin >> ch))
                return ' ';
            this->char_buffer->write(ch);
            this->char_buffer->allow_read();
            return ch;
        }

        void start() {
            read_name();
            while(toupper(read_char()) != 'E');
            for (int i = 1; i <= NUMBER_OF_QUESTIONS && !(*game_ended); i++) {
                read_question();
                read_char();
            }
        }
};

void start_game(Game *game) {
    game->start();
}

void start_reader(Reader *reader) {
    reader->start();
}

int main (void) {
    SharedBuffer<string> buffer_str;
    SharedBuffer<char> buffer_char;
    ifstream questions;
    atomic<bool> game_ended;
    game_ended = false;
    Game game(&buffer_str, &buffer_char, &game_ended);
    Reader reader(&buffer_str, &buffer_char, "questions.txt", &game_ended);
    thread th2(start_game, &game);
    thread th1(start_reader, &reader);
    th2.join();
    th1.join();
	return 0;
}
