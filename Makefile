CC = gcc

CFILES = main.c

all: $(CFILES)
	$(CC) $(CFLAGS) -g -o gtkdatetimepicker $(CFILES) `pkg-config --cflags --libs gtk+-3.0` --std=c99
