# CarePulse — Smart Hospital Patient & Resource Allocation System
# Run "make" to build, "make clean" to remove build output.

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lm
SRC = $(wildcard src/*.c)
TARGET = carepulse

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) beds_status.txt patient_records.txt

.PHONY: clean
