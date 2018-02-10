CC = gcc
CFLAGS = -std=c99
SRC = $(wildcard src/*.c)
TARGET = check_tags.out

.PHONY: default all debug clean

default: $(TARGET)
all: default

$(TARGET):
	$(CC) $(CFLAGS) -s $(SRC) -o $@

debug:
	$(CC) $(CFLAGS) -g $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
