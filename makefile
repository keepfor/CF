#CC=clang++
CC=g++
#CC=gcc

.PHONY: reset

all: sol.exe main copy clean 
	
clear:
	clear

sol.exe: sol.cc
	$(CC) -Wall -DLOCAL -std=gnu++17  sol.cc -o sol.exe -DDEBUG -g 

main:
	./sol.exe <input.txt> output.txt 
	cat output.txt
clean:
	rm -f sol.exe

copy:
	cp sol.cc copy.cc

reset:
	echo > input.txt
	cp reset.cc sol.cc
	vim sol.cc
