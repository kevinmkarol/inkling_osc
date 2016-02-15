CC = gcc
CFLAGS = -g -Wall -framework CoreFoundation -framework IOKit

OBJECTS = main.o inkling/inkling_listener.o osc_broadcaster/osc_broadcaster.o libraries/hidapi/mac/hid.o libraries/tinyosc/tinyosc.o

default: $(OBJECTS)
	$(MAKE) -C libraries
	$(CC) -o inkling_broadcaster $(OBJECTS) $(CFLAGS)


libraires/tinyosc/tinyosc.o: tinyosc.c
	$(CC) -o tinyosc.c

clean:
	-rm -f *.o
	-rm -f $(TARGET)
