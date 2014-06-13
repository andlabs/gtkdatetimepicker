CC = gcc

CFILES = main.c datetimepicker.c

all: $(CFILES)
	$(CC) $(CFLAGS) -g -o datetimepicker $(CFILES) `pkg-config --cflags --libs gtk+-3.0` --std=c99
