
cc = gcc
flags = -Wfatal-errors -Wall -Werror -Wpedantic -Wextra -std=c89

test: test.o user.o
	$(cc) -o test test.o user.o $(flags)

test.o: test.c user.h
	$(cc) -c test.c $(flags)

user.o: user.c
	$(cc) -c user.c $(flags)

clean:
	rm test *.o
