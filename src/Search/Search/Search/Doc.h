/*
* �ļ�����Doc.h
*
* �ļ��������������ӿڵȵ������б�Doc
*
* �ļ����ܣ�ʵ���ĵ���
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef DOC_H
#define DOC_H

/**
 * ���ܣ��ĵ���
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
class Doc
{
public:
	//�ĵ��ṹ��������
	typedef struct{
		int docID; //��ҳ���
		int times; //���ִ���
	}Document;

public:
	Document head; //�ĵ����

public:
	Doc(){head.docID = -1; head.times = 0;} //���캯��
	~Doc(){}

	void operator = (Doc &s){head = s.head;} //=����
	bool operator == (Doc &s){if(s.head.docID == head.docID && s.head.times == head.times) return true; return false;} //�Ƚ��ĵ����
};

#endif