COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror -Wall -ggdb3 -fsanitize=undefined -pthread

all: bin bin/timer.o bin/questions.o bin/display.o bin/utils.o\
	bin/control.o bin/game_state.o bin/main.o
	$(COMPILER) $(COMPILATION_FLAGS) -o program \
		bin/timer.o bin/game_state.o bin/questions.o bin/utils.o\
		bin/display.o bin/control.o bin/main.o

bin:
	mkdir bin

bin/timer.o: src/timer.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/timer.o src/timer.cpp

bin/questions.o: src/questions.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/questions.o src/questions.cpp

bin/display.o: src/display.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display.o src/display.cpp

bin/utils.o: src/utils.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/utils.o src/utils.cpp

bin/control.o: src/control.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/control.o src/control.cpp

bin/game_state.o: src/game_state.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/game_state.o src/game_state.cpp


bin/main.o: src/main.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

zip:
	rm -rf programaTrab bin *.bin *.zip
	zip -r Trabalho1.zip include/ src/ Makefile

run:
	./program

clean:
	rm -rf programa bin *.bin *.zip erros.txt
