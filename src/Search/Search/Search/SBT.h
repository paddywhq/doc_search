/*
* �ļ�����SBT.h
*
* �ļ��������������ӿڵȵ������б�DocLink.h, SBT
*
* �ļ����ܣ�ʵ�ִ�С����ƽ���������ĵ�
*
* ���ߣ�������
*
* ���ڣ�2014��1��1��
*/
#ifndef SBT_H
#define SBT_H
#include "DocLink.h"
#include <iostream>

/**
 * ���ܣ���С����ƽ���������ĵ�
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
class SBT
{
public:
	//��С����ƽ���������������
	typedef struct SBTNode{
		DocLink data; //������������ĵ�����
		SBTNode *lchild, *rchild; //���Һ���
		int size; //�Ըýڵ�Ϊ������������С
	}SBTNode, *pSBTNode;

public:
	pSBTNode head; //��С����ƽ���������

public:
	SBT();
	~SBT();

	void initSBT();
	void deleteSBT(pSBTNode &tree);
	void leftRotate(pSBTNode &tree);
	void rightRotate(pSBTNode &tree);
	bool insertNode(pSBTNode &tree, DocLink &e);
	bool indexNode(pSBTNode &tree, DocLink &e);
	bool changeNode(pSBTNode &tree, DocLink &e);
	void deleteNode(pSBTNode &tree, DocLink &e, DocLink &r);
	void maintain(pSBTNode &tree, bool flag);
	void addSBT(int i);
	void outputSBT(pSBTNode &tree);
	void buildSBT();
};

#endif