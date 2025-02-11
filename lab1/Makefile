CC = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS = -lgtest -lpthread

TARGET = string_test

all: $(TARGET)

$(TARGET): String.o String.test.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

String.o: String.cpp String.hpp
	$(CC) $(CXXFLAGS) -c $<

String.test.o: String.test.cpp String.hpp
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

format:
	clang-format -i String.cpp String.hpp String.test.cpp