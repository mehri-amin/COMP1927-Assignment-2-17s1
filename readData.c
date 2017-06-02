#define _GNU_SOURCE
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "BSTree.h"
#include "graph.h"
#include "readData.h"
#include "llist.h"

List GetCollection() {
	FILE *f = fopen("collection.txt","r");
	List urls = getList(f);
	fclose(f);
	return urls;
}

List getList(FILE *in)
{
	List l;
	char *buff;
	l = newList();
	while (fscanf(in, "%ms\n", &buff) != EOF) { // let fscanf allocate a buffer
		ListAppend(l, buff);
		free(buff);
	}
	return l;
}

List GetOutgoingUrls(char *url) {
	int len = strlen(url) + 5;
	char *fname = malloc(sizeof(char) * len);
	snprintf(fname, len, "%s.txt", url);

	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		printf("Couldn't open '%s'\n", fname);
		return NULL;
	}
	free(fname);

	char *buf = NULL;
	size_t buflen = 0;

	while (getline(&buf, &buflen, f) != -1) {
		if (strstr(buf, "#start Section-1") == buf) {
			break;
		}
	}

	free(buf);

	buf = NULL;
	buflen = 0;

	List res = newList();
	while (getline(&buf, &buflen, f) != -1) {
		if (strstr(buf, "#end Section-1") == buf) {
			// end of section
			break;
		}
		char *entry = strtok(buf, " ");
		while (entry != NULL) {
			if (entry[0] != '\n') {
				listPrepend(res, newNode(entry));
			}
			entry = strtok(NULL, " ");
		}
	}
	free(buf);
	fclose(f);

	return res;
}

Graph GetGraph(void) {

	List urls = GetCollection();
	int nV = listLength(urls);

	Graph g = newGraph(nV);

	char buff[1000];
	int i = 0;
	FILE *f;
	char *txt = ".txt";

	Node curr = NULL;
	while(i< nV){
		curr = next(urls, curr);
		char *file = malloc((strlen(nodeValue(curr)) + 5) * sizeof(char));
		strcpy(file, nodeValue(curr));
		strcat(file, txt);
		f = fopen(file, "r");
		free(file);
		while ((fscanf(f,"%s", buff) != EOF) && strcmp(buff, "#end") != 0) {
			if ((strcmp(buff,"#start")!=0) && (strcmp(buff,"Section-1")!=0)) {
				// Get url texts from text file and treat as vertices
				addEdge(g, nodeValue(curr), buff);
			}
		}

		i++;
		fclose(f);
	}
	destroyList(urls);
	return g;
}

void strlower(char *str) {
	int len = strlen(str);
	int i;
	for (i = 0; i < len; i++) {
		str[i] = tolower(str[i]);
	}
}

void normalise(char *str) {
	strlower(str);
	// remove trailing newlines - whitespace is handled by strtok()
	// newlines can only happen once in a word thanks to getline()
	char *pos = strchr(str, '\n');
	if (pos != NULL) {
		*pos = 0; // replace with null - new end of string
	}
	// strcpy manpage says 'src and dest can't overlap', so
	// temporarily copy data into this buffer
	char *buf = malloc(sizeof(char) * strlen(str));
	// look for full stops
	while ((pos = strchr(str, '.')) != NULL) {
		strcpy(buf, pos+1);
		strcpy(pos, buf);
	}
	free(buf);
}

List GetWords(char *url) {
	int len = strlen(url) + 5;
	char *fname = malloc(sizeof(char) * len);
	snprintf(fname, len, "%s.txt", url);

	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		printf("Couldn't open '%s'\n", fname);
		return NULL;
	}
	free(fname);

	char *buf = NULL;
	size_t buflen = 0;

	while (getline(&buf, &buflen, f) != -1) {
		if (strstr(buf, "#start Section-2") == buf) {
			break;
		}
	}

	free(buf);

	buf = NULL;
	buflen = 0;

	List res = newList();
	while (getline(&buf, &buflen, f) != -1) {
		if (strstr(buf, "#end Section-2") == buf) {
			// end of section
			break;
		}
		char *entry = strtok(buf, " ");
		while (entry != NULL) {
			if (entry[0] != '\n') {
				normalise(entry);
				if (!listHasElement(res, entry))
					listPrepend(res, newNode(entry));
			}
			entry = strtok(NULL, " ");
		}
	}
	free(buf);
	fclose(f);

	return res;
}

BSTree GetInvertedList(List urls) {
	BSTree t = newBSTree();
	Node n = NULL;
	while ((n = next(urls, n)) != NULL) {
		// get words
		List words = GetWords(nodeValue(n));
		Node w = NULL;
		while ((w = next(words, w)) != NULL) {
			// Tree - each node contains "key" (word) and "value" (list of arrays)
			List vals = BSTreeFind(t, nodeValue(w));
			if (vals == NULL) {
				vals = newList();
				listPrepend(vals, newNode(nodeValue(n)));
				t = BSTreeInsert(t, nodeValue(w), vals);
			} else {
				listPrepend(vals, newNode(nodeValue(n)));
			}
		}
		destroyList(words);
	}
	return t;
}

