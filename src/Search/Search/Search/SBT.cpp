/*
* �ļ�����SBT.cpp
*
* �ļ��������������ӿڵȵ������б�SBT.h, LinkedList.h
*
* �ļ����ܣ�ʵ�ִ�С����ƽ���������ĵ�����
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
#include"SBT.h"
#include"LinkedList.h"

/**
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
* ���ڣ�2014��1��1��
 */
SBT::SBT()
{
	head = NULL;
}

/**
 * ���ܣ���������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
SBT::~SBT()
{
	deleteSBT(head);
}

/**
 * ���ܣ���ʼ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::initSBT()
{
	deleteSBT(head); //ɾ����
}

/**
 * ���ܣ�ɾ��ƽ����
 * ����������ֵ˵����
 *     ������tree�������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::deleteSBT(pSBTNode &tree)
{
	if(tree == NULL) //��Ϊ��ʱ�˳�
		return;
	deleteSBT(tree->lchild); //ɾ��������
	deleteSBT(tree->rchild); //ɾ��������
	delete tree; //ɾ�������
	tree = NULL;
}

/**
 * ���ܣ�����
 * ����������ֵ˵����
 *     ������tree�������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::leftRotate(pSBTNode &tree)
{
	pSBTNode temp;

	//��������
	temp = tree->rchild;
	tree->rchild = temp->lchild;
	temp->lchild = tree;
	tree = temp;

	//�޸�����������С
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
 * ���ܣ�����
 * ����������ֵ˵����
 *     ������tree�������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::rightRotate(pSBTNode &tree)
{
	pSBTNode temp;

	//��������
	temp = tree->lchild;
	tree->lchild = temp->rchild;
	temp->rchild = tree;
	tree = temp;

	//�޸�����������С
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
 * ���ܣ�������
 * ����������ֵ˵����
 *     ������tree�������
 *           e���������ֵ
 *     ����ֵ�������Ƿ�ɹ����Ƿ��Ѵ��ڴ������㣩
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
bool SBT::insertNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //����Ϊ�գ������½��
	{
		tree = new(SBTNode);
		tree->lchild = NULL;
		tree->rchild = NULL;
		tree->size = 1;
		tree->data = e;
		return true;
	}
	else //������Ϊ��
	{
		if(tree->data > e) //��������Ԫ��С
		{
			if(insertNode(tree->lchild, e)) //������ɹ�
			{
				tree->size++; //�޸�����С
				maintain(tree, e > tree->data); //ƽ��ά��
				return true;
			}
			return false;
		}
		else if(tree->data < e) //��������Ԫ�ش�
		{
			if(insertNode(tree->rchild, e)) //������ɹ�
			{
				tree->size++; //�޸�����С
				maintain(tree, e > tree->data); //ƽ��ά��
				return true;
			}
			return false;
		}
		else //���Ѵ��ڴ�����Ԫ�أ�������
			return false;
	}
}

/**
 * ���ܣ�ƽ��ά��
 * ����������ֵ˵����
 *     ������tree�������
 *           flag�������������������������㵼����Ҫά��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::maintain(pSBTNode &tree, bool flag)
{
	if(tree->size <= 2) //����ά��
		return;
	if(flag == false) //�������������˽��
	{
		if(tree->rchild == NULL) //��������Ϊ��
		{
			if(tree->lchild->lchild != NULL) //������������������Ϊ��
			{
				rightRotate(tree);
				goto check;
			}
			else if(tree->lchild->rchild != NULL) //������������������Ϊ��
			{
				leftRotate(tree->lchild);
				rightRotate(tree);
				goto check;
			}
		}
		if(tree->lchild->lchild != NULL) //������������������Ϊ��
		{
			if(tree->lchild->lchild->size > tree->rchild->size) //��������������������������
			{
				rightRotate(tree);
				goto check;
			}
		}
		if(tree->lchild->rchild != NULL) //������������������Ϊ��
		{
			if(tree->lchild->rchild->size > tree->rchild->size) //��������������������������
			{
				leftRotate(tree->lchild);
				rightRotate(tree);
				goto check;
			}
		}
		return;
	}
	else if(flag == true) //�������������˽��
	{
		if(tree->lchild == NULL) //����������Ϊ��
		{
			if(tree->rchild->rchild != NULL) //������������������Ϊ��
			{
				leftRotate(tree);
				goto check;
			}
			else if(tree->rchild->lchild != NULL) //������������������Ϊ��
			{
				rightRotate(tree->rchild);
				leftRotate(tree);
				goto check;
			}
		}
		if(tree->rchild->rchild != NULL) //������������������Ϊ��
		{
			if(tree->rchild->rchild->size > tree->lchild->size) //��������������������������
			{
				leftRotate(tree);
				goto check;
			}
		}
		if(tree->rchild->lchild != NULL) //������������������Ϊ��
		{
			if(tree->rchild->lchild->size > tree->lchild->size) //��������������������������
			{
				rightRotate(tree->rchild);
				leftRotate(tree);
				goto check;
			}
		}
		return;
	}
	check: //����ת������������ά��
	maintain(tree->lchild, false);
	maintain(tree->rchild, true);
	maintain(tree, false);
	maintain(tree, true);
}

/**
 * ���ܣ����ҽ��
 * ����������ֵ˵����
 *     ������tree�������
 *           e�������ҵ�ֵ������ʱ�᷵���Ѵ���ĵ�����
 *     ����ֵ�������Ƿ�ɹ����Ƿ��Ѵ��ڴ����ҽ�㣩
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
bool SBT::indexNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //����Ϊ��
		return false;
	if(tree->data == e) //���ҵ�Ԫ��
	{
		e = tree->data;
		return true;
	}
	if(tree->data > e) //��������Ԫ��С
		return indexNode(tree->lchild, e);
	if(tree->data < e) //��������Ԫ�ش�
		return indexNode(tree->rchild, e);
}

/**
 * ���ܣ�ɾ����㣬����������ɾ�����ҵ���ײ�Ľ��
 * ����������ֵ˵����
 *     ������tree�������
 *           e����ɾ����ֵ
 *           r��ɾ���Ľ��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void SBT::deleteNode(pSBTNode &tree, DocLink &e, DocLink &r)
{
	tree->size--;
	if((e == tree->data) || (e < tree->data && tree->lchild == NULL) || (e > tree->data && tree->rchild == NULL)) //���ҵ����ѵ��ײ�
	{
		r = tree->data;
		if(tree->lchild == NULL)  //����ɾ��Ԫ��С
		{
			pSBTNode temp = tree;
			tree = tree->rchild;
			delete temp;
			temp = NULL;
		}
		else if(tree->rchild == NULL) //����ɾ��Ԫ�ش�
		{
			pSBTNode temp = tree;
			tree = tree->lchild;
			delete temp;
			temp = NULL;
		}
		else //���ҵ�
			deleteNode(tree->lchild, e, tree->data);
	}
	else //��δ����
	{
		if(e < tree->data) //����ɾ��Ԫ��С
			deleteNode(tree->lchild, e, r);
		else //����ɾ��Ԫ�ش�
			deleteNode(tree->rchild, e, r);
	}
}

/**
 * ���ܣ��滻���
 * ����������ֵ˵����
 *     ������tree�������
 *           e�����滻��ֵ
 *     ����ֵ���滻�Ƿ�ɹ����Ƿ��Ѵ��ڴ��滻��㣩
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
bool SBT::changeNode(pSBTNode &tree, DocLink &e)
{
	if(tree == NULL) //����Ϊ��
		return false;
	if(tree->data == e) //���ҵ�Ԫ��
	{
		tree->data = e;
		return true;
	}
	if(tree->data > e) //�����滻Ԫ��С
		return changeNode(tree->lchild, e);
	if(tree->data < e) //�����滻Ԫ�ش�
		return changeNode(tree->rchild, e);
}

/**
 * ���ܣ�����ҳ�����С����ƽ���������ĵ�
 * ����������ֵ˵����
 *     ������i����ҳ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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
		if(indexNode(head, webinfo)) //������Ѵ���
		{
			web.head.docID = i;
			web.head.times = 1;
			webinfo.insertDoc(web);
			if(changeNode(head, webinfo));
		}
		else //����㲻����
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
 * ���ܣ���������ĵ�
 * ����������ֵ˵����
 *     ������tree�������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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
 * ���ܣ�ͨ�������ĵ�������С����ƽ����
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
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
		insertNode(head, webinfo); //������
		str.destroyString();
	}
	webinfo.docinfo.head = NULL;
	webpage.sync();
	webpage.clear();
	webpage.close();
}