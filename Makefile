CC = gcc
CFLAGS = -Wall -g

prog1: prog1.c
	$(CC) $(CFLAGS) -o prog1 prog1.c

prog5: prog5.c
	$(CC) $(CFLAGS) -o prog5 prog5.c

lsgrep: lsgrep.c
	$(CC) $(CFLAGS) -o lsgrep lsgrep.c

clean:
	rm -f prog1 prog5 lsgrep
