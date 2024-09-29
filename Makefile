
CC?=gcc
CFLAGS?=-O2 -g -Wall
CFLAGS+=-Isrc 
#CFLAGS+=-Wall -Wwrite-strings -pedantic -std=gnu99
LDFLAGS+=-pthread 
LDLIBS=-lmicrohttpd 

CURLLIBS=-lcurl

STRIP=yes

ULTARI_OBJS=src/auth.o src/client_list.o src/commandline.o src/conf.o \
	src/debug.o src/fw_iptables.o src/path.o src/main.o src/http_microhttpd.o src/http_microhttpd_utils.o \
	src/ultarictl_thread.o src/safe.o src/tc.o src/util.o src/template.o \

CURL_OBJS=src/auth_curl.o src/input_validation.o

.PHONY: all clean install checkastyle fixstyle deb

all: ultari ultarictl auth_curl

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

auth_curl: $(CURL_OBJS)
	$(CC) -o auth_curl $+ $(CURLLIBS)

ultari: $(ULTARI_OBJS) $(LIBHTTPD_OBJS)
	$(CC) $(LDFLAGS) -o ultari $+ $(LDLIBS)

ultarictl: src/ultarictl.o
	$(CC) $(LDFLAGS) -o ultarictl $+ $(LDLIBS)

clean:
	rm -f ultari ultarictl auth_curl src/*.o
	rm -rf dist

install:
#ifeq(yes,$(STRIP))
	strip ultari
	strip ultarictl
#endif
	mkdir -p $(DESTDIR)/usr/bin/
	cp ultarictl $(DESTDIR)/usr/bin/
	cp ultari $(DESTDIR)/usr/bin/
	mkdir -p $(DESTDIR)/etc/ultari/htdocs/images
	cp resources/ultari.conf $(DESTDIR)/etc/ultari/
	cp resources/splash.html $(DESTDIR)/etc/ultari/htdocs/
	cp resources/splash.css $(DESTDIR)/etc/ultari/htdocs/
	cp resources/status.html $(DESTDIR)/etc/ultari/htdocs/
	cp resources/splash.jpg $(DESTDIR)/etc/ultari/htdocs/images/

checkastyle:
	@command -v astyle >/dev/null 2>&1 || \
	{ echo >&2 "We need 'astyle' but it's not installed. Aborting."; exit 1; }

checkstyle: checkastyle
	@if astyle \
		--dry-run \
		--lineend=linux \
		--suffix=none \
		--style=kr \
		--indent=force-tab \
		--formatted --recursive "src/*.c" "src/*.h" | grep -q -i formatted ; then \
			echo Please fix formatting or run fixstyle ; false ; else \
			echo Style looks ok. ; fi

fixstyle: checkastyle
	@echo "\033[1;34mChecking style ...\033[00m"
	@if astyle \
		--dry-run \
		--lineend=linux \
		--suffix=none \
		--style=kr \
		--indent=force-tab \
		--formatted --recursive "src/*.c" "src/*.h" | grep -q -i formatted ; then \
			echo "\033[1;33mPrevious files have been corrected\033[00m" ; else \
			echo "\033[0;32mAll files are ok\033[00m" ; fi

DEBVERSION=$(shell dpkg-parsechangelog | awk -F'[ -]' '/^Version/{print($$2); exit;}' )
deb: clean
	mkdir -p dist/ultari-$(DEBVERSION)
	tar --exclude dist --exclude ".git*" -cf - . | (cd dist/ultari-$(DEBVERSION) && tar xf -)
	cd dist && tar cjf ultari_$(DEBVERSION).orig.tar.bz2 ultari-$(DEBVERSION) && cd -
	cd dist/ultari-$(DEBVERSION) && dpkg-buildpackage -us -uc && cd -
	rm -rf dist/ultari-$(DEBVERSION)
