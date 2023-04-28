CC=g++
obj=objSolCc
src=sol.cc
dotSwap=.sol.*
copySrc=copy.cc
output=output.txt
input=input.txt
resetCc=reset.cc

define re
	echo > ${input}
	cp ${resetSrc} ${src}
endef

debug="-DLOCAL"
CXXFLAGS ?= -std=c++2a -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion -g
DEBUGFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -D_FORTIFY_SOURCE=2

.PHONY: reset new

all: ${obj} main copy clean 
	
clear:
	clear

${obj}: ${src}
	$(CC) ${CXXFLAGS} ${debug} ${src} -o ${obj} -DDEBUG -g 

main:
	./${obj} <${input}> ${output}
	cat ${output}

clean:
	rm -f ${dotSwap}

copy:
	cp ${src} ${copySrc}

re:
	$(re)

rev:
	$(re)
	vim ${src}

new:
	echo > ${input}
	cp ${resetSrc} ${src}
