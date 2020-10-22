CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 07
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := spk-ssh.if.uj.edu.pl
SUSERNAME := 
MAIN_PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}/..

#tar zxvf JakubKosmaty_Zestaw07.tar.gz

.PHONY: all link createlib clean tar gupload supload slogin

all: msg.o createlib link klient.x serwer.x msguse.x

msguse.x: msguse.o
msguse.o: msguse.c msg.h

klient.x: klient.o
klient.o: klient.c msg.h

serwer.x: serwer.o
serwer.o: serwer.c msg.h

msg.o: msg.c msg.h

#$(CC) $(LDFLAGS) -o $@ $^ -L. -lshmem -Xlinker -rpath -Xlinker $(PWD)

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lmsg -pthread -Wl,-R $(PWD) -lrt

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

link:
	ar rv libmsg.a msg.o

createlib:
	$(CC) $(CFLAGS) -fPIC -c msg.c; $(CC) -shared -o libmsg.so msg.o

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
