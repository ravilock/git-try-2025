TRACE=true
CC=gcc

build:
	if [ "$(TRACE)" = "true" ]; then \
		$(CC) -DLEV_TRACE -o main main.c diff.c; \
	else \
		$(CC) -o main main.c diff.c; \
	fi

debug:
	$(CC) -DLEV_TRACE -g -o main main.c diff.c
