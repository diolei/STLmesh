CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -lm

SRCS = STLmesh.c
EXEC = meshData

all: $(EXEC)

$(EXEC): $(SRCS)
	     $(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(EXEC)

