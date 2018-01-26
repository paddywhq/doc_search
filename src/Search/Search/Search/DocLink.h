/*
* �ļ�����DocLink.h
*
* �ļ��������������ӿڵȵ������б�Doc.h, CharString.h, LinkedList.h, DocLink
*
* �ļ����ܣ�ʵ���ĵ�������
*
* ���ߣ�������
*
* ���ڣ�2014��1��1��
*/
#ifndef DOCLINK_H
#define DOCLINK_H
#include "Doc.h"
#include "CharString.h"
#include "LinkedList.h"

/**
 * ���ܣ��ĵ�������
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
class DocLink
{
public:
	CharString term; //����
	int df; //������ҳ��
	int occur; //�����ܴ���
	LinkedList<Doc> docinfo; //�ĵ�����

public:
	DocLink();
	~DocLink();

	void initDocLink();
	void clearDocLink();
	void destroyDocLink();
	void insertDoc(Doc &e);
	void indexDoc(int &id, Doc &e);
	void deleteDoc(int &id, Doc &e);
	void changeDoc(int &id, Doc &e);
	void outputLink();
	bool operator > (DocLink &s){return(term > s.term);} //����>
	bool operator < (DocLink &s){return(term < s.term);} //����<
	bool operator == (DocLink &s){return(term == s.term);} //����==
	bool operator >= (DocLink &s){return(term >= s.term);} //����>=
	bool operator <= (DocLink &s){return(term <= s.term);} //����<=
	bool operator != (DocLink &s){return(term != s.term);} //����!=
	void operator = (DocLink &s){df = s.df; occur = s.occur; term = s.term; docinfo = s.docinfo;} //����=
};

#endif