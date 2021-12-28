CC=g++
CXXFLAGS = -std=c++11 -I/usr/local/opt/curl/include
LDFLAGS = -L/usr/local/opt/curl/lib
LDLIBS = -lcurl

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

.PHONY: clean

all: main-build

main-build: program

program: $(obj)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LDLIBS)
	rm -f $(obj)

clean:
	rm -f $(obj) program

