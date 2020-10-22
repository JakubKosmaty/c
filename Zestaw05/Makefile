CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 05
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := spk-ssh.if.uj.edu.pl
SUSERNAME := 
MAIN_PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}/..

.PHONY: all link clean tar gupload supload slogin

all: sem.o link semuse.x powielacz.x prog.x

sem.o: sem.c sem.h

semuse.x: semuse.o
semuse.o: semuse.c sem.h

powielacz.x: powielacz.o
powielacz.o: powielacz.c sem.h

prog.x: prog.o
prog.o: prog.c sem.h

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lsem -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

link:
	ar rv libsem.a sem.o

clean:
	find . -name ".DS_Store" -delete; $(RM) *.o *.x *.a

tar:
	cd ../; $(FIX_MACOS_FILES) tar $(TAR_FLAGS) $(FILE_NAME).$(TAR_EXT) Zestaw$(SET_NUMBER)

gupload:
	cd ../; gdrive upload $(FILE_NAME).$(TAR_EXT)

supload:
	cd ../; scp $(DIR)/$(FILE_NAME).$(TAR_EXT) $(SUSERNAME)@$(HOST):$(MAIN_PATH)

slogin:
	ssh $(SUSERNAME)@$(HOST)
