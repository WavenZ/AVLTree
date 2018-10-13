/*
	@brief:ƽ�������
	@author��WavenZ
	@time:2018/10/13
*/
#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"


void R_Rotate(BSTree *p) {//����
	BSTNode *lc = NULL;
	lc = (*p)->lchild;
	(*p)->lchild = lc->rchild;
	lc->rchild = (*p);
	(*p) = lc;
}
void L_Rotate(BSTree *p) {//����
	BSTNode *lc = NULL;
	lc = (*p)->rchild;
	(*p)->rchild = lc->lchild;
	lc->lchild = (*p);
	(*p) = lc;
}
void LeftBalance(BSTree *T) {//��ƽ��
	BSTNode *lc = (*T)->lchild;
	BSTNode *rd = NULL;
	switch (lc->bf){
	case LH://�루*T��->bfͬ��
		(*T)->bf = lc->bf = EH;//ƽ��֮������Ϊ0
		R_Rotate(T); //����
		break;
	case RH://�루*T��->bf���
		rd = lc->rchild;//rdָ��lc�����������ڵ�
		switch (rd->bf) {//������ڵ������
		case LH:(*T)->bf = RH; lc->bf = EH; break;//�������Ϊ1����*T��->bf=-1��lc->bf=0;
		case EH:(*T)->bf = lc->bf = EH;		break;//�������Ϊ0����Ϊ0
		case RH:(*T)->bf = EH; lc->bf = LH; break;//�������Ϊ-1����*T)->bf=0, lc-bf=1;
		default:break;
		}
		rd->bf = EH;
		L_Rotate(&(*T)->lchild);
		//R_Rotate(&(*T));
		R_Rotate(T);
	default:break;
	}
}

void RightBalance(BSTree *T) {//��ƽ��
	BSTNode *lc = (*T)->rchild;
	BSTNode *rd = NULL;
	switch (lc->bf) {
	case RH://�루*T��->bfͬ��
		(*T)->bf = lc->bf = EH;//ƽ��֮������Ϊ0
		L_Rotate(T); //����
		break;
	case LH://�루*T��->bf���
		rd = lc->lchild;//rdָ��lc�����������ڵ�
		switch (rd->bf) {//������ڵ������
		case RH:(*T)->bf = LH; lc->bf = EH; break;//�������Ϊ1����*T��->bf=-1��lc->bf=0;
		case EH:(*T)->bf = lc->bf = EH;		break;//�������Ϊ0����Ϊ0
		case LH:(*T)->bf = EH; lc->bf = RH; break;//�������Ϊ-1����*T)->bf=0, lc-bf=1;
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
	//taller��Ӧ�Ƿ񳤸�
	if (!(*T)){//����������
		(*T) = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = 1;
	}
	else {
		if (EQ(e, (*T)->data)) {//����Ԫ���Ѿ����ڣ����ٲ���
			*taller=0;
			return 0;
		}
		if (LT(e, (*T)->data)) {//С��
			if (!InsertAVL(&(*T)->lchild, e, taller)) return 0;//���벻�ɹ�������0
			if (*taller) {//�������ɹ���taller=1
				switch ((*T)->bf) {//
				case LH://�����*T��->bf=1,����߸ߣ��������ƽ��
					LeftBalance(T);
					*taller = 0;
					break;
				case EH://�����*T��->bf=0,��ƽ�⣬��������*T��->bf=1�������
					(*T)->bf = LH;
					*taller = 1; 
					break;
				case RH:
					(*T)->bf = EH;//�����*T��->bf=-1,���ұ߸ߣ�������ƽ��
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
				case LH://�������ߣ��Ҳ���ƽ��
					(*T)->bf = EH;
					*taller = 0;
					break;
				case EH://�����ƽ�������Ҳ����Ҹ�
					(*T)->bf = RH;
					*taller = 1;
					break;
				case RH://������Ҹߣ��Ҳ������Ҫ����ƽ��
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