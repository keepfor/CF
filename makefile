cc ?= /usr/local/Cellar/gcc/14.2.0/bin/g++-14
pure_g++ ?= /usr/local/Cellar/gcc/14.2.0/bin/g++-14
cfg ?= -O3 -Wall -Werror -Wshadow  -Wc++2a-extensions  -g 
dfg ?= -DDEBUG
gdb ?= -g
std ?= -std=c++2a 
prog ?= prog
src ?= sol.cc
input ?= in
output ?= out
reset_cc ?= reset.cc
last_cc ?= last.cc
gen_cc ?= gen.cc
gen ?= gen
compile_out ?= compile_out

CXXFLAGS ?= -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal  -Wconversion -Wlong-long -Wshift-overflow -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -Wl,-stack_size,256000000 

DEBUGFLAGS ?= -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC  -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

mac_g++_no ?= -fsanitize=undefined -fsanitize=address -Wunknown-warning-option

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

all: main copy 
	
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
	$(cc) $(src) -o $(prog) $(CXXFLAGS) $(DEBUGFLAGS) $(std) $(dfg) $(gdb)  2>&1 | tee $(compile_out)

$(prog): $(src)
	rm -rf $(prog)*
	$(cc) $(src) -o $(prog) $(CXXFLAGS) $(DEBUGFLAGS) $(std) $(dfg) $(gdb)  2>&1 | tee $(compile_out)

main: $(prog)
	cat $(input)
	./$(prog) < $(input) 2>&1 | tee $(output) 

clean:
	rm -rf .$(src)*
	rm -rf $(prog)
	rm -rf $(prog).dSYM/

copy:
	cp $(src) $(last_cc)

re:
	$(re)

new: 
	$(re)
	vim $(src) $(input)

gen:
	$(CC) $(gen_cc) -o gen
	./$(gen) > $(input)

empty:
	echo "" > $(src)
	vim $(src)
