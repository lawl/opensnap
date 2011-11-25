all:
	g++ -o opensnap -lX11 -lXrandr opensnap.c
clean:
	rm opensnap
