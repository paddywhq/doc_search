/*
* �ļ�����Hash.h
*
* �ļ��������������ӿڵȵ������б�DocLink.h, Hash
*
* �ļ����ܣ�ʵ�ֹ�ϣ�����ĵ�
*
* ���ߣ�������
*
* ���ڣ�2014��1��1��
*/
#ifndef HASH_H
#define HASH_H
#include "DocLink.h"
#include <iostream>

/**
 * ���ܣ���ϣ���ĵ�����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
class Hash
{
public:
	LinkedList<DocLink> *head; //��ϣͰ

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