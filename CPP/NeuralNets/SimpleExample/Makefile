CC=g++
CFLAGS=-I.
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

neuralNet: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)
	rm -f $(obj)

.PHONY: clean
clean:
	rm -f $(obj) neuralNet
