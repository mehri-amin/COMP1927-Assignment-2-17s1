#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "BSTree.h"
#include "graph.h"
#include "readData.h"
#include "llist.h"

List GetCollection() {
	FILE *f = fopen("collection.txt", "r");
	List l = newList();
	char *buf = NULL;
	size_t bufsize = 0;
	while (getline(&buf, &bufsize, f) != -1) {
		char *entry = strtok(buf, " ");
		while (entry != NULL) {
			if (entry[0] != '\n') {
				listPrepend(l, newNode(entry));
			}
			entry = strtok(NULL, " ");

		}
	}
	fclose(f);
	free(buf);
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

Graph GetGraph(List urls) {
	Node cur = NULL;
	Graph g = newGraph(listLength(urls));
	while ((cur = next(urls, cur)) != NULL) {
		List outgoing = GetOutgoingUrls(nodeValue(cur));
		Node edge = NULL;
		while ((edge = next(outgoing, edge)) != NULL) {
			addEdge(g, nodeValue(cur), nodeValue(edge));
		}
		destroyList(outgoing);
	}
	return g;
}

void strlower(char *str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
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
			List vals = BSTreeFind(t, nodeValue(w));
			if (vals == NULL) {
				vals = newList();
				listPrepend(vals, newNode(nodeValue(n)));
				t = BSTreeInsert(t, nodeValue(w), vals);
			} else {
				listPrepend(vals, newNode(nodeValue(n)));
			}
		}
	}
	return t;
}

