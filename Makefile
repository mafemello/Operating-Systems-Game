COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror -Wall -ggdb3 -fsanitize=undefined -pthread

all: bin bin/utils.o bin/timer.o bin/questions.o\
	bin/display_context.o bin/pages_manager.o bin/display.o\
	bin/game_context.o bin/controllers.o bin/starting_controller.o\
	bin/introduction_controller.o bin/question_controller.o\
	bin/results_controller.o bin/engine.o bin/main.o
	$(COMPILER) $(COMPILATION_FLAGS) -o operating_systems_game \
		bin/utils.o bin/timer.o bin/questions.o\
		bin/display_context.o bin/pages_manager.o bin/display.o\
		bin/game_context.o bin/controllers.o bin/starting_controller.o\
		bin/introduction_controller.o bin/question_controller.o\
		bin/results_controller.o bin/engine.o bin/main.o

bin:
	mkdir bin

bin/utils.o: src/utils.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/utils.o src/utils.cpp

bin/timer.o: src/timer.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/timer.o src/timer.cpp

bin/questions.o: src/questions.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/questions.o src/questions.cpp

bin/display_context.o: src/display/display_context.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display_context.o\
		src/display/display_context.cpp

bin/pages_manager.o: src/display/pages_manager.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/pages_manager.o\
		src/display/pages_manager.cpp

bin/display.o: src/display/display.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display.o src/display/display.cpp

bin/game_context.o: src/control/game_context.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/game_context.o\
		src/control/game_context.cpp
	
bin/controllers.o: src/control/controllers.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/controllers.o\
		src/control/controllers.cpp

bin/starting_controller.o: src/control/starting_controller.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/starting_controller.o\
		src/control/starting_controller.cpp

bin/introduction_controller.o: src/control/introduction_controller.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/introduction_controller.o\
		src/control/introduction_controller.cpp

bin/question_controller.o: src/control/question_controller.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/question_controller.o\
		src/control/question_controller.cpp

bin/results_controller.o: src/control/results_controller.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/results_controller.o\
		src/control/results_controller.cpp

bin/engine.o: src/control/engine.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/engine.o src/control/engine.cpp

bin/main.o: src/main.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

zip:
	rm -rf operating_systems_game bin *.zip
	zip -r OperatingSystemsGame.zip include/ src/ Makefile questions.txt

run:
	./operating_systems_game

clean:
	rm -rf operating_systems_game bin *.zip
