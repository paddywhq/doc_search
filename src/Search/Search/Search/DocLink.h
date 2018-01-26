/*
* 文件名：DocLink.h
*
* 文件中所包含的类或接口等的名称列表：Doc.h, CharString.h, LinkedList.h, DocLink
*
* 文件功能：实现文档链表类
*
* 作者：王华清
*
* 日期：2014年1月1日
*/
#ifndef DOCLINK_H
#define DOCLINK_H
#include "Doc.h"
#include "CharString.h"
#include "LinkedList.h"

/**
 * 功能：文档链表类
 * 作者：王华清
 * 日期：2014年1月1日
 */
class DocLink
{
public:
	CharString term; //单词
	int df; //出现网页数
	int occur; //出现总次数
	LinkedList<Doc> docinfo; //文档链表

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
	bool operator > (DocLink &s){return(term > s.term);} //重载>
	bool operator < (DocLink &s){return(term < s.term);} //重载<
	bool operator == (DocLink &s){return(term == s.term);} //重载==
	bool operator >= (DocLink &s){return(term >= s.term);} //重载>=
	bool operator <= (DocLink &s){return(term <= s.term);} //重载<=
	bool operator != (DocLink &s){return(term != s.term);} //重载!=
	void operator = (DocLink &s){df = s.df; occur = s.occur; term = s.term; docinfo = s.docinfo;} //重载=
};

#endif