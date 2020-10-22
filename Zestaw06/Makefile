CC := gcc
CFLAGS := -std=c99 -O3 -Wall
LDFLAGS := -std=c99 -s -lm
TAR_FLAGS := zcvf
TAR_EXT := tar.gz
FIX_MACOS_FILES := COPYFILE_DISABLE=1
SET_NUMBER := 06
FILE_NAME := JakubKosmaty_Zestaw$(SET_NUMBER)
HOST := spk-ssh.if.uj.edu.pl
SUSERNAME := 
MAIN_PATH := /home/$(SUSERNAME)/systemy
DIR := ${CURDIR}/..

#tar zxvf JakubKosmaty_Zestaw06.tar.gz

.PHONY: all link createlib clean tar gupload supload slogin

all: sem.o createlib link shmuse1.x shmuse2.x producent.x glowny.x konsument.x

glowny.x: glowny.o
glowny.o: glowny.c shmem.h sem.h

producent.x: producent.o
producent.o: producent.c shmem.h sem.h

konsument.x: konsument.o
konsument.o: konsument.c shmem.h sem.h

sem.o: sem.c sem.h

shmuse1.x: shmuse.o
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lshmem -Wl,-R $(PWD) -lrt

#$(CC) $(LDFLAGS) -o $@ $^ -L. -lshmem -Xlinker -rpath -Xlinker $(PWD)

shmuse2.x: shmuse.o
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lshmem -lrt

shmuse.o: shmuse.c shmem.h

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ -L. -lshmem -pthread -lsem -Wl,-R $(PWD) -lrt

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

link:
	ar rv libsem.a sem.o

createlib:
	$(CC) $(CFLAGS) -fPIC -c shmem.c; $(CC) -shared -o libshmem.so shmem.o

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
