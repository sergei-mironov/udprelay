PREFIX=/usr/local

.PHONY: all install clean
all: udprelay

udprelay: udprelay.c
	gcc -lpthread $< -o $@

install: udprelay
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install $< $(DESTDIR)$(PREFIX)/bin/udprelay

clean:
	-rm udprelay

