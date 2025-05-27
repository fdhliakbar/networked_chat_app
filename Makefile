CC = g++
CFLAGS = -std=c++17 -I./src
LDFLAGS = -lpthread
SRC_CPP = src/main.cpp
SRC_C = src/main.c
TARGET = chat_app

all: $(TARGET)

$(TARGET): $(SRC_CPP) $(SRC_C)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_CPP) $(SRC_C) $(LDFLAGS)

clean:
	rm -f $(TARGET)