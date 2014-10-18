all:
	mkdir -p bin
	$(CC) -std=c99 -Wall -o bin/opensnap src/opensnap.c -lX11 `pkg-config gtk+-3.0 --cflags` `pkg-config gtk+-3.0 --libs`
clean:
	rm bin/opensnap
