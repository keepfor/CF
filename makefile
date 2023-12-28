cc := g++ -std=gnu++2a
cfg := -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions  -g 
dfg := -DDEBUG

prog := prog
src := sol.cc
input := in
output := out
reset_cc := reset.cc
copy_cc := copy.cc
gen_cc := gen.cc
gen := gen

define re 
	> $(input)
	cp $(reset_cc) $(src)
endef

define cat_out
	cat $(output)
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
	rm -rf $(prog)
	$(cc) $(dfg) $(src) -o $(prog) 2>&1 | tee $(output)

main: $(prog)
	./$(prog) < $(input) 2>&1 | tee $(output) 

clean:
	rm -rf .$(src)*

copy:
	cp $(src) $(copy_cc)

re:
	$(re)

new: 
	$(re)
	vim $(src) ${input}

gen:
	${CC} ${gen_cc} -o gen
	./${gen} > $(input)

empty:
	echo "" > $(src)
	vim $(src)
