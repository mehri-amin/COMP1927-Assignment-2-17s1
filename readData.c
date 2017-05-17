#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

// Linked List ADT

typedef struct Node {
	char *val;
	struct Node *next;
} *Node;

typedef struct ListHead {
	struct Node *head;
	int length;

} *List;

Node newNode(char *val) {
	struct Node *n = malloc(sizeof(struct Node));
	n->val = strdup(val);
	n->next = NULL;
	return n;
}

char *nodeValue(Node n) {
	return n->val;
}

List newList() {
	List l = calloc(1, sizeof(struct ListHead));
	l->head = NULL;
	return l;
}

void destroyList(List l) {
	Node cur = l->head;
	while (cur != NULL) {
		Node tmp = cur;
		free(cur->val);
		cur = cur->next;
		free(tmp);
	}
	free(l);
}

Node next(List l, Node n) {
	if (n == NULL)
		return l->head;
	return n->next;
}

void listPrepend(List l, Node n) {
	n->next = l->head;
	l->head = n;
	l->length++;
}

int listLength(List l) {
	return l->length;
}

void showList(List l) {
	Node n = NULL;
	printf("list(length=%d)", l->length);
	while ((n = next(l, n)) != NULL) {
		printf(", %s", n->val);
	}
	printf("\n");
}


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

int main(int argc, char *argv[]) {
	List urls = GetCollection();
	showList(urls);
	Graph g = GetGraph(urls);
	showGraph(g, 0);
	destroyList(urls);
	disposeGraph(g);
}
