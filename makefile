#CC=clang++
#CC=gcc
CC=g++

debug="-DLOCAL"
CXXFLAGS ?= -std=c++2a -O2 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

.PHONY: reset new

exe="sol.exe"
src="sol.cc"
all: ${exe} main copy clean 
	
clear:
	clear

${exe}: sol.cc
	$(CC) ${CXXFLAGS} ${debug} ${src} -o ${exe} -DDEBUG -g 

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

new:
	echo > input.txt
	cp reset.cc sol.cc
