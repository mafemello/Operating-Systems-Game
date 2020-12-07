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
#include <functional>
#include <time.h>
using namespace std;

// global variables 
string name;
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
}

#include <semaphore.h>

typedef struct {
    string buffer;
    sem_t can_read;
    sem_t can_write;
} SharedBuffer;

void display_home(SharedBuffer *buffer) {
    system("tput reset");
    cout << "Welcome to the game 'Who Wants to be a Bilionaire?'.\n"
        "Are you ready? Tell us your name:\nWelcome to the game "
        "'Who Wants to be a Bilionaire?'. \nAre you ready? "
        "Tell us your name:" << endl;
    sem_post(&buffer->can_write);
}

void display_greetings(SharedBuffer *buffer) {
    system("tput reset");
    sem_wait(&buffer->can_read);
	cout << "\nHi, " << name << ", let's start with the rules:"
        "You have 30 seconds to answer each question. You type "
        "the answer (e.g.: 'b'), and the timer stops.\n"
        "If the timer ends, you lose it all.\n"
        "\nPress 'E' to start." << endl;
    sem_post(&buffer->can_write);
}

void display_question(SharedBuffer *buffer) {
    system("tput reset");
    sem_wait(&buffer->can_read);
}



int main (void) {
	// testing the timer
	Timer tHello;
    tHello.start(chrono::milliseconds(1000), []{
        cout << "Hello!" << endl;
    });

    this_thread::sleep_for(chrono::seconds(2));
    tHello.stop();

    string interface = "Welcome to the game 'Who Wants to be a Bilionaire?'. "
        "\nAre you ready? Tell us your name:\n";
	
	cout << "Welcome to the game 'Who Wants to be a Bilionaire?'. \nAre you ready? Tell us your name:\n";
	cin >> name;
	cout << "\nHi, " << name << ", let's start with the rules:" << endl;
	cout << "You have 30 seconds to answer each question. You type the answer (e.g.: 'b'), and the timer stops." << endl;
	cout << "If the timer ends, you lose it all.\n";
	cout << "\nPress 'E' to start." << endl;

	char enter;
	while (cin >> enter) {
		if (enter == 'e' || enter == 'E'){
			GameLoop ();
			break;
		}
		else cout << "Please, try again. Press 'E' to start." << endl;
	}


	return 0;
}
