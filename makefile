CC := g++
obj := prog
src := sol.cc
dotSwap := .sol.*
copySrc := copy.cc
output := output.txt
input := input.txt
resetSrc := reset.cc

define re
	echo > ${input}
	cp ${resetSrc} ${src}
endef

debug := "-DDEBUG"
CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g
DEBUGFLAGS := -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

.PHONY: format all reset new main

all: format main copy clean 

format:
	clang-format -style=Google -i ${src}
	
clear:
	clear

verbose:
	$(CC) ${CXXFLAGS} ${debug} ${src} -o ${obj}  

simple:
	$(CC) ${debug} ${src} -o ${obj}  

${obj}: ${src}
	$(CC) ${debug} ${src} -o ${obj} 2>&1 | tee ${output} 

main: ${obj}
	./${obj} < ${input} 2>&1 | tee ${output} 

clean:
	rm -f ${dotSwap}

copy:
	cp ${src} ${copySrc}

re:
	$(re)

rev:
	$(re)
	vim ${src} ${input}

new:
	echo > ${input}
	cp ${resetSrc} ${src}
	vim ${src} ${input}
