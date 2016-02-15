TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: tinyOSC
	$(MAKE) -C hidapi

tinyOSC: tinyosc/tinyosc.h tinyosc/tinyosc.c
	$(CC) -o tinyosc/tinyosc.c