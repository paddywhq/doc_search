/*
* 文件名：Hash.h
*
* 文件中所包含的类或接口等的名称列表：DocLink.h, Hash
*
* 文件功能：实现哈希表倒排文档
*
* 作者：王华清
*
* 日期：2014年1月1日
*/
#ifndef HASH_H
#define HASH_H
#include "DocLink.h"
#include <iostream>

/**
 * 功能：哈希表文档链表
 * 作者：王华清
 * 日期：2013年11月24日
 */
class Hash
{
public:
	LinkedList<DocLink> *head; //哈希桶

public:
	Hash();

	void initHash();
	void deleteHash();
	void insertNode(DocLink &e);
	bool indexNode(DocLink &e);
	void changeNode(DocLink &e);
	void deleteNode(DocLink &e);
	int hashkey(DocLink &e);
	void addHash(int i);
	void outputHash();
	void buildHash();
};

#endif