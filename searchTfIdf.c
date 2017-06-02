#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "readData.h"
#include "llist.h"
#include "BSTree.h"
#include "myMergeSort.h"

int countTerms(char *url, char *term) {
	char *name = malloc(sizeof(char) * (strlen(url) + 5));
	char *txt = ".txt";

	strcpy(name, url);
	strcat(name, txt);

	FILE *f = fopen(name, "r");
	free(name);

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
	int count = 0;
	while (getline(&buf, &buflen, f) != -1) {
		if (strstr(buf, "#end Section-2") == buf) {
			// end of section
			break;
		}

		char *entry = strtok(buf, " ");
		while (entry != NULL) {
			if (entry[0] != '\n') {
				normalise(entry);
				if (strcmp(entry, term) == 0) {
					count++;
				}
			}
			entry = strtok(NULL, " ");
		}
	}
	fclose(f);
	return count;
}

struct tfidf {
	double tfidf;
	char *url;
};

static int compareTfIdf(const void *a, const void *b) {
	if (a == NULL)
		return 0;
	if (b == NULL)
		return 1;
	return (((struct tfidf*)a)->tfidf > ((struct tfidf*)b)->tfidf) ? 1 : 0;
}

int main(int argc, char **argv) {
	List urls =  GetCollection();
	BSTree index = GetInvertedList(urls);
	int N = listLength(urls); // total number of documents
	struct tfidf **freqs = calloc(N, sizeof(struct tfidf*));
	int i;
	for (i = 1; i < argc; i++) { // argv[0] is the program name - skip it
		List containing = BSTreeFind(index, argv[i]);
		Node cur = NULL;
		if (containing == NULL) {
			continue;
		}
		int D = listLength(containing); // number of documents with this term
		double idf = log10((double) N / (double) D);
		while ((cur = next(containing, cur)) != NULL) {
			int idx = listIndex(urls, nodeValue(cur));
			if (freqs[idx] == NULL) {
				freqs[idx] = malloc(sizeof(struct tfidf));
				freqs[idx]->url = strdup(nodeValue(cur));
				freqs[idx]->tfidf = 0;
			}
			int count = countTerms(nodeValue(cur), argv[i]);
			freqs[idx]->tfidf += (double)count * idf;
		}
	}

	myMergeSort((void*)freqs, 0, N-1, N, compareTfIdf);
	for (i = 0; i < N; i++) {
		if (freqs[i] == NULL)
			continue;
		if (freqs[i]->tfidf > 0) {
			printf("%s %0.6f\n", freqs[i]->url, freqs[i]->tfidf);
		}
	}
	return 0;
}
