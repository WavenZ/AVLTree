/*
	@brief:平衡二叉树
	@author：WavenZ
	@time:2018/10/13
*/
#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"


void R_Rotate(BSTree *p) {//右旋
	BSTNode *lc = NULL;
	lc = (*p)->lchild;
	(*p)->lchild = lc->rchild;
	lc->rchild = (*p);
	(*p) = lc;
}
void L_Rotate(BSTree *p) {//左旋
	BSTNode *lc = NULL;
	lc = (*p)->rchild;
	(*p)->rchild = lc->lchild;
	lc->lchild = (*p);
	(*p) = lc;
}
void LeftBalance(BSTree *T) {//左平衡
	BSTNode *lc = (*T)->lchild;
	BSTNode *rd = NULL;
	switch (lc->bf){
	case LH://与（*T）->bf同号
		(*T)->bf = lc->bf = EH;//平衡之后因子为0
		R_Rotate(T); //右旋
		break;
	case RH://与（*T）->bf异号
		rd = lc->rchild;//rd指向lc的左子树根节点
		switch (rd->bf) {//计算各节点的因子
		case LH:(*T)->bf = RH; lc->bf = EH; break;//如果因子为1，则（*T）->bf=-1，lc->bf=0;
		case EH:(*T)->bf = lc->bf = EH;		break;//如果因子为0，则都为0
		case RH:(*T)->bf = EH; lc->bf = LH; break;//如果因子为-1，则（*T)->bf=0, lc-bf=1;
		default:break;
		}
		rd->bf = EH;
		L_Rotate(&(*T)->lchild);
		//R_Rotate(&(*T));
		R_Rotate(T);
	default:break;
	}
}

void RightBalance(BSTree *T) {//右平衡
	BSTNode *lc = (*T)->rchild;
	BSTNode *rd = NULL;
	switch (lc->bf) {
	case RH://与（*T）->bf同号
		(*T)->bf = lc->bf = EH;//平衡之后因子为0
		L_Rotate(T); //右旋
		break;
	case LH://与（*T）->bf异号
		rd = lc->lchild;//rd指向lc的左子树根节点
		switch (rd->bf) {//计算各节点的因子
		case RH:(*T)->bf = LH; lc->bf = EH; break;//如果因子为1，则（*T）->bf=-1，lc->bf=0;
		case EH:(*T)->bf = lc->bf = EH;		break;//如果因子为0，则都为0
		case LH:(*T)->bf = EH; lc->bf = RH; break;//如果因子为-1，则（*T)->bf=0, lc-bf=1;
		default:break;
		}
		rd->bf = EH;
		R_Rotate(&(*T)->rchild);
		//L_Rotate(&(*T));
		L_Rotate(T);
	default:break;
	}
}
Status InsertAVL(BSTree *T, elemtType e, int *taller) {
	//taller反应是否长高
	if (!(*T)){//空树，插入
		(*T) = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = 1;
	}
	else {
		if (EQ(e, (*T)->data)) {//插入元素已经存在，不再插入
			*taller=0;
			return 0;
		}
		if (LT(e, (*T)->data)) {//小于
			if (!InsertAVL(&(*T)->lchild, e, taller)) return 0;//插入不成功，返回0
			if (*taller) {//如果插入成功且taller=1
				switch ((*T)->bf) {//
				case LH://如果（*T）->bf=1,即左边高，则进行左平衡
					LeftBalance(T);
					*taller = 0;
					break;
				case EH://如果（*T）->bf=0,即平衡，则左插入后（*T）->bf=1，即左高
					(*T)->bf = LH;
					*taller = 1; 
					break;
				case RH:
					(*T)->bf = EH;//如果（*T）->bf=-1,即右边高，则插入后即平衡
					*taller = 0;
					break;
				default:break;
				}
			}
			}
		else {
			if (!InsertAVL(&(*T)->rchild, e, taller)) return 0;
			if (*taller) {
				switch ((*T)->bf) {
				case LH://如果是左高，右插后变平衡
					(*T)->bf = EH;
					*taller = 0;
					break;
				case EH://如果是平衡术，右插后变右高
					(*T)->bf = RH;
					*taller = 1;
					break;
				case RH://如果是右高，右插后则需要进行平衡
					RightBalance(T);
					*taller = 0;
					break;
				default:break;
				}

			}
		}
	}
	return 1;
}

Status InorderTraverse(BSTree T, int(*visit)(elemtType)) {
	if (T) {
		InorderTraverse(T->lchild, visit);
		visit(T->data);
		InorderTraverse(T->rchild, visit);
	}
	else return 0;
	return 1;
}