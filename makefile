CC := g++
obj := prog
src := sol.cc
sol_swap := .sol.*
copy_cc := copy.cc
output := out
input := in
reset_cc := reset.cc
compile_out := compile_out

define re
	echo > ${input}
	cp ${reset_cc} ${src}
endef

define cat_out
	cat ${output}
endef

gdb := -g
debug := -DDEBUG
CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g
DEBUGFLAGS := -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

.PHONY: format all reset new main

all: format main copy clean 

format:
	clang-format -style=Google -i ${src}
	
clear:
	clear

verbose:
	$(CC) ${CXXFLAGS} ${debug} ${src} -o ${obj} 2>&1 | tee ${compile_out}

simple:
	$(CC) ${debug} ${src} -o ${obj}  

${obj}: ${src}
	rm -f ${obj}*
	$(CC) ${debug} ${src} -o ${obj} 2>&1 | tee ${compile_out}

define run_in
	cat ${input}
	./${obj} < ${input} 2>&1 | tee ${output}
endef

main: ${obj}
	$(run_in)

clean:
	rm -f ${sol_swap}

copy:
	cp ${src} ${copy_cc}

re:
	$(re)

rev:
	$(re)
	vim ${src} ${input}

new:
	echo > ${input}
	cp ${reset_cc} ${src}
	vim ${src} ${input}
