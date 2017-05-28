#include <stdio.h>
#include <stdlib.h>
#include "readData.h"
#include "llist.h"
#include "graph.h"
#include "BSTree.h"

int main(int argc, char *argv[]) {
	List urls = GetCollection();
	showList(urls);
	Graph g = GetGraph();
	showGraph(g, 0);
	BSTree t = GetInvertedList(urls);
	showBSTree(t);
	FILE *idx = fopen("invertedIndex.txt", "w");
	BSTreeInfixDump(t, idx);
	fclose(idx);
	destroyList(urls);
	disposeGraph(g);
}
