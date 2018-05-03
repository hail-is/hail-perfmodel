CXX      ?= /usr/bin/c++
CXXFLAGS := -std=c++11 -fno-strict-aliasing -Wall -Werror -O2

.PHONY: all clean

all: alloc

clean:
	-rm -f *.o alloc

alloc: alloc.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<
