CC=gcc

build:
	$(CC) -o main main.c diff.c

debug:
	$(CC) -DLEV_TRACE -g -o main main.c diff.c
