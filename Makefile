CC = gcc
CFLAGS = -Wall -g

.PHONY: clean

OBJFLS = keys.o certificate.o

%.o: %.c keys.h certificate.h
	$(CC) -c $(CFLAGS) -o $@ $<

main: main.o $(OBJFLS) 
	$(CC) -o $@ $^

clean:
	rm *.o
