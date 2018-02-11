CC = gcc
CFLAGS = -std=c99
DEBUG = -g -Wall -Werror
SRC = $(wildcard src/*.c)
TARGET = check_tags.out

.PHONY: default all debug clean

default: $(TARGET)
all: default

$(TARGET):
	$(CC) $(CFLAGS) -s $(SRC) -o $@

debug:
	$(CC) $(CFLAGS) $(DEBUG) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
