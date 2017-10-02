#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt/inc/btree.h"
#include <ncurses.h>

#include "model_lib.h"

#define MAX 2000

void findSuggestion(BTA *soundExTree, char *word) {
	
	char soundex[5];
	char suggestion_str[10][MAX_LEN_WORD];

	int size = suggestion(soundExTree, word, suggestion_str);

	if (size > 0)
	{
		printf("Do you mean: \n");
		for (int i = 0; i < size; i++)
		{
			printf("%s\n",suggestion_str[i] );
		}
	}
	else printf("No suggetion found\n");
}

void searchWord(BTA *dict, BTA *soundExTree, char *word, char *mean) {
	int val;
	val = findWord(dict, word, mean);

	if(val == 1) printf("%s\n", mean);

	else findSuggestion(soundExTree, word);

}

void search(BTA *dict, BTA *soundExTree) {
	char result[MAX_LEN_WORD];
	char word[MAX_LEN_WORD];
	char mean[MAX_LEN_MEAN];
	word[0] = '\0';
	int mode;
	mode = get_word(word);
	
	if(mode == 2) {
		int val = autoComplete(soundExTree,word, result);
		if (val > 0) {
			printf("%s\n", result);
			getchar();
			searchWord(dict, soundExTree, result, mean);
		}
		else  {
			printf("%s\n",word);
			getchar();
			searchWord(dict, soundExTree, word, mean);
		}
	}

	if (mode == 1)
	{	
		printf("%s\n",word);
		getchar();
		searchWord(dict, soundExTree, word, mean);
	}
}
