CC = gcc
CFLAGS = -Wall

.PHONY: clean

OBJFLS = keys.o

%.o: %.c keys.h
	$(CC) -c $(CFLAGS) -o $@ $<

main: main.o $(OBJFLS) 
	$(CC) -o $@ $^

clean:
	rm *.o
