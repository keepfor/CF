CC=g++

define re 
	> input.txt
	cp reset.cc sol.cc
endef

.PHONY: reset gen reset revim empty

all: sol.exe main copy clean
	
clear:
	clear
	rm -rf sol.exe*
	rm -rf .sol.cc*

sol.exe: sol.cc
	$(CC) -DLOCAL -g -O3 -Wall -Werror -Wshadow  -Wc++17-extensions -std=gnu++2a  sol.cc -o sol.exe

main:
	./sol.exe <input.txt> output.txt 
	cat output.txt

clean:
	rm -rf sol.exe*
	rm -rf .sol.cc*

copy:
	cp sol.cc copy.cc

re:
	$(re)

rev: 
	$(re)
	vim sol.cc

gen:
	${CC} gen.cc -o gen
	./gen > input.txt

empty:
	echo "" > sol.cc
	vim sol.cc
