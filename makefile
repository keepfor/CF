CC=clang++

.PHONY: clean

all: clear sol.o main clean
	
clear:
	clear

sol.o: sol.cc
	$(CC) -std=gnu++17 sol.cc -o sol.o

main:
	./sol.o <input.txt> output.txt
	cat output.txt

clean:
	rm -f sol.o
