/*
* 文件名：WordLibrary.h
*
* 文件中所包含的类或接口等的名称列表：CharString.h\LinkedList.h\WordLibrary
*
* 文件功能：实现词库类
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef WORDLIBRARY_H
#define WORDLIBRARY_H

#include"CharString.h"
#include"LinkedList.h"
#include<fstream>

/**
 * 功能：词库类
 * 作者：王华清
 * 日期：2013年11月24日
 */
class WordLibrary
{
public:
	LinkedList<CharString> *dic; //词库Hash表

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