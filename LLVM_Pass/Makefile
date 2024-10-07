CXX = clang++
CFLAGS ?= -lSDL2

SRC = ./src/
APP_SRC = ../SDL/src/app.c

all: 
	$(CXX) $(CFLAGS) start.c sim.c app.c
	
log_pass: 
	$(CXX) $(SRC)log.cpp -fPIC -shared -I$$(llvm-config --includedir) -o log_pass.so
	
run_pass: log_pass
	clang -fpass-plugin=./log_pass.so $(APP_SRC) ../SDL/src/sim.c -I$$(../SDL/src/)

clean:
	rm a.out app.ll