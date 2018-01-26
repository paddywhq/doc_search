/*
* �ļ�����CharString.cpp
*
* �ļ��������������ӿڵȵ������б�CharString.h
*
* �ļ����ܣ�ʵ���ַ����ຯ��
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#include "StdAfx.h"
#include<iostream>
using namespace std;
#include"CharString.h"

/**
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
CharString::CharString()
{
	head = NULL;
}

/**
 * ���ܣ���������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
CharString::~CharString()
{
	destroyString();
}

/**
 * ���ܣ���ʼ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::initString()
{
	destroyString(); //ɾ��ԭ�ַ���
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
}

/**
 * ���ܣ���ʼ������ֵ
 * ����������ֵ˵����
 *     ������s����ʼ��Ҫ����ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::initString(char* s)
{
	destroyString(); //ɾ��ԭ�ַ���
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
	strAssign(s); //��ֵΪs
}

/**
 * ���ܣ���ֵ
 * ����������ֵ˵����
 *     ������s��Ҫ����ֵ
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::strAssign(char* s)
{
	int i = 0; //������
	while(s[i] != 0) //��s�ĳ���
		i++;
	if(head == NULL) //��ָ��Ϊ�ճ�ʼ���ַ���
		initString();
	delete []head->ch; //ɾ��ԭ�ַ���
	head->ch = new(char[i + 1]); //�����¿ռ�
	head->length = i; //������ֵ
	for(i = 0; i < head->length; i++) //��ֵ
		head->ch[i] = s[i];
	head->ch[head->length] = '\0';
}

/**
 * ���ܣ�ɾ���ַ���
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::destroyString()
{
	if(head == NULL) //ָ�벻Ϊ��ʱ���в���
		return;
	delete []head->ch;
	head->ch = NULL;
	head->length = 0;
	delete head;
	head = NULL;
}

/**
 * ���ܣ������ַ���
 * ����������ֵ˵����
 *     ������s�������Ƶ��ַ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::strCopy(CharString &s)
{
	if(s.head == NULL) //�������Ƶ��ַ���Ϊ��
		destroyString(); //ɾ���ַ���
	else
		strAssign(s.head->ch); //��ֵ
}

/**
 * ���ܣ����ַ�������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ���ַ�������
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
int CharString::strLength()
{
	if(head == NULL) //�ַ���Ϊ��ʱ����-1
		return -1;
	return head->length;
}

/**
 * ���ܣ��Ƚ��ַ���
 * ����������ֵ˵����
 *     ������s����֮�Ƚϵ��ַ���
 *     ����ֵ��1����ǰ�ַ�����
 *             -1����ǰ�ַ���С
 *             0���ַ������
 *             ���ַ����Ƚ�ʱ�Ƚϵ�һλ��ͬ���ַ���
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
int CharString::strCompare(CharString &s)
{
	if(head == NULL && s.head == NULL)  //��Ϊ��
		return 0;
	if(head == NULL) //��ǰ�ַ���Ϊ��
		return -1;
	if(s.head == NULL) //�Ƚ϶���Ϊ��
		return 1;
	int i = 0; //������
	while(head->ch[i] == s.head->ch[i] &&
		head->ch[i] != '\0' && s.head->ch[i] != '\0') //�ַ�������ַ���δ����ʱ
	{
		i++;
	}
	if(head->ch[i] == s.head->ch[i]) //ͬʱ����
		return 0;
	else if(head->ch[i] - s.head->ch[i] > 0) //��ǰ�ַ����ַ���
		return 1;
	else //��ǰ�ַ����ַ�С
		return -1;
}

/**
 * ���ܣ������ַ���
 * ����������ֵ˵����
 *     ������s1���ַ���1
 *           s2���ַ���2
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::concat(CharString s1, CharString s2)
{
	int i = 0;
	if(head == NULL) //��ǰ�ַ���Ϊ��
		initString();
	if(s1.head == NULL) //�ַ���s1Ϊ��
		s1.initString();
	if(s2.head == NULL) //�ַ���s2Ϊ��
		s2.initString();
	delete []head->ch; //ɾ��ԭ�ַ���
	head->ch = new(char[s1.head->length + s2.head->length + 1]); //�����¿ռ�
	head->length = s1.head->length + s2.head->length; //������ֵ
	for(i = 0; i < s1.head->length; i++) //��s1ֵ
		head->ch[i] = s1.head->ch[i];
	for(i = s1.head->length; i < s1.head->length + s2.head->length; i++) //��s2ֵ
		head->ch[i] = s2.head->ch[i - s1.head->length];
	head->ch[head->length] = '\0';
}

/**
 * ���ܣ��ַ����п�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ��trueΪ�գ�false��Ϊ��
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
bool CharString::strEmpty()
{
	if(head == NULL)
		return true;
	if(head->length == 0)
		return true;
	return false;
}

/**
 * ���ܣ���ȡ�ַ���
 * ����������ֵ˵����
 *     ������pos����ȡ��ʼλ��
 *           len����ȡ����
 *     ����ֵ����ȡ���ַ���
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::subString(int pos, int len, CharString &s)
{
	int i = 0; //������
	if(head == NULL) //�ַ�����Ϊ��ʱ���в���
	{
		s = NULL;
		return;
	}
	if(head->length < pos + len || pos < 0) //����ȡ�ַ�������ʱ���в���
	{
		s = NULL;
		return;
	}
	s.destroyString();
	s.head = new(HString); //�����¿ռ�
	s.head->ch = new(char[len + 1]); //�����¿ռ�
	s.head->length = len; //������ֵ
	for(i = 0; i < len; i++) //��ֵ
		s.head->ch[i] = head->ch[pos + i];
	s.head->ch[len] = '\0';
}

/**
 * ���ܣ�����ַ���
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::clearString()
{
	destroyString(); //ɾ��ԭ�ַ���
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
}

/**
 * ���ܣ������ַ���
 * ����������ֵ˵����
 *     ������s�������ҵ��ַ���
 *     ����ֵ���ҵ��ַ�����ʼλ��
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
int CharString::index(CharString &s)
{
	if(head == NULL) //�ַ���Ϊ�շ���-1
		return -1;
	int i, j = 1, k = 0, *next; //������

	//����next[]ֵ
	next = new(int[s.head->length + 1]);
	for(i = 0; i < s.head->length; i++)
		next[i] = 0;
	while(j < s.head->length)
	{
		if(k == 0 || s.head->ch[j - 1] == s.head->ch[k - 1])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}

	//KMP�㷨
	i = 0, j = 1;
	while (i <= head->length && j <= s.head->length)
	{
		if(j == 0 || head->ch[i - 1] == s.head->ch[j - 1])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	delete []next;
	if(j > s.head->length) //�ҵ��ַ���
		return(i - s.head->length - 1);
	else //δ�ҵ��ַ���
		return -1;
}

/**
 * ���ܣ������ַ���
 * ����������ֵ˵����
 *     ������s�������ҵ��ַ���
 *           pos��������ʼλ��
 *     ����ֵ���ҵ��ַ�����ʼλ��
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
int CharString::index(CharString &s, int pos)
{
	if(head == NULL)  //�ַ���Ϊ�շ���-1
		return -1;
	int i, j = 1, k = 0, *next; //������

	//����next[]ֵ
	next = new(int[s.head->length + 1]);
	for(i = 0; i < s.head->length; i++)
		next[i] = 0;
	while(j < s.head->length)
	{
		if(k == 0 || s.head->ch[j - 1] == s.head->ch[k - 1])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}

	//KMP�㷨
	i = pos, j = 1;
	while (i <= head->length && j <= s.head->length)
	{
		if(j == 0 || head->ch[i - 1] == s.head->ch[j - 1])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	delete []next;
	if(j > s.head->length) //�ҵ��ַ���
		return(i - s.head->length - 1);
	else //δ�ҵ��ַ���
		return -1;
}

/**
 * ���ܣ�ɾ�������ַ���
 * ����������ֵ˵����
 *     ������pos��ɾ����ʼλ��
 *           len��ɾ������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::strDelete(int pos, int len)
{
	CharString p, q;
	subString(0, pos, p);
	subString(pos + len, head->length - pos - len, q);
	concat(p, q);
	p = NULL;
	q = NULL;
}

/**
 * ���ܣ������ַ���
 * ����������ֵ˵����
 *     ������pos��������ʼλ��
 *           s����������ַ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::strInsert(int pos, CharString s)
{
	CharString temp, p, q;
	subString(0, pos, p);
	temp.concat(p, s);
	subString(pos, head->length - pos, q);
	concat(temp, q);
}

/**
 * ���ܣ��滻�ַ���
 * ����������ֵ˵����
 *     ������s�������ַ���
 *           t���滻�ַ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::replace(CharString s, CharString t)
{
	int i = 0; //������
	while(true)
	{
		i = index(s, i);
		if(i == -1) //�Ҳ���s������
			return;
		strDelete(i, s.head->length);
		strInsert(i, t);
		i += t.head->length;
	}
}

/**
 * ���ܣ����ַ������һ���ַ�
 * ����������ֵ˵����
 *     ������c����������ַ�
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void CharString::addChar(char c)
{
	if(head == NULL) //�ַ���Ϊ��ʱ��ʼ��
		initString();
	head->length++; //����+1
	head->ch = (char*)realloc(head->ch, (head->length + 1) * sizeof(char)); //����ռ�
	head->ch[head->length - 1] = c; //��ֵ
	head->ch[head->length] = '\0';
}