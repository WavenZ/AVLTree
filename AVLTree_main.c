#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

int visit(int e) {
	printf("%d ", e);
	return 1;
}

int main(int argc, char* argv[]) {
	
	int data;
	int taller=0;
	BSTree T=NULL;
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	while (scanf("%d", &data) != -1) {
		InsertAVL(&T, data, &taller);
	}
	InorderTraverse(T, visit);
	fclose(stdin);
	fclose(stdout);
	system("pause");
	return 1;
}