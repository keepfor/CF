cc := g++
cfg := -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions  -g 
dfg := -DDEBUG

gdb := -g
debug := -DDEBUG

std ?= -std=c++2a

CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlong-long -Wshift-overflow -Wunknown-warning-option -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g -Wl,-stack_size,256000000

DEBUGFLAGS := -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

prog := prog
src := sol.cc
input := in
output := out
reset_cc := reset.cc
copy_cc := copy.cc
gen_cc := gen.cc
gen := gen
compile_out := compile_out

define re 
	> $(input)
	cp $(reset_cc) $(src)
endef

define cat_out
	cat $(output)
endef

define format_func
	clang-format -style=Google -i $(src)
endef

.PHONY: reset gen reset revim empty

all: main copy clean
	
format:
	clang-format -style=Google -i $(src)

clear:
	clear
	rm -rf $(prog)
	rm -rf .$(src)
	rm -rf $(prog).dSYM/

simple:
	$(cc) $(src) -o $(prog) $(std) $(dfg)  

verbose:
	$(cc) $(src) -o $(prog) ${CXXFLAGS} $(DEBUGFLAGS) $(gdb) $(dfg) 2>&1 | tee $(compile_out)

$(prog): $(src)
	rm -rf $(prog)*
	$(cc) $(src) -o $(prog) $(std) $(dfg) 2>&1 | tee $(compile_out) 
	
main: $(prog)
	cat $(input)
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
