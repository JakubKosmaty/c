CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER  := 02

.PHONY: all clean tar upload

all: drzewko1.x drzewko2.x potomny.x macierzysty.x zombi.x orphan.x execute.x

drzewko1.x: drzewko1.o
drzewko1.o: drzewko1.c

drzewko2.x: drzewko2.o
drzewko2.o: drzewko2.c

macierzysty.x: macierzysty.o procinfo.o
macierzysty.o: macierzysty.c procinfo.h

potomny.x: potomny.o procinfo.o
potomny.o: potomny.c procinfo.h

orphan.x: orphan.o
orphan.x: orphan.o

zombi.x: zombi.o
zombi.o: zombi.c

execute.x: execute.o
execute.o: execute.c

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