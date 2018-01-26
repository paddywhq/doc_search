/*
* �ļ�����Hash.cpp
*
* �ļ��������������ӿڵȵ������б�Hash.h, LinkedList.h
*
* �ļ����ܣ�ʵ�ֹ�ϣ�����ĵ�����
*
* ���ߣ�������
*
* ���ڣ�2014��1��1��
*/
#include "StdAfx.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include"Hash.h"
#include"LinkedList.h"

/**
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
Hash::Hash()
{
	initHash();
}

/**
 * ���ܣ���ʼ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::initHash()
{
	head = new(LinkedList<DocLink>[1000003]);
	for(int i = 0; i < 1000003; i++) //����Hash��
	{
		head[i].initList();
	}
}

/**
 * ���ܣ�ɾ����ϣ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::deleteHash()
{
	if(head == NULL)
		return;
	delete []head;
	head = NULL;
}

/**
 * ���ܣ�������
 * ����������ֵ˵����
 *     ������e���������ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::insertNode(DocLink &e)
{
	int key = hashkey(e); //��ϣֵ
	LinkedList<DocLink>::pLinkNode p;
	p = new(LinkedList<DocLink>::LinkNode);
	p->data = e;
	p->next = head[key].head->next;
	head[key].head->next = p;
}

/**
 * ���ܣ����ҽ��
 * ����������ֵ˵����
 *     ������e���������ֵ
 *     ����ֵ���Ƿ��ҵ�
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
bool Hash::indexNode(DocLink &e)
{
	int key = hashkey(e); //��ϣֵ
	LinkedList<DocLink>::pLinkNode p = head[key].head->next;
	while(p != head[key].head) //��δ������ĩβ
	{
		if(e == p->data) //���ҵ�
		{
			e = p->data;
			return true;
		}
		p = p->next;
	}
	return false;
}

/**
 * ���ܣ����Ľ��
 * ����������ֵ˵����
 *     ������e�������ĵ�ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::changeNode(DocLink &e)
{
	int key = hashkey(e); //��ϣֵ
	LinkedList<DocLink>::pLinkNode p = head[key].head->next;
	while(p != head[key].head) //��δ������ĩβ
	{
		if(e == p->data) //���ҵ�
		{
			p->data = e;
			return;
		}
		p = p->next;
	}
}

/**
 * ���ܣ�ɾ�����
 * ����������ֵ˵����
 *     ������e����ɾ����ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::deleteNode(DocLink &e)
{
	int key = hashkey(e); //��ϣֵ
	LinkedList<DocLink>::pLinkNode p = head[key].head, q = p->next;
	while(q != head[key].head) //��δ������ĩβ
	{
		if(e == q->data) //���ҵ�
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
 * ���ܣ�����ϣֵ
 * ����������ֵ˵����
 *     ������e��������Ľ��
 *     ����ֵ����ϣֵ
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
int Hash::hashkey(DocLink &e)
{
	unsigned int i = 0, key = 0;
	while(e.term.head->ch[i] != 0) //BKDR�ַ���Hash����
	{
		key = key * 100 + abs(e.term.head->ch[i] + e.term.head->ch[i + 1]);
		key %= 1000003;
		i += 2;
	}
	return(key);
}

/**
 * ���ܣ�����ҳ�����ϣ�����ĵ�
 * ����������ֵ˵����
 *     ������i����ҳ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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

	//����ҳ�ִʽ��
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
	
	if(!webpage) //����ʧ��
	{
		str.destroyString();
		webinfo.docinfo.head = NULL;
		file.destroyString();
		webpage.sync();
		webpage.clear();
		webpage.close();
		return;
	}

	while(true) //�ļ�δ����ʱ
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
		if(indexNode(webinfo)) //������Ѵ���
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			changeNode(webinfo);
		}
		else //����㲻����
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
 * ���ܣ���������ĵ�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void Hash::outputHash()
{
	LinkedList<DocLink>::pLinkNode p;
	for(int i = 0; i < 1000003; i++) //�Թ�ϣ��ѭ��
	{
		p = head[i].head->next;
		while(p != head[i].head) //���������ĵ�����
		{
			p->data.outputLink();
			p = p->next;
		}
	}
}

/**
 * ���ܣ�ͨ�������ĵ�������ϣ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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
	if(!webpage) //����ʧ��
	{
		str.destroyString();
		webinfo.docinfo.head = NULL;
		webpage.sync();
		webpage.clear();
		webpage.close();
		return;
	}
	while(true) //�ļ�δ����ʱ
	{
		webpage.get(c);
		if(c != '(')
			break;
		webpage.get(c);
		str.strAssign("\0");
		while(c < 0) //�������ĵ���
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
			if(c == '(') //�����ĵ���Ϣ
			{
				webpage>>web.head.docID>>web.head.times;
				webinfo.insertDoc(web);
			}
			webpage.get(c);
		}
		insertNode(webinfo); //������
		str.destroyString();
	}
	webinfo.docinfo.head = NULL;
	webpage.sync();
	webpage.clear();
	webpage.close();
}