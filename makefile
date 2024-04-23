cc := g++ -std=gnu++2a
cfg := -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions  -g 
dfg := -DDEBUG

gdb := -g
debug := -DDEBUG
CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g
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
	rm -rf $(prog)*
	rm -rf .$(src)*

simple:
	$(cc) $(dfg) $(src) -o $(prog)

verbose:
	$(cc) $(dfg) $(cfg) $(src) -o $(prog)

$(prog): $(src)
	rm -rf $(prog)
	$(cc) $(dfg) $(src) -g -o $(prog) 2>&1 | tee $(compile_out)

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
