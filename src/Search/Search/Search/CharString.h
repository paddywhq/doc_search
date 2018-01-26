/*
* �ļ�����CharString.h
*
* �ļ��������������ӿڵȵ������б�CharString
*
* �ļ����ܣ�ʵ���ַ�����
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef CHARSTRING_H
#define CHARSTRING_H

/**
 * ���ܣ��ַ�����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
class CharString
{
public:
	//�ַ����ṹ��������
	typedef struct{
		char *ch; //�ַ���
		int length; //�ַ�������
	}HString, *pHString;

public:
	pHString head; //�ַ���ָ��

public:
	CharString();
	~CharString();

	void initString();
	void initString(char *s);
	void strAssign(char* s);
	void destroyString();
	void strCopy(CharString &s);
	int strLength();
	int strCompare(CharString &s);
	void concat(CharString s1, CharString s2);
	bool strEmpty();
	void subString(int pos, int len, CharString &s);
	void clearString();
	int index(CharString &s);
	int index(CharString &s, int pos);
	void strDelete(int pos, int len);
	void strInsert(int pos, CharString s);
	void replace(CharString s, CharString t);
	void operator = (int s){if(s == 0) head = NULL;} //�ã��ַ����� = 0�����������
	void operator = (CharString &s){strCopy(s);} //�ַ����ำֵ
	bool operator == (CharString &s){return(strCompare(s) == 0);} //�Ƚ��ַ������
	bool operator >= (CharString &s){return(strCompare(s) >= 0);} //�Ƚ��ַ���
	bool operator <= (CharString &s){return(strCompare(s) <= 0);} //�Ƚ��ַ���
	bool operator > (CharString &s){return(strCompare(s) > 0);} //�Ƚ��ַ���
	bool operator < (CharString &s){return(strCompare(s) < 0);} //�Ƚ��ַ���
	bool operator != (CharString &s){return(strCompare(s) != 0);} //�Ƚ��ַ���
	void addChar(char c);
};

#endif