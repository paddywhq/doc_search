/*
* �ļ�����WordLibrary.h
*
* �ļ��������������ӿڵȵ������б�CharString.h\LinkedList.h\WordLibrary
*
* �ļ����ܣ�ʵ�ִʿ���
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef WORDLIBRARY_H
#define WORDLIBRARY_H

#include"CharString.h"
#include"LinkedList.h"
#include<fstream>

/**
 * ���ܣ��ʿ���
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
class WordLibrary
{
public:
	LinkedList<CharString> *dic; //�ʿ�Hash��

public:
	WordLibrary();
	~WordLibrary();

	void preMatch(char* s);
	void initWordLibrary();
	void saveWordLibrary(char* ch);
	unsigned int hash(char* s);
	bool findWord(CharString &s);
};

#endif