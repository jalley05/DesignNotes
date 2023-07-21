CC=g++
CXXFLAGS = -std=c++11
CFLAGS=-I -ftree-vectorize -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

.PHONY: clean

all: main-build

main-build: program

program: $(obj)
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS)
	rm -f $(obj)

clean:
	rm -f $(obj) program

