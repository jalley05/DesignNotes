CC=g++
CFLAGS=-I.
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

neuralNet: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) neuralNet
