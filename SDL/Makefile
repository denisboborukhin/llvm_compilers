CC 		= clang
CFLAGS 	?= -lSDL2
 
all: 
	$(CC) $(CFLAGS) start.c sim.c app.c
	
gen_app_ir:
	$(CC) app.c -S -emit-llvm -o app.ll -O2
	
run: all
	./a.out

clean:
	rm a.out app.ll