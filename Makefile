CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11 -O3 -g
LDFLAGS = -lm -lgmpxx -lgmp

all: main

main: main.o functions.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cc functions.hh
	$(CC) $(CFLAGS) -c $<

functions.o: functions.cc functions.hh
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main