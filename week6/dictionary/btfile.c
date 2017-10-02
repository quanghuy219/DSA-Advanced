#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include "soundex.h"
#include "bt/inc/btree.h"

#define MAX_WORD 100
#define MAX_DATA 50000
#define MAX 1000
#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 1000

void correct(char *str) {
	while (str[strlen(str) - 1] == '\n') str[strlen(str)-1] = '\0';
}

void split_word(char *word, char* mean) {
	int mark = 0;
	size_t i;
	for (i = 0; i < strlen(word); i++)
	{
		if(word[i] == '/') {
			mark = i;
			break;
		} 
	}
	if(mark != 0) {
	 	//strcat(mean,word+mark);
	 	// for (int i = mark; i < strlen(word); i++)
	 	// {
	 	// 	mean[i-mark] = word[i];
	 	// }
	 	word[mark-1] = '\0';
	}
	 
	for (i = 0; i < strlen(word); i++)
	{
		word[i] = word[i+1];
	}
}

int createBdict(FILE* fi,BTA* dict) {
	int count = 0;
	char word[MAX_WORD];
	char data[MAX_DATA];
	char buff[MAX_DATA];
	int val;

	while(!feof(fi)) {
	
		fgets(buff, MAX_DATA, fi);

		while(buff[0] != '@') {
			strcat(data, buff);
			if(feof(fi)) break;
			fgets(buff, MAX_DATA, fi);
		}

		correct(data);
		if(strlen(word) != 0 && strlen(data) != 0) {
			val = btins(dict, word, data, MAX * sizeof(char));
			
		}
		count++;
		if (buff[0] == '@')
		{
			word[0] = '\0';
			data[0] = '\0';	
			strcpy(word,buff);
			correct(word);
			split_word(word,data);
		}
		buff[0] = '\0';
	}
	return count;
}

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

int main()
{
	FILE* f1 = fopen("src.txt","r");
	btinit();
	BTA* dict = btcrt("dict.dat",0,0);
	BTA* soundExTree = btcrt("soundExTree.dat",0,0);

	if (dict == NULL)
	{
		printf("Error\n");
		return 0;
	}

	int words = createBdict(f1,dict);
	printf("Words inserted: %d\n", words);
	
	createSoundExTree(dict, soundExTree);

	fclose(f1);
	btcls(dict);
	return 0;
}