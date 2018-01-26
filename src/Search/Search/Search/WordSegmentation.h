/*
* �ļ�����WordSegmentation.h
*
* �ļ��������������ӿڵȵ������б�CharString.h\LinkedList.h\WordLibrary.h\Stack.h\WordSegmentation
*
* �ļ����ܣ�ʵ����ҳ������
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

#include"WordLibrary.h"
#include"CharString.h"
#include"LinkedList.h"
#include"Stack.h"
#include<fstream>

/**
 * ���ܣ���ҳ������
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
class WordSegmentation
{
public:
	Stack<CharString> html; //��ҳ����ջ
	WordLibrary	dic, stop; //��ҳ�����ʿ�
	LinkedList<CharString> word; //��ҳ�����������
	
public:
	WordSegmentation();
	~WordSegmentation();

	void htmlParse();
	void pickOutHtmlMainBody(char* chin, char* chout);
	void wordSegmentation(char* ch);
	void segmentation(CharString &s);
	void outputWord(char* ch);
	void addWordLibrary();
};

#endif