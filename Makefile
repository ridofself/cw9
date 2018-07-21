
cc = gcc
flags = -Wfatal-errors -Wall -Werror -Wpedantic -Wextra -std=c89
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)

target = test

$(target): $(objects)
	$(cc) $(objects) -o $(target)

%.o: %.c
	$(cc) -c $(flags) $< -o $@

clean:
	rm -rf $(target) $(objects) users/*
	touch users/placeholder
