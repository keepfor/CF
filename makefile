CC=clang++

.PHONY: initialize

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
	cp sol.cc last.cc

initialize:
	cp ini.cc sol.cc
