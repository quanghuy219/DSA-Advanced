#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt/inc/btree.h"
#include "soundex.h"

#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 1500


int createSoundExTree(BTA *dict, BTA *soundExTree) {
	char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];
	int rsize;
	int count = 0;
	char soundex[5];

	btsel(dict,"", mean, MAX_LEN_MEAN *sizeof(char), &rsize);
	while(  btseln(dict,word, mean, MAX_LEN_MEAN * sizeof(char), &rsize) == 0 ) {
		SoundEx(soundex, word,4,1);
		btins(soundExTree, word, soundex, 5 * sizeof(char));
		count++;
	}
	return count;
}

int findWord(BTA *dict, char *word, char *mean) {
	int rsize;
	int val;

	val = btsel(dict, word, mean, MAX_LEN_MEAN * sizeof(char), &rsize );

	if(val == 0) return 1;

	else return 0;
}


//chek if s1 is pre-substr of s2
int preStr(char *s1, char *s2) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);

	if(len1 > len2) return 0;

	for (int i = 0; i < len1; ++i)
	{
		if(s1[i] != s2[i]) return 0;
	}

	return 1;
}


int autoComplete(BTA *soundExTree, char *word, char *result) {
	
	int rsize;
	char en[MAX_LEN_WORD];
	char soundex[5];
	int check = 0;

	btsel(soundExTree, "", soundex, 5 * sizeof(char), &rsize);
	while( btseln(soundExTree,en, soundex, 5 * sizeof(char), &rsize ) == 0 ) {
		check = preStr(word, en);
		if(check == 1)  {
			strcpy(result, en);
			return 1;	
		}
	}
	
	return 0;
}

int suggestion(BTA *soundExTree, char* word, char suggestion[][MAX_LEN_WORD]) {
	int rsize;
	char word_soundex[5];
	char soundex[5];
	int size = 0;
	char en[MAX_LEN_WORD];

	SoundEx(word_soundex, word, 4,1);

	btsel(soundExTree, "", soundex, 5 * sizeof(char), &rsize);
	while( btseln(soundExTree, en, soundex, 5 * sizeof(char), &rsize ) == 0 && size < 10) {
		if ( strcmp(word_soundex, soundex) == 0 ) {
			strcpy(suggestion[size], en);
			size++;
		}
	}
	return size;
}
