/*
* �ļ�����DocLink.cpp
*
* �ļ��������������ӿڵȵ������б�DocLink.h, Doc.h, LinkedList.h, CharString.h
*
* �ļ����ܣ�ʵ���ĵ������ຯ��
*
* ���ߣ�������
*
* ���ڣ�2014��1��1��
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
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
DocLink::DocLink()
{
	initDocLink();
}

/**
 * ���ܣ���������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
DocLink::~DocLink()
{
	destroyDocLink();
}

/**
 * ���ܣ���ʼ������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::initDocLink()
{
	term.initString();
	df = 0;
	occur = 0;
	docinfo.initList();
}

/**
 * ���ܣ��������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::clearDocLink()
{
	term.clearString();
	df = 0;
	occur = 0;
	docinfo.clearList();
}

/**
 * ���ܣ�ɾ������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::destroyDocLink()
{
	term.destroyString();
	df = -1;
	occur = 0;
	docinfo.destroyList();
}

/**
 * ���ܣ����뺯��
 * ����������ֵ˵����
 *     ������e���������Ԫ��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::insertDoc(Doc &e)
{
	if(docinfo.head == NULL) //���ĵ�����δ��ʼ��
		return;
	LinkedList<Doc>::pLinkNode p = docinfo.head, q = p->next;
	while(true)
	{
		if(q == docinfo.head) //��������ĩβ
			break;
		if(q->data.head.docID == e.head.docID) //���Ѵ���
		{
			//�޸Ľ�㲢����ǡ��λ��
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
		if(q == docinfo.head) //����ĩβ
			break;
		if(q->data.head.times >= e.head.times) //���ҵ����봦
			break;
		p = p->next;
		q = q->next;
	}

	//�����½��
	q = new(LinkedList<Doc>::LinkNode);
	q->data = e;
	q->next = p->next;
	p->next = q;
	df++;
	occur += e.head.times;
}

/**
 * ���ܣ����Һ���
 * ����������ֵ˵����
 *     ������id�����ұ��
 *           e�����ؽ��ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::indexDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //��δ��ʼ��
	{
		e.head.docID = 0;
		e.head.times = 0;
		return;
	}
	LinkedList<Doc>::pLinkNode p = docinfo.head->next;
	while(true)
	{
		if(p == docinfo.head) //���ҵ�ĩβ
			break;
		if(p->data.head.docID == id) //���ҵ�
		{
			e = p->data;
			return;
		}
		p = p->next;
	}

	//��δ�ҵ�
	e.head.docID = 0;
	e.head.times = 0;
}

/**
 * ���ܣ�ɾ������
 * ����������ֵ˵����
 *     ������id����ɾ���ı��
 *           e������ɾ����Ԫ��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::deleteDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //��δ��ʼ��
	{
		e.head.docID = 0;
		e.head.times = 0;
		return;
	}
	LinkedList<Doc>::pLinkNode p = docinfo.head, q = p->next;
	while(true)
	{
		if(q == docinfo.head) //����ĩβ
			break;
		if(q->data.head.docID == id) //���ҵ�
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
 * ���ܣ��޸ĺ���
 * ����������ֵ˵����
 *     ������id�����޸ĵı��
 *           e���޸�Ϊ��Ԫ��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void DocLink::changeDoc(int &id, Doc &e)
{
	if(docinfo.head == NULL) //��Ϊ��ʼ��
		return;
	LinkedList<Doc>::pLinkNode p = docinfo.head;
	Doc temp;
	while(true)
	{
		if(p == docinfo.head) //����ĩβ
			break;
		if(p->data.head.docID == id) //���ҵ�
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
 * ���ܣ��������
 * ����������ֵ˵����
 *     ������id����
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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
	while(true) //����ĵ�����
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