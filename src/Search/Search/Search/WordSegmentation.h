/*
* 文件名：WordSegmentation.h
*
* 文件中所包含的类或接口等的名称列表：CharString.h\LinkedList.h\WordLibrary.h\Stack.h\WordSegmentation
*
* 文件功能：实现网页解析类
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

#include"WordLibrary.h"
#include"CharString.h"
#include"LinkedList.h"
#include"Stack.h"
#include<fstream>

/**
 * 功能：网页解析类
 * 作者：王华清
 * 日期：2013年11月24日
 */
class WordSegmentation
{
public:
	Stack<CharString> html; //网页解析栈
	WordLibrary	dic, stop; //网页解析词库
	LinkedList<CharString> word; //网页解析结果链表
	
public:
	WordSegmentation();
	~WordSegmentation();

	void htmlParse();
	void pickOutHtmlMainBody(char* chin, char* chout);
	void wordSegmentation(char* ch);
	void segmentation(CharString &s);
	void outputWord(char* ch);
	void addWordLibrary();
};

#endif