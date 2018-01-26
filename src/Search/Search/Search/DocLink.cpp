/*
* 文件名：DocLink.cpp
*
* 文件中所包含的类或接口等的名称列表：DocLink.h, Doc.h, LinkedList.h, CharString.h
*
* 文件功能：实现文档链表类函数
*
* 作者：王华清
*
* 日期：2014年1月1日
*/
#include "StdAfx.h"
#include<iostream>
#include<fstream>
using namespace std;
#include "DocLink.h"
#include "Doc.h"
#include "LinkedList.h"
#include "CharString.h"

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
DocLink::DocLink()
{
	initDocLink();
}

/**
 * 功能：析构函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
DocLink::~DocLink()
{
	destroyDocLink();
}

/**
 * 功能：初始化函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::initDocLink()
{
	term.initString();
	df = 0;
	occur = 0;
	docinfo.initList();
}

/**
 * 功能：清除函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::clearDocLink()
{
	term.clearString();
	df = 0;
	occur = 0;
	docinfo.clearList();
}

/**
 * 功能：删除函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::destroyDocLink()
{
	term.destroyString();
	df = -1;
	occur = 0;
	docinfo.destroyList();
}

/**
 * 功能：插入函数
 * 参数及返回值说明：
 *     参数：e：待插入的元素
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::insertDoc(Doc &e)
{
	if(docinfo.head == NULL) //若文档链表未初始化
		return;
	LinkedList<Doc>::pLinkNode p = docinfo.head, q = p->next;
	while(true)
	{
		if(q == docinfo.head) //若查找至末尾
			break;
		if(q->data.head.docID == e.head.docID) //若已存在
		{
			//修改结点并移至恰当位置
			df--;
			occur -= q->data.head.times;
			q->data.head.times += e.head.times;
			p->next = q->next;
			insertDoc(q->data);
			delete q;
			return;
		}
		p = p->next;
		q = q->next;
	}
	p = docinfo.head;
	q = p->next;
	while(true)
	{
		if(q == docinfo.head) //若到末尾
			break;
		if(q->data.head.times >= e.head.times) //若找到插入处
			break;
		p = p->next;
		q = q->next;
	}

	//加入新结点
	q = new(LinkedList<Doc>::LinkNode);
	q->data = e;
	q->next = p->next;
	p->next = q;
	df++;
	occur += e.head.times;
}

/**
 * 功能：查找函数
 * 参数及返回值说明：
 *     参数：id：查找编号
 *           e：返回结点值
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::indexDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //若未初始化
	{
		e.head.docID = 0;
		e.head.times = 0;
		return;
	}
	LinkedList<Doc>::pLinkNode p = docinfo.head->next;
	while(true)
	{
		if(p == docinfo.head) //若找到末尾
			break;
		if(p->data.head.docID == id) //若找到
		{
			e = p->data;
			return;
		}
		p = p->next;
	}

	//若未找到
	e.head.docID = 0;
	e.head.times = 0;
}

/**
 * 功能：删除函数
 * 参数及返回值说明：
 *     参数：id：待删除的编号
 *           e：返回删除的元素
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::deleteDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //若未初始化
	{
		e.head.docID = 0;
		e.head.times = 0;
		return;
	}
	LinkedList<Doc>::pLinkNode p = docinfo.head, q = p->next;
	while(true)
	{
		if(q == docinfo.head) //若到末尾
			break;
		if(q->data.head.docID == id) //若找到
		{
			occur -= q->data.head.times;
			df--;
			e = q->data;
			p->next = q->next;
			delete q;
			return;
		}
		p = p->next;
		q = q->next;
	}
	e.head.docID = 0;
	e.head.times = 0;
}

/**
 * 功能：修改函数
 * 参数及返回值说明：
 *     参数：id：待修改的编号
 *           e：修改为的元素
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::changeDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //若为初始化
		return;
	LinkedList<Doc>::pLinkNode p = docinfo.head;
	Doc temp;
	while(true)
	{
		if(p == docinfo.head) //若到末尾
			break;
		if(p->data.head.docID == id) //若找到
		{
			deleteDoc(id, temp);
			if(temp.head.docID != 0)
				insertDoc(e);
			return;
		}
		p = p->next;
	}
}

/**
 * 功能：输出函数
 * 参数及返回值说明：
 *     参数：id：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void DocLink::outputLink()
{
	ofstream output;
	output.open("doc.txt", ios::app);
	output<<"(";
	for(int i = 0; i < term.head->length; i++)
		output<<term.head->ch[i];
	output<<" "<<df<<" "<<occur<<")";
	LinkedList<Doc>::pLinkNode p = docinfo.head->next;
	while(true) //输出文档链表
	{
		if(p == docinfo.head)
			break;
		output<<" ("<<p->data.head.docID<<" "<<p->data.head.times<<")";
		p = p->next;
	}
	output<<endl;
	output.clear();
	output.close();
}