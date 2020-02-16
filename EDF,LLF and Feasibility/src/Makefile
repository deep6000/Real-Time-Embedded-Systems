
CC=gcc
TARGET = feasibility

CDEFS=
CFLAGS= -w -g 

HFILES:= -I../inc/
SOURCES= $(wildcard *.c)

OBJECTS= $(SOURCES:.c=.o)

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o  $(TARGET) $(HFILES) -lm

clean:
	rm -f *.o
	rm -f $(TARGET)

distclean:
	rm -f *.o *.d

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@ $(HFILES)
