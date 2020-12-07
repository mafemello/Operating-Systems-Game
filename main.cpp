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

#include <time.h>

#define NUMBER_OF_QUESTIONS 15
#define NUMBER_OF_ALTERNATIVES 4
#define REFUSE_TO_ANSWER "E - Não responder"

using namespace std;

const int PRIZES[4] = {0, 75000, 250000, 1000000};


// global variables 
/*string name;
FILE *quest;

// thread timer class 
class Timer {

	thread th;
    bool running = false;

public:
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    void start(const Interval &interval, const Timeout &timeout) {
        running = true;

        th = thread([=]() {
            while (running == true) {
                this_thread::sleep_for(interval);
                timeout();
            }
        });
    }
    void stop() {
        running = false;
        th.join();
    }
};

void start_timer(int interval) {
    int offset = cout.tellp();
    
    for (int i = 0; i < interval; i++) {
        cout << "Time remaingin: " << i << " seconds";
    }
}

// void function to open the questions file txt
void openQuestions () {
	quest = fopen ("questions.txt", "r");
	if (quest == NULL) {
		cout << "Looks like we have a problem with the questions file... I'm sorry, " << name << " :(";
		return;
	}	
	return;
}

// main function 
void GameLoop () {

	openQuestions (); // loading questions

	srand(time(0)); 
	int random = rand() % 20 + 1; // generating random number to pick random questions
	char* result;
	char line [100];

	int i = 1;
	while (!feof (quest)) {
		result = fgets (line, 100, quest);
		if (result) {
			if (i == random) cout << "Question" << line << endl;
			i++;
		}
	}
}*/

typedef struct {
    string buffer;
    sem_t can_read;
    sem_t can_write;
} SharedBufferString;

typedef struct {
    int buffer;
    sem_t can_read;
    sem_t can_write;
} SharedBufferInt;

void display_home(SharedBufferString *buffer) {
    system("tput reset");
    cout << "Welcome to the game 'Who Wants to be a Bilionaire?'.\n"
        "Are you ready? Tell us your name:" << endl;
    sem_post(&buffer->can_write);
}

void display_greetings(SharedBufferString *buffer) {
    sem_wait(&buffer->can_read);
    system("tput reset");
	cout << "\nHi, " << buffer->buffer << ", let's start with the rules:"
        "You have 30 seconds to answer each question. You type "
        "the answer (e.g.: 'b'), and the timer stops.\n"
        "If the timer ends, you lose it all.\n"
        "\nPress 'E' to start." << endl;
    sem_post(&buffer->can_write);
}

/*void display_timer(int limit) {

}*/

void display_question(SharedBufferString *buffer, bool save_point_reached, int prize) {
    sem_post(&buffer->can_write);
    sem_wait(&buffer->can_read);
    system("tput reset");
    if (save_point_reached)
        cout << "Congratulations. You have won $" << prize << "\n";
    cout << buffer->buffer << "\n";
    /*thread(display_timer, 30);*/
}

void display_results(int prize) {
    cout << "The game has finished. You won " << prize << "\n";
}

void read_question(SharedBufferString *buffer, ifstream &questions) {
    sem_wait(&buffer->can_write);
    string aux;
    buffer->buffer.clear();
    for (int i = 0; i < NUMBER_OF_ALTERNATIVES + 1; i++)  {
        getline(questions, aux);
        buffer->buffer.append(aux);
        buffer->buffer.append("\n");
    }
    getline(questions, aux);
    buffer->buffer.append(REFUSE_TO_ANSWER);
    buffer->buffer.append("\n");
    sem_post(&buffer->can_read);
}

void read_name(SharedBufferString *buffer) {
    sem_wait(&buffer->can_write);
    cin >> buffer->buffer;
    sem_post(&buffer->can_read);
}

void read_enter(SharedBufferString *buffer) {
    sem_wait(&buffer->can_write);
    cin >> buffer->buffer;
    sem_post(&buffer->can_read);
}

void display_thread(SharedBufferString *buffer_str) {
    display_home(buffer_str);
    display_greetings(buffer_str);
    int i;
    for (i = 1; i <= NUMBER_OF_QUESTIONS; i++) {
        display_question(buffer_str, i % 5 == 0, PRIZES[i / 5]);
    }
    display_results(PRIZES[i / 5]);
}

void read_thread(SharedBufferString *buffer_str, ifstream &questions) {
    read_name(buffer_str);
    read_enter(buffer_str);
    for (int i = 1; i <= NUMBER_OF_QUESTIONS; i++)
        read_question(buffer_str, questions);
}

int main (void) {
    SharedBufferString buffer_str;
    buffer_str.buffer = "";
    sem_init(&buffer_str.can_read, 0, 0);
    sem_init(&buffer_str.can_write, 0, 0);
    ifstream questions;
    questions.open("questions.txt");
    thread th2(display_thread, &buffer_str);
    thread th1(read_thread, &buffer_str, ref(questions));
    th2.join();
    th1.join();
	return 0;
}
