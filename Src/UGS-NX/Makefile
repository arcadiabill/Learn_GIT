#*---------------------------------------------------- UgsUpdate -----
#| Makefile: UgsUpdate
#| Author  : william h robertson
#|
#| Purpose : Build UgsUpdate & ListFiles programs
#| Note    : ListFiles will parse the subdirectory containing the
#|           UgsUpdate showing the files that need updating. This
#|           list needs to be redireted to UgsUpdate.txt and the
#|           source and destination directories for the files addedwill
#|           at the top. See UgsUpdate.c for the file's structure.
#|
#| --Ver--  ---Date---  ----By----  ---Description of the Change---
#|     0    07-20-2016      whr     Initial release
#|
#*------------------------------------------------------------------*/
CC = gcc
CFLAGS = -std=gnu11 -Wall
OBJ = ugsUpdate.o addPathSprtr.o copyFile.o doesFileExist.o\
      errorExit.o fixPaths.o getFilesize.o isAdministrator.o\
      skipComments.o trimLine.o ugsHeader.o verifyFiles.o

all: Pgm ListFiles

Pgm: $(OBJ)
	$(CC) $(CFLAGS) -o UgsUpdate $(OBJ)

ListFiles: ListFiles.o
	$(CC) $(CFLAGS) -o ListFiles ListFiles.c

$(OBJ) :

clean:
	del UgsUpdate.exe $(OBJ) ListFiles.exe ListFiles.o
