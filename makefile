CC=clang++

.PHONY: reset

all: clear sol.o main copy clean
	
clear:
	clear

sol.o: sol.cc
	$(CC) -std=gnu++17 sol.cc -o sol.o

main:
	./sol.o <input.txt> output.txt
	cat output.txt

clean:
	rm -f sol.o

copy:
	cp sol.cc copy.cc

reset:
	> input.txt
	cp reset.cc sol.cc
	vim sol.cc
