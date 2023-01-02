# -Wall: enable all the warnings about constructions
# -Wextra: enable some extra warning flags
# -pedantic: issue all the warnings demanded by strict ISO C
# -ggdb: produce debugging information for use by GDB
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

lit: run.c
	$(CC) $(CFLAGS) -o ./test/lit run.c

