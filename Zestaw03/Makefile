CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 03
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := 
SUSERNAME := 
PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}

.PHONY: all clean tar gupload supload slogin

all: obsluga.x wysylaj.x grupa.x
 
obsluga.x: obsluga.o procinfo.o
obsluga.o: obsluga.c procinfo.h

wysylaj.x: wysylaj.o
wysylaj.o: wysylaj.c

grupa.x: grupa.o
grupa.o: grupa.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	find . -name ".DS_Store" -delete; $(RM) $(wildcard *.[ox])

tar:
	cd ../; $(FIX_MACOS_FILES) tar $(TAR_FLAGS) $(FILE_NAME).$(TAR_EXT) Zestaw$(SET_NUMBER)

gupload:
	cd ../; gdrive upload $(FILE_NAME).$(TAR_EXT)

supload:
	cd ../; scp $(DIR)/$(FILE_NAME).$(TAR_EXT) $(SUSERNAME)@$(HOST):$(PATH)

slogin:
	ssh $(SUSERNAME)@$(HOST)
