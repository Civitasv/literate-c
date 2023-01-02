# -Wall: enable all the warnings about constructions
# -Wextra: enable some extra warning flags
# -pedantic: issue all the warnings demanded by strict ISO C
# -ggdb: produce debugging information for use by GDB
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

.PHONY: all

all: Main.pdf Main Main.c

Main.pdf: Main.tex
	pdflatex Main.tex

Main: Main.c
	$(CC) $(CFLAGS) -c Main.c

Main.c: Main.tex
	./lit Main.tex > Main.c