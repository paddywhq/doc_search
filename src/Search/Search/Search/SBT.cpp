/*
* 文件名：SBT.cpp
*
* 文件中所包含的类或接口等的名称列表：SBT.h, LinkedList.h
*
* 文件功能：实现大小二叉平衡树倒排文档函数
*
* 作者：王华清
*
* 日期：2014年1月1日
*/
#include "StdAfx.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include"SBT.h"
#include"LinkedList.h"

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
* 日期：2014年1月1日
 */
SBT::SBT()
{
	head = NULL;
}

/**
 * 功能：析构函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
SBT::~SBT()
{
	deleteSBT(head);
}

/**
 * 功能：初始化
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::initSBT()
{
	deleteSBT(head); //删除树
}

/**
 * 功能：删除平衡树
 * 参数及返回值说明：
 *     参数：tree：根结点
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::deleteSBT(pSBTNode &tree)
{
	if(tree == NULL) //树为空时退出
		return;
	deleteSBT(tree->lchild); //删除左子树
	deleteSBT(tree->rchild); //删除右子树
	delete tree; //删除根结点
	tree = NULL;
}

/**
 * 功能：左旋
 * 参数及返回值说明：
 *     参数：tree：根结点
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::leftRotate(pSBTNode &tree)
{
	pSBTNode temp;

	//左旋操作
	temp = tree->rchild;
	tree->rchild = temp->lchild;
	temp->lchild = tree;
	tree = temp;

	//修改左旋后树大小
	if(tree->lchild->lchild != NULL && tree->lchild->rchild != NULL)
		tree->lchild->size = tree->lchild->lchild->size + tree->lchild->rchild->size + 1;
	else if(tree->lchild->lchild == NULL && tree->lchild->rchild != NULL)
		tree->lchild->size = tree->lchild->rchild->size + 1;
	else if(tree->lchild->lchild != NULL && tree->lchild->rchild == NULL)
		tree->lchild->size = tree->lchild->lchild->size + 1;
	else
		tree->lchild->size = 1;
	if(tree->rchild != NULL)
		tree->size = tree->lchild->size + tree->rchild->size + 1;
	else
		tree->size = tree->lchild->size + 1;
}

/**
 * 功能：右旋
 * 参数及返回值说明：
 *     参数：tree：根结点
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::rightRotate(pSBTNode &tree)
{
	pSBTNode temp;

	//右旋操作
	temp = tree->lchild;
	tree->lchild = temp->rchild;
	temp->rchild = tree;
	tree = temp;

	//修改右旋后树大小
	if(tree->rchild->rchild != NULL && tree->rchild->lchild != NULL)
		tree->rchild->size = tree->rchild->rchild->size + tree->rchild->lchild->size + 1;
	else if(tree->rchild->rchild == NULL && tree->rchild->lchild != NULL)
		tree->rchild->size = tree->rchild->lchild->size + 1;
	else if(tree->rchild->rchild != NULL && tree->rchild->lchild == NULL)
		tree->rchild->size = tree->rchild->rchild->size + 1;
	else
		tree->rchild->size = 1;
	if(tree->lchild != NULL)
		tree->size = tree->rchild->size + tree->lchild->size + 1;
	else
		tree->size = tree->rchild->size + 1;
}

/**
 * 功能：插入结点
 * 参数及返回值说明：
 *     参数：tree：根结点
 *           e：待插入的值
 *     返回值：插入是否成功（是否已存在待插入结点）
 * 作者：王华清
 * 日期：2014年1月1日
 */
bool SBT::insertNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //若树为空，插入新结点
	{
		tree = new(SBTNode);
		tree->lchild = NULL;
		tree->rchild = NULL;
		tree->size = 1;
		tree->data = e;
		return true;
	}
	else //若树不为空
	{
		if(tree->data > e) //若待插入元素小
		{
			if(insertNode(tree->lchild, e)) //若插入成功
			{
				tree->size++; //修改树大小
				maintain(tree, e > tree->data); //平衡维护
				return true;
			}
			return false;
		}
		else if(tree->data < e) //若待插入元素大
		{
			if(insertNode(tree->rchild, e)) //若插入成功
			{
				tree->size++; //修改树大小
				maintain(tree, e > tree->data); //平衡维护
				return true;
			}
			return false;
		}
		else //若已存在待插入元素，不操作
			return false;
	}
}

/**
 * 功能：平衡维护
 * 参数及返回值说明：
 *     参数：tree：根结点
 *           flag：因左子树还是右子树插入结点导致需要维护
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::maintain(pSBTNode &tree, bool flag)
{
	if(tree->size <= 2) //无需维护
		return;
	if(flag == false) //在左子树插入了结点
	{
		if(tree->rchild == NULL) //若右子树为空
		{
			if(tree->lchild->lchild != NULL) //若左子树的左子树不为空
			{
				rightRotate(tree);
				goto check;
			}
			else if(tree->lchild->rchild != NULL) //若左子树的右子树不为空
			{
				leftRotate(tree->lchild);
				rightRotate(tree);
				goto check;
			}
		}
		if(tree->lchild->lchild != NULL) //若左子树的左子树不为空
		{
			if(tree->lchild->lchild->size > tree->rchild->size) //若左子树的左子树比右子树大
			{
				rightRotate(tree);
				goto check;
			}
		}
		if(tree->lchild->rchild != NULL) //若左子树的右子树不为空
		{
			if(tree->lchild->rchild->size > tree->rchild->size) //若左子树的右子树比右子树大
			{
				leftRotate(tree->lchild);
				rightRotate(tree);
				goto check;
			}
		}
		return;
	}
	else if(flag == true) //在右子树插入了结点
	{
		if(tree->lchild == NULL) //若左子树不为空
		{
			if(tree->rchild->rchild != NULL) //若右子树的右子树不为空
			{
				leftRotate(tree);
				goto check;
			}
			else if(tree->rchild->lchild != NULL) //若右子树的左子树不为空
			{
				rightRotate(tree->rchild);
				leftRotate(tree);
				goto check;
			}
		}
		if(tree->rchild->rchild != NULL) //若右子树的右子树不为空
		{
			if(tree->rchild->rchild->size > tree->lchild->size) //若右子树的右子树比左子树大
			{
				leftRotate(tree);
				goto check;
			}
		}
		if(tree->rchild->lchild != NULL) //若右子树的左子树不为空
		{
			if(tree->rchild->lchild->size > tree->lchild->size) //若右子树的左子树比左子树大
			{
				rightRotate(tree->rchild);
				leftRotate(tree);
				goto check;
			}
		}
		return;
	}
	check: //若旋转过，继续进行维护
	maintain(tree->lchild, false);
	maintain(tree->rchild, true);
	maintain(tree, false);
	maintain(tree, true);
}

/**
 * 功能：查找结点
 * 参数及返回值说明：
 *     参数：tree：根结点
 *           e：待查找的值，返回时会返回已存的文档链表
 *     返回值：查找是否成功（是否已存在待查找结点）
 * 作者：王华清
 * 日期：2014年1月1日
 */
bool SBT::indexNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //若树为空
		return false;
	if(tree->data == e) //若找到元素
	{
		e = tree->data;
		return true;
	}
	if(tree->data > e) //若待查找元素小
		return indexNode(tree->lchild, e);
	if(tree->data < e) //若待查找元素大
		return indexNode(tree->rchild, e);
}

/**
 * 功能：删除结点，若不存在则删除查找到最底层的结点
 * 参数及返回值说明：
 *     参数：tree：根结点
 *           e：待删除的值
 *           r：删掉的结点
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::deleteNode(pSBTNode &tree, DocLink &e, DocLink &r)
{
	tree->size--;
	if((e == tree->data) || (e < tree->data && tree->lchild == NULL) || (e > tree->data && tree->rchild == NULL)) //若找到或已到底层
	{
		r = tree->data;
		if(tree->lchild == NULL)  //若待删除元素小
		{
			pSBTNode temp = tree;
			tree = tree->rchild;
			delete temp;
			temp = NULL;
		}
		else if(tree->rchild == NULL) //若待删除元素大
		{
			pSBTNode temp = tree;
			tree = tree->lchild;
			delete temp;
			temp = NULL;
		}
		else //若找到
			deleteNode(tree->lchild, e, tree->data);
	}
	else //若未结束
	{
		if(e < tree->data) //若待删除元素小
			deleteNode(tree->lchild, e, r);
		else //若待删除元素大
			deleteNode(tree->rchild, e, r);
	}
}

/**
 * 功能：替换结点
 * 参数及返回值说明：
 *     参数：tree：根结点
 *           e：待替换的值
 *     返回值：替换是否成功（是否已存在待替换结点）
 * 作者：王华清
 * 日期：2014年1月1日
 */
bool SBT::changeNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //若树为空
		return false;
	if(tree->data == e) //若找到元素
	{
		tree->data = e;
		return true;
	}
	if(tree->data > e) //若待替换元素小
		return changeNode(tree->lchild, e);
	if(tree->data < e) //若待替换元素大
		return changeNode(tree->rchild, e);
}

/**
 * 功能：将网页加入大小二叉平衡树倒排文档
 * 参数及返回值说明：
 *     参数：i：网页编号
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::addSBT(int i)
{
	int m, n, o, p;
	ifstream webpage;
	CharString str, file;
	Doc web;
	DocLink webinfo;
	string s;
	char* c;

	//打开网页分词结果
	m = i / 1000 + 48;
	n = i / 100 % 10 + 48;
	o = i / 10 % 10 + 48;
	p = i % 10 + 48;
	file.strAssign("Segmentation\\0001.txt\0");
	file.head->ch[13] = m;
	file.head->ch[14] = n;
	file.head->ch[15] = o;
	file.head->ch[16] = p;
	webpage.open(file.head->ch);

	if(!webpage) //若打开失败
	{
		str.destroyString();
		webinfo.docinfo.head = NULL;
		file.destroyString();
		webpage.sync();
		webpage.clear();
		webpage.close();
		return;
	}

	while(true) //文件未读完时
	{
		getline(webpage, s);
		if(s == "")
			break;
		c = (char*)s.c_str();
		str.strAssign(c);
		webinfo.docinfo.head = new(LinkedList<Doc>::LinkNode);
		webinfo.docinfo.head->next = webinfo.docinfo.head;
		webinfo.term = str;
		webinfo.df = 0;
		webinfo.occur = 0;
		if(indexNode(head, webinfo)) //若结点已存在
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			if(changeNode(head, webinfo));
		}
		else //若结点不存在
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			if(insertNode(head, webinfo));
		}
		str.destroyString();
	}
	webinfo.docinfo.head = NULL;
	file.destroyString();
	webpage.sync();
	webpage.clear();
	webpage.close();
}

/**
 * 功能：输出倒排文档
 * 参数及返回值说明：
 *     参数：tree：根结点
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::outputSBT(pSBTNode &tree)
{
	if(tree == NULL)
		return;
	tree->data.outputLink();
	outputSBT(tree->lchild);
//	tree->data.outputLink();
	outputSBT(tree->rchild);
}

/**
 * 功能：通过倒排文档建立大小二叉平衡树
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void SBT::buildSBT()
{
	ifstream webpage;
	CharString str;
	Doc web;
	DocLink webinfo;
	char c;
	int df, occur;
	webpage.open("docSBTREE.txt");
	if(!webpage) //若打开失败
	{
		str.destroyString();
		webinfo.docinfo.head = NULL;
		webpage.sync();
		webpage.clear();
		webpage.close();
		return;
	}
	while(true) //文件未读完时
	{
		webpage.get(c);
		if(c != '(')
			break;
		webpage.get(c);
		str.strAssign("\0");
		while(c < 0) //读入中文单词
		{
			str.addChar(c);
			webpage.get(c);
			str.addChar(c);
			webpage.get(c);
		}
		webinfo.docinfo.head = new(LinkedList<Doc>::LinkNode);
		webinfo.docinfo.head->next = webinfo.docinfo.head;
		webpage>>df>>occur;
		webinfo.term = str;
		webinfo.df = 0;
		webinfo.occur = 0;
		while(c != '\n')
		{
			if(c == '(') //读入文档信息
			{
				webpage>>web.head.docID>>web.head.times;
				webinfo.insertDoc(web);
			}
			webpage.get(c);
		}
		insertNode(head, webinfo); //插入结点
		str.destroyString();
	}
	webinfo.docinfo.head = NULL;
	webpage.sync();
	webpage.clear();
	webpage.close();
}