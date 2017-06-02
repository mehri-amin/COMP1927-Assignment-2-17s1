#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "searchPagerank.h"

#define MAX_LENGTH 100
#define MAX_URLS 100

struct words {

	char *line;
	int *urls;
	struct words *next;

};

words newWord(){

	struct words *n = malloc(sizeof(words));
	assert(n != NULL);
	n->line = malloc(100* sizeof(char));
	n->next = NULL;
	n->urls = malloc(MAX_URLS * sizeof(int));

	return n;

}

int main( int argc, char *argv[]){

	if( argc > 1){


		struct words *head = newWord();
		head = inputindex(head);
		findmatches(argv, head, argc);

	}else{
		printf("Too few arguments.\n");

	}

	return 0;
}


words inputindex(words head){

	FILE* fii;

	int i,k,l;
	int endofline;
	struct words *prev = NULL;
	struct words *n = NULL;
	if( (fii = fopen("invertedIndex.txt","r")) != NULL ){
		while( 1 ){
			char *input = malloc(MAX_LENGTH* sizeof(char));
			if(fgets(input, MAX_LENGTH, fii) == 0) break;
			i = 0;
			endofline = 0;
			n = newWord();
			if(prev != NULL){
				prev->next = n;
			}

			//storing the keywords in char*
			while(input[i] != '\0' && input[i] != '\n' && input[i] != ' ' && i < MAX_LENGTH){
				n->line[i] = input[i];
				i++;
				if(input[i] == '\n' || input[i] == '\0')
					endofline = 1;
			}
			if(head->line[0] == 0)
				head->line = strdup(n->line);

			//skipping all the spaces
			while(input[i] == ' ')
				i++;
			l = 0;
			//storing all the urls in int[] until reaches the end of line
			while(!endofline){
				char* url = malloc(10* sizeof(char));
				k = 0;
				while(input[i] != EOF && input[i] != '\n' && input[i] != ' '){
					if(input[i] == 'u' && input[i+1] == 'r' && input[i+2] == 'l'){
						i = i + 3;
					}
					url[k] = input[i];
					k++;
					i++;
					if(input[i] == '\n' || input[i] == EOF)
						endofline = 1;
				}

				while(input[i] == ' ')
					i++;
				if(input[i] == '\n' || input[i] == EOF)
					endofline = 1;

				k = 0;
				n->urls[l] = atoi(url);
				l++;
				free(url);

			}
			prev = n;

			//removing urls that shouldnt exist
			i = l;
			while( n->urls[i] != 0 ){
				n->urls[i] = 0;
			}


			if(head->next == NULL){
				i = 0;
				for(i = 0; i < l; i++){
					head->urls[i] = n->urls[i];
				}
				prev = head;
				free(n);
			}

			free(input);
		}
		fclose(fii);
	}
	return head;
}

int inputpr(int url[], float pr[]){

	FILE* fpr;
	int i;

	if( (fpr = fopen("pagerankList.txt","r")) != NULL ){
		i = 0;
		while(!feof(fpr)){
			char* degree = malloc(MAX_LENGTH* sizeof(char));
			char* string = malloc(MAX_LENGTH* sizeof(char));
			char* urls = malloc(MAX_LENGTH* sizeof(char));

			//getting inputs from pagranklist.txt
			fscanf(fpr,"%[^,],%[^,],%f", string, degree, &pr[i]);
			//printf("<%s> ",string);
			//printf("<%d> ",atoi(degree));
			//printf("%.8f ", pr[i]);
			fscanf(fpr,"\n");

			int k = 0;
			int l = 0;
			while(string[l] != 'u')
				l++;

			//changing "url123" to (int) 123
			if(string[l] == 'u' && string[l+1] == 'r' && string[l+2] == 'l'){
				while(isdigit(string[k+3])){
					urls[k] = string[l+3];
					k++;
					l++;
				}
			}
			urls[k] = '\0';
			url[i] = atoi(urls);
			i++;
			free(string);
			free(degree);
			free(urls);
		}
		fclose(fpr);
	} else {
		printf("failed to open pagerank\n");
	}

	return i;
}

void findmatches(char* argv[], words head, int argc){

	int match[100] = {0};
	int i = 0;
	struct words *curr = head;
	int appear = 0;

	//putting all the urls from firs line/keyword in match[]
	while( curr != NULL){
		appear = 0;
		if( !strcmp(argv[1],curr->line) ){
			while(curr->urls[i] != 0){
				match[i] = curr->urls[i];
				i++;
			}
			appear = 1;
			break;
		}
		if(appear) break;
		curr = curr->next;
	}

	int k = 2;
	int check = 0;

	int l = 0;

	if(appear){
		appear = 0;
		while(k < argc){
			curr = head;
			while(curr != NULL){
				appear = 0;
				if( !strcmp(argv[k],curr->line) ){
					i = 0;
					while(match[i] != 0){
						l = 0;
						check = 0;
						while(curr->urls[l] != 0){

							if(curr->urls[l] == match[i]){
								check = 1;
								break;
							}
							l++;
						}
						//setting all the uncommon url to -1
						if( check == 0){
							match[i] = -1;
						}else{
							appear = 1;
						}
						i++;
					}
				}
				if(appear)
					break;
				curr = curr->next;
			}
			k++;
		}
	}

	int url[100] = {0};
	float pr[100] = {0};

	int count = 0;
	count = inputpr(url,pr);

	if(count > 10)
		count = 10;
	i = 0;

	while(url[i] != 0 && i < count){
		k = 0;
		while(match[k] != 0){
			if(match[k] == url[i])
				printf("url%d\n",url[i]);
			k++;
		}
		i++;
	}
}
