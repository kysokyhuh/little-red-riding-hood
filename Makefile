CC = gcc
CFLAGS = -Wall -Iheaders
SOURCES = main.c agent.c grid.c elements.c utils.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
