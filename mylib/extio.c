#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20

void correct(char *s) {
  for (int i=0; i<strlen(s); i++) {
    	if (s[i] == '_')
      		s[i] = ' ';
	}
	while(s[strlen(s) - 1] == '\n') s[strlen(s) - 1] = '\0';
	while(s[0] == ' ') strcpy(s,s+1);
}

void* my_memcpy(void* region1, const void* region2, size_t n) {
	const char* first = (const char*) region2;
	const char* last = ((const char*) region2) + n;
	char* result = (char*) region1;
	while(first != last) *result++ = *first++;
}

int exch(void* buff, int size, int pos1, int pos2) {
	if(buff == NULL) return -1;
	void* tmp = malloc(size);
	memcpy(tmp, (char*)buff+pos1*size, size);
	memcpy((char*)buff+pos1*size, (char*)buff+pos2*size, size);
	memcpy((char*)buff+pos2*size, tmp, size);
	free(tmp);
	return 1;
}

int splitStr(char* input, char *out, char* delim) {
	if(input == NULL) return -1;
	char* strCpy = (char*)malloc( 100 * sizeof(char) + 1);
	strcpy(strCpy, input);
	char* token;
	int i = 0;
	token = strtok(strCpy, delim);
	while(token != NULL) {
		strcpy(out + i * MAX_LEN,token);
		token = strtok(NULL,delim);
		i++;
	}
	return i;
}

char* convertName(char *s) {
	if(s == NULL) return NULL;
	char *tmp = (char*)malloc(MAX_LEN * sizeof(char));
	int count = splitStr(s, tmp);
	char *result = (char*)malloc(sizeof(char) * MAX_LEN);
	
	for (int i = count-1; i >= 0; i--)
	{
		strcat(result,tmp + i * MAX_LEN);
		strcat(result," ");
	}

	while (!isalpha(result[strlen(result) - 1]))
	{
		result[strlen(result) - 1] = '\0';
	}
	return result;
}

int main(int argc, char const *argv[])
{
	char* buff = "Pham Quang Huy";
	char* name = (char*)malloc(5 * MAX_LEN * sizeof(char));
	//int x = exch(buff,20, 0 ,1);
	name = convertName(buff);
	printf("%s\n",name );
	// for (int i = 0; i < x; i++)
	// {
	// 	printf(".%s.\n",name + i * MAX_LEN);
	// }
	
	return 0;
}
