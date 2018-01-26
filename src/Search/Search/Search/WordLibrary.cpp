/*
* 文件名：WordLibrary.cpp
*
* 文件中所包含的类或接口等的名称列表：WordLibrary.h/CharString.h/LinkedList.h
*
* 文件功能：实现词库函数
*
* 作者：王华清
*
* 日期：2013年11月24日
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
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
WordLibrary::WordLibrary()
{
	initWordLibrary();
}

WordLibrary::~WordLibrary()
{
	for(int i = 0; i < 1000003; i++) //创建Hash表
	{
		dic[i].destroyList();
	}
	delete []dic;
}


/**
 * 功能：把分词词库载入内存
 * 参数及返回值说明：
 *     参数：s：词典路径
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordLibrary::preMatch(char* s)
{
	saveWordLibrary(s); //加载词库
}

/**
 * 功能：初始化
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordLibrary::initWordLibrary()
{
	dic = new(LinkedList<CharString>[1000003]);
	for(int i = 0; i < 1000003; i++) //创建Hash表
	{
		dic[i].initList();
	}
}

/**
 * 功能：把分词词库存入Hash表
 * 参数及返回值说明：
 *     参数：ch：词库路径名
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordLibrary::saveWordLibrary(char* ch)
{
	ifstream wordlibrary;
	wordlibrary.open(ch);
	string s;
	CharString str;
	int hashkey; //Hash值
	while(!wordlibrary.eof()) //文件未读完时
	{
		str.destroyString();
		getline(wordlibrary, s);
		char* ch = (char*)s.c_str();
		str.strAssign(ch);
		hashkey = hash(ch); //计算Hash值
		dic[hashkey].listInsert(1, str); //在对应Hash值链表中存入词语
//		delete []ch;
	}
	wordlibrary.sync();
	wordlibrary.clear();
	wordlibrary.close();
}

/**
 * 功能：计算Hash值
 * 参数及返回值说明：
 *     参数：s：词语
 *     返回值：Hash值
 * 作者：王华清
 * 日期：2013年11月24日
 */
unsigned int WordLibrary::hash(char* s)
{
	unsigned int i = 0, key = 0;
	while(s[i] != 0) //BKDR字符串Hash函数
	{
		key = key * 13131 + abs(s[i] + s[i + 1]);
		key %= 1000003;
		i += 2;
	}
	return(key);
}

/**
 * 功能：计算Hash值
 * 参数及返回值说明：
 *     参数：s：词语
 *     返回值：true在词典中，false不在词典中
 * 作者：王华清
 * 日期：2013年11月24日
 */
bool WordLibrary::findWord(CharString &s)
{
	int hashkey = hash(s.head->ch); //Hash值
	return(dic[hashkey].locateElem(s) > 0);
}