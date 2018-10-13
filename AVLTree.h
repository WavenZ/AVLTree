#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "BasicFunctions.h"
#ifndef Status
	#define Status int 
#endif
typedef int elemtType;

typedef struct BSTNode {
	elemtType	data;
	int			bf;
	struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

#define LH 1  //左高
#define EH 0  //等高
#define RH -1 //右高

void R_Rotate(BSTree *p);
void L_Rotate(BSTree *p);
void LeftBalance(BSTree *T);
void RightBalance(BSTree *T);
Status InsertAVL(BSTree *T, elemtType e, int *taller);
Status InorderTraverse(BSTree T, int(*visit)(elemtType));
