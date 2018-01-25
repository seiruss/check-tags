CC = gcc
CFLAGS = -std=c99

TARGET = check_tags
SRC = $(wildcard src/*.c)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
