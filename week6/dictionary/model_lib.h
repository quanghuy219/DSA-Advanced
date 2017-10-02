#define MAX_LEN_WORD 40
#define MAX_LEN_MEAN 1000

int createSoundExTree(BTA *dict, BTA *soundExTree);

/*
** find meaning a @param word
** meaning stored in @param mean
*/
int findWord(BTA *dict, char *word, char *mean);

/*
** @param word
** @param: find first matching word in soundExTree
** return 1 : found, 0: not found 
/*/
int autoComplete(BTA *soundExTree, char *word, char *result);

/*
** get input word
** source code: input.c
*/
int get_word(char *word);

/*
** return max - 10 suggession of @param word
*/
int suggestion(BTA *soundExTree, char* word, char suggestion[][MAX_LEN_WORD]);