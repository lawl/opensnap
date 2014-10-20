all:
	mkdir -p bin
	$(CC) -std=c99 -Wall -o bin/opensnap src/opensnap.c -lX11 `pkg-config gtk+-3.0 --cflags` `pkg-config gtk+-3.0 --libs`
install:
	install bin/opensnap /usr/bin/
	install -dm0755 /etc/opensnap
	for file in `ls sample_configs/` ; do \
		install -m0644 "sample_configs/$$file" "/etc/opensnap/$$file" ; \
	done
uninstall:
	rm -ri /etc/opensnap/
	rm -i /usr/bin/opensnap
clean:
	rm bin/opensnap
