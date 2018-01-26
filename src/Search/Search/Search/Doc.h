/*
* 文件名：Doc.h
*
* 文件中所包含的类或接口等的名称列表：Doc
*
* 文件功能：实现文档类
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef DOC_H
#define DOC_H

/**
 * 功能：文档类
 * 作者：王华清
 * 日期：2013年11月24日
 */
class Doc
{
public:
	//文档结构数据类型
	typedef struct{
		int docID; //网页编号
		int times; //出现次数
	}Document;

public:
	Document head; //文档结点

public:
	Doc(){head.docID = -1; head.times = 0;} //构造函数
	~Doc(){}

	void operator = (Doc &s){head = s.head;} //=重载
	bool operator == (Doc &s){if(s.head.docID == head.docID && s.head.times == head.times) return true; return false;} //比较文档相等
};

#endif