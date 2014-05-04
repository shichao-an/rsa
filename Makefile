CC = gcc
CFLAGS = -Wall -g

.PHONY: clean

OBJFLS = keys.o certificate.o trace.o

%.o: %.c keys.h certificate.h trace.h
	$(CC) -c $(CFLAGS) -o $@ $<

main: main.o $(OBJFLS) 
	$(CC) -o $@ $^

clean:
	rm *.o
