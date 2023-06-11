CC = clang
CFLAGS = -Wall -Wextra -lcs50

SRC_FILES := $(wildcard *.c)
EXECUTABLES := $(SRC_FILES:.c=)

.PHONY: all clean

all: $(EXECUTABLES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)
