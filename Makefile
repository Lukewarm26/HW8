# Makefile
# Lucas Eifert
# COSC 3750 Spring 22
# Homework 8
# Modified 04/19/2022
#
# Makefile to compile wyshell program
CC=gcc
CFLAGS=-Wall -ggdb
RM=/bin/rm -f

wyshell: wyshell.c
	${CC} ${CFLAGS} wyshell.c wyScanner.c wyshell

clean:
	${RM} wyshell