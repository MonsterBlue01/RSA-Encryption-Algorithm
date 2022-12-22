# Compile compute.cc with compute.hh

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11 -O3 -g -lgmp -lgmpxx

all: compute

compute: compute.cc compute.hh
	$(CC) $(CFLAGS) -o compute compute.cc

clean:
	rm -f compute