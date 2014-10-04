all:
	mkdir -p bin
	g++ -Wall -o bin/opensnap src/opensnap.c -lX11 `pkg-config gtk+-3.0 --cflags` `pkg-config gtk+-3.0 --libs`
install: 
	install bin/opensnap /usr/bin/
clean:
	rm bin/opensnap
