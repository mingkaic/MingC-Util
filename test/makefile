CC = g++
DEBUG = -g
CFLAG = -std=c++11
TESTFLAG = -lgtest
PYFLAG = -framework Python
THREADFLAG = -pthread

all:
	$(CC) $(CFLAG) $(TESTFLAG) $(PYFLAG) $(THREADFLAG) main.cpp -o test

clean:
	rm test