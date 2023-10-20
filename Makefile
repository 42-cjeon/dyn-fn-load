.PHONY : all
all : main

.PHONY : clean
clean :
	rm -f lib.o main mul1 mul2 mul3

mul1 mul2 mul3 : lib.o
	objcopy --dump-section .text.$@=$@ $<

lib.o : lib.c
	gcc -ffunction-sections -c $<

main : main.c mul1 mul2 mul3
	gcc -o $@ $<
