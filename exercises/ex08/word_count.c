/*
Functionality:
This program will read a text file
split the lines into words
counts the frequency of each word
and print a list of unque words and the frequencies

Purpose: 
To learn glib

Author: Jiaxuan (Amy) Wu

Compile: gcc -Wall -o word_count word_count.c $(pkg-config --cflags --libs glib-2.0)
Run: ./word_count

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
