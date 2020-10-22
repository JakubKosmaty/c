CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER  := 01

.PHONY: all clean tar upload

all: main.x kopiuj.x procesy.x lider.x

main.x: main.o procinfo.o
main.o: main.c procinfo.h

kopiuj.x: kopiuj.o
kopiuj.o: kopiuj.c

procesy.x: procesy.o procinfo.o
procesy.o: procesy.c procinfo.h

kopiuj.x: kopiuj.o
kopiuj.o: kopiuj.c

lider.x: lider.o
lider.o: lider.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	find . -name ".DS_Store" -delete; $(RM) $(wildcard *.[ox])

tar:
	cd ../; $(FIX_MACOS_FILES) tar $(TAR_FLAGS) JakubKosmaty_Zestaw$(SET_NUMBER).tar.gz Zestaw$(SET_NUMBER)

upload:
	cd ../; gdrive upload JakubKosmaty_Zestaw$(SET_NUMBER).tar.gz