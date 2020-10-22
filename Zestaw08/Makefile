CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 08
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := spk-ssh.if.uj.edu.pl
SUSERNAME := 
MAIN_PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}/..

#tar zxvf JakubKosmaty_Zestaw08.tar.gz

.PHONY: all link createlib clean tar gupload supload slogin

all: wykluczanie.x 

wykluczanie.x: wykluczanie.o
wykluczanie.o: wykluczanie.c 

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ -lpthread -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	find . -name ".DS_Store" -delete; $(RM) *.o *.x *.so *.a

tar:
	cd ../; $(FIX_MACOS_FILES) tar $(TAR_FLAGS) $(FILE_NAME).$(TAR_EXT) Zestaw$(SET_NUMBER)

gupload:
	cd ../; gdrive upload $(FILE_NAME).$(TAR_EXT)

supload:
	cd ../; scp $(DIR)/$(FILE_NAME).$(TAR_EXT) $(SUSERNAME)@$(HOST):$(MAIN_PATH)

slogin:
	ssh $(SUSERNAME)@$(HOST)
