BLibDir=../BasicLibrary
incl1=include
incl2=$(BLibDir)/include
src1=src
src2=$(BlibDir)/src
lib1=
lib2=$(BLibDir)/bin/Release
CC=g++
flags=-Wno-write-strings -Wno-multichar
data=curso2018-1.dat
numind=100
numepoc=1000
muttax=0.2

all: main.o BScheduler.o BScheduler

main.o: main.cpp $(incl1)/BScheduler.h $(incl1)/BSchedulerDefaults.h \
	      $(incl2)/BCommandLine.h $(incl2)/BFile.h $(incl2)/BList.h
	$(CC) $(flags) -c main.cpp -I$(incl1) -I$(incl2)  -o main.o

BScheduler.o: main.cpp $(incl1)/BScheduler.h $(incl1)/BSchedulerDefaults.h \
	      $(incl2)/BCommandLine.h $(incl2)/BFile.h $(incl2)/BList.h
	$(CC) $(flags) -I$(incl1) -I$(incl2) -c $(src1)/BScheduler.cpp -o BScheduler.o

BScheduler: BScheduler.o main.o
	$(CC) $(flags) main.o BScheduler.o  $(lib2)/BasicLibrary.lib -o BScheduler

clean:
	- rm main.o BScheduler.o BScheduler

run:
	./BScheduler -in=$(data) -population=$(numind) -taxmutation=$(muttax)
