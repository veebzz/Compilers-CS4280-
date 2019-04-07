#Vibhav Chemarla
#CS4280 PA 1
#03/06/19

CC = g++
 CFLAGS = -std=c++11
 TARGET = scanner
 OBJS = main.o scanner.o testScanner.o
 $(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp scanner.h testScanner.h token.h
	$(CC) $(CFLAGS) -c main.cpp
scanner.o: scanner.cpp
	$(CC) $(CFLAGS) -c scanner.cpp
testScanner.o: testScanner.cpp
	$(CC) $(CFLAGS) -c testScanner.cpp

clean:
	/bin/rm -f *.o keyboardinput.txt $(TARGET)
