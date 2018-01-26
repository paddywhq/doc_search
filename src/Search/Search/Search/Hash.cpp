/*
* 文件名：Hash.cpp
*
* 文件中所包含的类或接口等的名称列表：Hash.h, LinkedList.h
*
* 文件功能：实现哈希表倒排文档函数
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
#include"Hash.h"
#include"LinkedList.h"

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
Hash::Hash()
{
	initHash();
}

/**
 * 功能：初始化
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::initHash()
{
	head = new(LinkedList<DocLink>[1000003]);
	for(int i = 0; i < 1000003; i++) //创建Hash表
	{
		head[i].initList();
	}
}

/**
 * 功能：删除哈希表
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::deleteHash()
{
	if(head == NULL)
		return;
	delete []head;
	head = NULL;
}

/**
 * 功能：插入结点
 * 参数及返回值说明：
 *     参数：e：待插入的值
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::insertNode(DocLink &e)
{
	int key = hashkey(e); //哈希值
	LinkedList<DocLink>::pLinkNode p;
	p = new(LinkedList<DocLink>::LinkNode);
	p->data = e;
	p->next = head[key].head->next;
	head[key].head->next = p;
}

/**
 * 功能：查找结点
 * 参数及返回值说明：
 *     参数：e：待插入的值
 *     返回值：是否找到
 * 作者：王华清
 * 日期：2014年1月1日
 */
bool Hash::indexNode(DocLink &e)
{
	int key = hashkey(e); //哈希值
	LinkedList<DocLink>::pLinkNode p = head[key].head->next;
	while(p != head[key].head) //若未到链表末尾
	{
		if(e == p->data) //若找到
		{
			e = p->data;
			return true;
		}
		p = p->next;
	}
	return false;
}

/**
 * 功能：更改结点
 * 参数及返回值说明：
 *     参数：e：待更改的值
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::changeNode(DocLink &e)
{
	int key = hashkey(e); //哈希值
	LinkedList<DocLink>::pLinkNode p = head[key].head->next;
	while(p != head[key].head) //若未到链表末尾
	{
		if(e == p->data) //若找到
		{
			p->data = e;
			return;
		}
		p = p->next;
	}
}

/**
 * 功能：删除结点
 * 参数及返回值说明：
 *     参数：e：待删除的值
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::deleteNode(DocLink &e)
{
	int key = hashkey(e); //哈希值
	LinkedList<DocLink>::pLinkNode p = head[key].head, q = p->next;
	while(q != head[key].head) //若未到链表末尾
	{
		if(e == q->data) //若找到
		{
			p->next = q->next;
			e = q->data;
			delete q;
			return;
		}
		p = p->next;
		q = q->next;
	}
}

/**
 * 功能：结点哈希值
 * 参数及返回值说明：
 *     参数：e：待计算的结点
 *     返回值：哈希值
 * 作者：王华清
 * 日期：2014年1月1日
 */
int Hash::hashkey(DocLink &e)
{
	unsigned int i = 0, key = 0;
	while(e.term.head->ch[i] != 0) //BKDR字符串Hash函数
	{
		key = key * 100 + abs(e.term.head->ch[i] + e.term.head->ch[i + 1]);
		key %= 1000003;
		i += 2;
	}
	return(key);
}

/**
 * 功能：将网页加入哈希表倒排文档
 * 参数及返回值说明：
 *     参数：i：网页编号
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::addHash(int i)
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
		if(indexNode(webinfo)) //若结点已存在
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			changeNode(webinfo);
		}
		else //若结点不存在
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			insertNode(webinfo);
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
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::outputHash()
{
	LinkedList<DocLink>::pLinkNode p;
	for(int i = 0; i < 1000003; i++) //对哈希表循环
	{
		p = head[i].head->next;
		while(p != head[i].head) //输入所有文档链表
		{
			p->data.outputLink();
			p = p->next;
		}
	}
}

/**
 * 功能：通过倒排文档建立哈希表
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void Hash::buildHash()
{
	ifstream webpage;
	CharString str;
	Doc web;
	DocLink webinfo;
	char c;
	int df, occur;
	webpage.open("docHash.txt");
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
		insertNode(webinfo); //插入结点
		str.destroyString();
	}
	webinfo.docinfo.head = NULL;
	webpage.sync();
	webpage.clear();
	webpage.close();
}