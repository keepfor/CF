cc = g++
cfg = -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions -std=gnu++2a
dfg = -g -DLOCAL

prog = obj
src = sol.cc
input = input.txt
output = output.txt

define re 
	> $(input)
	cp reset.cc $(src)
endef

.PHONY: reset gen reset revim empty

all: $(prog) main copy clean
	
clear:
	clear
	rm -rf $(prog)*
	rm -rf .$(src)*

$(prog): $(src)
	$(cc) $(dfg) $(cfg) $(src) -o $(prog)

main:
	./$(prog) <$(input)> output.txt 
	cat output.txt

clean:
	rm -rf .$(src)*
	rm -rf $(prog).*

copy:
	cp $(src) copy.cc

re:
	$(re)

rev: 
	$(re)
	vim $(src)

gen:
	${CC} gen.cc -o gen
	./gen > $(input)

empty:
	echo "" > $(src)
	vim $(src)
