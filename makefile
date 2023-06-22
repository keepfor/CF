cc = g++
cfg = -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions -std=gnu++2a
dfg = -g -DLOCAL

prog = prog
src = sol.cc
input = input.txt
output = output.txt
resetSrc = reset.cc
copySrc = copy.cc
genSrc = gen.cc
gen = gen

define re 
	> $(input)
	cp $(resetSrc) $(src)
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
	./$(prog) <$(input)> $(output) 
	cat $(output)

clean:
	rm -rf .$(src)*
	rm -rf $(prog).*

copy:
	cp $(src) $(copySrc)

re:
	$(re)

rev: 
	$(re)
	vim $(src) ${input}

gen:
	${CC} ${genSrc} -o gen
	./${gen} > $(input)

empty:
	echo "" > $(src)
	vim $(src)
