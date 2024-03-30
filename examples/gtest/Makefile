CC=g++
CFLAGS=-pedantic-errors -std=c++20
LDFLAGS=-lgtest -lgtest_main
SOURCES=test.cpp version.cpp
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE):
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf *.o $(EXECUTABLE)