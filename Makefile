# CarePulse build file
# just type "make" to compile, "make clean" to wipe the binary

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c
TARGET = carepulse

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: clean
