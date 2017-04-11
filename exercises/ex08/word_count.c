/*
Functionality:
This program will read a text file
split the lines into words
counts the frequency of each word
and print a list of unique words and the frequencies

Purpose: 
To learn glib

Author: Jiaxuan (Amy) Wu

Compile: gcc -Wall -o word_count word_count.c $(pkg-config --cflags --libs glib-2.0)
Run: ./word_count sample.txt

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

/*prints out frequency of words*/
void printFrequency(gpointer key,gpointer value,gpointer user_data){
	printf(user_data,(char *)key,(int *)value);
}

/*splits of words in textfile*/
int main(int argc, char** argv) {
	if(argc!=2){
		printf("Select a textfile when you run the program\n"); 
		return -1;
	}
	
	const gchar* file = argv[1];
	gchar* words;
	GError* error = NULL;
	
	//splits lines into words using String utility
	g_file_get_contents(file,&words,NULL,&error);
	gchar** word = g_strsplit(words," ",-1);
	
	//count frequency
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	while(*word){
		gpointer count = g_hash_table_lookup(hash,*word);
		if(!count){
			g_hash_table_insert(hash,*word,(gpointer)1);
		}else{
			g_hash_table_replace(hash,*word,count+1);
		}
		word++;
	}

	g_hash_table_foreach(hash,(GHFunc)printFrequency,"%s appears %d times\n");
	g_hash_table_destroy(hash);
	return 0;
}
