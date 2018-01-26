/*
* 文件名：SBT.h
*
* 文件中所包含的类或接口等的名称列表：DocLink.h, SBT
*
* 文件功能：实现大小二叉平衡树倒排文档
*
* 作者：王华清
*
* 日期：2014年1月1日
*/
#ifndef SBT_H
#define SBT_H
#include "DocLink.h"
#include <iostream>

/**
 * 功能：大小二叉平衡树倒排文档
 * 作者：王华清
 * 日期：2014年1月1日
 */
class SBT
{
public:
	//大小二叉平衡树结点数据类型
	typedef struct SBTNode{
		DocLink data; //结点所存词语的文档链表
		SBTNode *lchild, *rchild; //左右孩子
		int size; //以该节点为根结点的子树大小
	}SBTNode, *pSBTNode;

public:
	pSBTNode head; //大小二叉平衡树根结点

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