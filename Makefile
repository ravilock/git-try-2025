CC=gcc

build:
	$(CC) -o main -Wall main.c diff.c

debug:
	$(CC) -DLEV_TRACE -g -o main -Wall  main.c diff.c
