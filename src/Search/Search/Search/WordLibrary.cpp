/*
* �ļ�����WordLibrary.cpp
*
* �ļ��������������ӿڵȵ������б�WordLibrary.h/CharString.h/LinkedList.h
*
* �ļ����ܣ�ʵ�ִʿ⺯��
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#include "StdAfx.h"
#include<iostream>
#include"WordLibrary.h"
#include"CharString.h"
#include"LinkedList.h"
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

/**
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
WordLibrary::WordLibrary()
{
	initWordLibrary();
}

WordLibrary::~WordLibrary()
{
	for(int i = 0; i < 1000003; i++) //����Hash��
	{
		dic[i].destroyList();
	}
	delete []dic;
}


/**
 * ���ܣ��ѷִʴʿ������ڴ�
 * ����������ֵ˵����
 *     ������s���ʵ�·��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void WordLibrary::preMatch(char* s)
{
	saveWordLibrary(s); //���شʿ�
}

/**
 * ���ܣ���ʼ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void WordLibrary::initWordLibrary()
{
	dic = new(LinkedList<CharString>[1000003]);
	for(int i = 0; i < 1000003; i++) //����Hash��
	{
		dic[i].initList();
	}
}

/**
 * ���ܣ��ѷִʴʿ����Hash��
 * ����������ֵ˵����
 *     ������ch���ʿ�·����
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void WordLibrary::saveWordLibrary(char* ch)
{
	ifstream wordlibrary;
	wordlibrary.open(ch);
	string s;
	CharString str;
	int hashkey; //Hashֵ
	while(!wordlibrary.eof()) //�ļ�δ����ʱ
	{
		str.destroyString();
		getline(wordlibrary, s);
		char* ch = (char*)s.c_str();
		str.strAssign(ch);
		hashkey = hash(ch); //����Hashֵ
		dic[hashkey].listInsert(1, str); //�ڶ�ӦHashֵ�����д������
//		delete []ch;
	}
	wordlibrary.sync();
	wordlibrary.clear();
	wordlibrary.close();
}

/**
 * ���ܣ�����Hashֵ
 * ����������ֵ˵����
 *     ������s������
 *     ����ֵ��Hashֵ
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
unsigned int WordLibrary::hash(char* s)
{
	unsigned int i = 0, key = 0;
	while(s[i] != 0) //BKDR�ַ���Hash����
	{
		key = key * 13131 + abs(s[i] + s[i + 1]);
		key %= 1000003;
		i += 2;
	}
	return(key);
}

/**
 * ���ܣ�����Hashֵ
 * ����������ֵ˵����
 *     ������s������
 *     ����ֵ��true�ڴʵ��У�false���ڴʵ���
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
bool WordLibrary::findWord(CharString &s)
{
	int hashkey = hash(s.head->ch); //Hashֵ
	return(dic[hashkey].locateElem(s) > 0);
}