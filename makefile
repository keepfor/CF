CC := g++
prog := prog
src := sol.cc
sol_swap := .sol.*
copy_cc := copy.cc
output := out
input := in
reset_cc := reset.cc
compile_out := compile_out

o2 := -O2
gdb := -g
debug := -DDEBUG
CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -Wl,-z,stack-size=256000000

DEBUGFLAGS := -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

define re
	echo > $(input)
	cp $(reset_cc) $(src)
endef

define cat_out
	cat $(output)
endef

define run_in
	cat $(input)
	./$(prog) < $(input) 2>&1 | tee $(output)
endef

all: main copy  

format:
	clang-format -style=Google -i $(src)
	
verbose:
	$(CC) $(CXXFLAGS) $(DEBUGFLAGS) $(debug) $(src) -o $(prog) 2>&1 | tee $(compile_out)

simple:
	$(CC) $(debug) $(src) -o $(prog)  

$(prog): $(src)
	rm -f $(prog)
	$(CC) $(src) $(CXXFLAGS) $(debug) $(gdb) $(DEBUGFLAGS) -o $(prog) 2>&1 | tee $(compile_out)

main: $(prog)
	$(run_in)

clean:
	rm -f $(sol_swap)
	rm -f $(prog)

copy:
	cp $(src) $(copy_cc)

re:
	$(re)

rev:
	$(re)
	vim $(src) $(input)

new:
	echo > $(input)
	cp $(reset_cc) $(src)
	vim $(src) $(input)

.PHONY: format all reset new main
