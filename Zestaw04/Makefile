CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 04
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := spk-ssh.if.uj.edu.pl
SUSERNAME := 
MAIN_PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}/..

.PHONY: all clean tar gupload supload slogin

all: prodkons.x konsument.x producent.x fifo.x

prodkons.x: prodkons.o
prodkons.o: prodkons.c

konsument.x: konsument.o
konsument.o: konsument.c

producent.x: producent.o
producent.o: producent.c

fifo.x: fifo.o
fifo.o: fifo.c

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
	cd ../; scp $(DIR)/$(FILE_NAME).$(TAR_EXT) $(SUSERNAME)@$(HOST):$(MAIN_PATH)

slogin:
	ssh $(SUSERNAME)@$(HOST)
