CFLAGS = -Wall -Wextra -O3 -std=c17 -pedantic
LDFLAGS = -lm

.PHONY: all clean

all: campo

campo: campo.c
	gcc $(CFLAGS) campo.c -o campo $(LDFLAGS)

clean:
	rm -f campo