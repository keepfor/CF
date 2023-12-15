cc := g++ -std=gnu++2a
cfg := -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions  -g 
dfg := -DDEBUG

prog := prog
src := sol.cc
input := input.txt
output := output.txt
resetSrc := reset.cc
copySrc := copy.cc
genSrc := gen.cc
gen := gen

define re 
	> $(input)
	cp $(resetSrc) $(src)
endef

.PHONY: reset gen reset revim empty

all: format main copy clean
	
format:
	clang-format -style=Google -i $(src)

clear:
	clear
	rm -rf $(prog)*
	rm -rf .$(src)*

simple:
	$(cc) $(dfg) $(src) -o $(prog)

verbose:
	$(cc) $(dfg) $(cfg) $(src) -o $(prog)

$(prog): $(src)
	$(cc) $(dfg) $(src) -o $(prog) 2>&1 | tee $(output)

main: $(prog)
	./$(prog) < $(input) 2>&1 | tee $(output) 

clean:
	rm -rf .$(src)*

copy:
	cp $(src) $(copySrc)

re:
	$(re)

new: 
	$(re)
	vim $(src) ${input}

gen:
	${CC} ${genSrc} -o gen
	./${gen} > $(input)

empty:
	echo "" > $(src)
	vim $(src)
