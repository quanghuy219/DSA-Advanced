#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jrb_graph.h"

#define MAX_LEN 100

void correct(char *s) {
  for (int i=0; i<strlen(s); i++) {
    	if (s[i] == '_')
      		s[i] = ' ';
	}
	while(s[strlen(s) - 1] == '\n' || s[strlen(s) - 1] == ' ') s[strlen(s) - 1] = '\0';
	while(s[0] == ' ') strcpy(s,s+1);
}

int splitStr(char* input, char *out, char* delim, size_t size) {
	if(input == NULL) return -1;
	char* strCpy = (char*)malloc( 100 * sizeof(char) + 1);
	strcpy(strCpy, input);
	char* token;
	int i = 0;
	token = strtok(strCpy, delim);
	while(token != NULL) {
		strcpy(out + i * size,token);
		token = strtok(NULL,delim);
		i++;
	}
	return i;
}

void readFile(FILE* fin, Graph list, Graph map) {
	char *string = (char*)malloc(MAX_LEN * sizeof(char));
	
	char* buff = (char*)malloc(100*sizeof(char));
	fgets(buff,100,fin);
	
	correct(buff);

	while(!feof(fin)) {
		if( strcmp(buff,"[STATIONS]") == 0) {
			while(fgets(buff, MAX_LEN, fin) != NULL && buff[0] != '[') {
				correct(buff);
				splitStr(buff, string, "=", MAX_LEN);
				correct(string);
				char *key = strdup(string);
				correct(string + MAX_LEN);
				char* val = strdup(string + MAX_LEN);
				jrb_insert_str(list, key, new_jval_s(val));
			}
		}

		correct(buff);

		if (strcmp(buff, "[LINES]") == 0) {
			while(fgets(buff,MAX_LEN, fin) != NULL && buff[0] != '[') {
				splitStr(buff, string, "=", MAX_LEN);
				correct(string + MAX_LEN);
				char *stations = (char*)malloc( MAX_LEN * sizeof(char));
				int x = splitStr(string + MAX_LEN, stations, " ", 10);
				for (int i = 0; i < x-1; i++)
				{	
					//printf("%s  %s\n",string1 + i * 10, string1 + (i+1) *10 );
					addEdge(map, stations + i * 10, stations + (i+1) * 10 );
				}
				
			}
		}
	}

}

void printVertex(char* v) {
  printf("%-5s",v);
}

int main()
{
	FILE *f1 = fopen("map.txt", "r");
	Graph list = createGraph();
	Graph map = createGraph();

	readFile(f1, list, map);
	
	findShortestPath(map,"S1","S9");
	
	
	return 0;
}