
cc = gcc
flags = -Wfatal-errors -Wall -Werror -Wpedantic -Wextra -std=c89
objects = src/test.o src/user.o
target = test

$(target): $(objects)
	$(cc) -o $(target) $(objects) $(flags)

clean:
	rm -rf test $(objects) users/*
	touch users/placeholder
