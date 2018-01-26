/*
* 文件名：CharString.h
*
* 文件中所包含的类或接口等的名称列表：CharString
*
* 文件功能：实现字符串类
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef CHARSTRING_H
#define CHARSTRING_H

/**
 * 功能：字符串类
 * 作者：王华清
 * 日期：2013年11月24日
 */
class CharString
{
public:
	//字符串结构数据类型
	typedef struct{
		char *ch; //字符串
		int length; //字符串长度
	}HString, *pHString;

public:
	pHString head; //字符串指针

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
	void operator = (int s){if(s == 0) head = NULL;} //用（字符串类 = 0；）语句清零
	void operator = (CharString &s){strCopy(s);} //字符串类赋值
	bool operator == (CharString &s){return(strCompare(s) == 0);} //比较字符串相等
	bool operator >= (CharString &s){return(strCompare(s) >= 0);} //比较字符串
	bool operator <= (CharString &s){return(strCompare(s) <= 0);} //比较字符串
	bool operator > (CharString &s){return(strCompare(s) > 0);} //比较字符串
	bool operator < (CharString &s){return(strCompare(s) < 0);} //比较字符串
	bool operator != (CharString &s){return(strCompare(s) != 0);} //比较字符串
	void addChar(char c);
};

#endif