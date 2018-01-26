/*
* 文件名：CharString.cpp
*
* 文件中所包含的类或接口等的名称列表：CharString.h
*
* 文件功能：实现字符串类函数
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#include "StdAfx.h"
#include<iostream>
using namespace std;
#include"CharString.h"

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
CharString::CharString()
{
	head = NULL;
}

/**
 * 功能：析构函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
CharString::~CharString()
{
	destroyString();
}

/**
 * 功能：初始化
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::initString()
{
	destroyString(); //删除原字符串
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
}

/**
 * 功能：初始化并赋值
 * 参数及返回值说明：
 *     参数：s：初始化要赋的值
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::initString(char* s)
{
	destroyString(); //删除原字符串
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
	strAssign(s); //赋值为s
}

/**
 * 功能：赋值
 * 参数及返回值说明：
 *     参数：s：要赋的值
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::strAssign(char* s)
{
	int i = 0; //计数器
	while(s[i] != 0) //求s的长度
		i++;
	if(head == NULL) //若指针为空初始化字符串
		initString();
	delete []head->ch; //删除原字符串
	head->ch = new(char[i + 1]); //分配新空间
	head->length = i; //赋长度值
	for(i = 0; i < head->length; i++) //赋值
		head->ch[i] = s[i];
	head->ch[head->length] = '\0';
}

/**
 * 功能：删除字符串
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::destroyString()
{
	if(head == NULL) //指针不为空时进行操作
		return;
	delete []head->ch;
	head->ch = NULL;
	head->length = 0;
	delete head;
	head = NULL;
}

/**
 * 功能：复制字符串
 * 参数及返回值说明：
 *     参数：s：待复制的字符串
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::strCopy(CharString &s)
{
	if(s.head == NULL) //若待复制的字符串为空
		destroyString(); //删除字符串
	else
		strAssign(s.head->ch); //赋值
}

/**
 * 功能：求字符串长度
 * 参数及返回值说明：
 *     参数：无
 *     返回值：字符串长度
 * 作者：王华清
 * 日期：2013年11月24日
 */
int CharString::strLength()
{
	if(head == NULL) //字符串为空时返回-1
		return -1;
	return head->length;
}

/**
 * 功能：比较字符串
 * 参数及返回值说明：
 *     参数：s：与之比较的字符串
 *     返回值：1：当前字符串大
 *             -1：当前字符串小
 *             0：字符串相等
 *             （字符串比较时比较第一位不同的字符）
 * 作者：王华清
 * 日期：2013年11月24日
 */
int CharString::strCompare(CharString &s)
{
	if(head == NULL && s.head == NULL)  //均为空
		return 0;
	if(head == NULL) //当前字符串为空
		return -1;
	if(s.head == NULL) //比较对象为空
		return 1;
	int i = 0; //计数器
	while(head->ch[i] == s.head->ch[i] &&
		head->ch[i] != '\0' && s.head->ch[i] != '\0') //字符相等且字符串未结束时
	{
		i++;
	}
	if(head->ch[i] == s.head->ch[i]) //同时结束
		return 0;
	else if(head->ch[i] - s.head->ch[i] > 0) //当前字符串字符大
		return 1;
	else //当前字符串字符小
		return -1;
}

/**
 * 功能：连接字符串
 * 参数及返回值说明：
 *     参数：s1：字符串1
 *           s2：字符串2
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::concat(CharString s1, CharString s2)
{
	int i = 0;
	if(head == NULL) //当前字符串为空
		initString();
	if(s1.head == NULL) //字符串s1为空
		s1.initString();
	if(s2.head == NULL) //字符串s2为空
		s2.initString();
	delete []head->ch; //删除原字符串
	head->ch = new(char[s1.head->length + s2.head->length + 1]); //分配新空间
	head->length = s1.head->length + s2.head->length; //赋长度值
	for(i = 0; i < s1.head->length; i++) //赋s1值
		head->ch[i] = s1.head->ch[i];
	for(i = s1.head->length; i < s1.head->length + s2.head->length; i++) //赋s2值
		head->ch[i] = s2.head->ch[i - s1.head->length];
	head->ch[head->length] = '\0';
}

/**
 * 功能：字符串判空
 * 参数及返回值说明：
 *     参数：无
 *     返回值：true为空，false不为空
 * 作者：王华清
 * 日期：2013年11月24日
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
 * 功能：截取字符串
 * 参数及返回值说明：
 *     参数：pos：截取起始位置
 *           len：截取长度
 *     返回值：截取的字符串
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::subString(int pos, int len, CharString &s)
{
	int i = 0; //计数器
	if(head == NULL) //字符串不为空时进行操作
	{
		s = NULL;
		return;
	}
	if(head->length < pos + len || pos < 0) //带截取字符串存在时进行操作
	{
		s = NULL;
		return;
	}
	s.destroyString();
	s.head = new(HString); //分配新空间
	s.head->ch = new(char[len + 1]); //分配新空间
	s.head->length = len; //赋长度值
	for(i = 0; i < len; i++) //赋值
		s.head->ch[i] = head->ch[pos + i];
	s.head->ch[len] = '\0';
}

/**
 * 功能：清空字符串
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::clearString()
{
	destroyString(); //删除原字符串
	head = new(HString);
	head->ch = new(char[1]);
	head->ch[0] = '\0';
	head->length = 0;
}

/**
 * 功能：查找字符串
 * 参数及返回值说明：
 *     参数：s：待查找的字符串
 *     返回值：找到字符串起始位置
 * 作者：王华清
 * 日期：2013年11月24日
 */
int CharString::index(CharString &s)
{
	if(head == NULL) //字符串为空返回-1
		return -1;
	int i, j = 1, k = 0, *next; //计数器

	//计算next[]值
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

	//KMP算法
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
	if(j > s.head->length) //找到字符串
		return(i - s.head->length - 1);
	else //未找到字符串
		return -1;
}

/**
 * 功能：查找字符串
 * 参数及返回值说明：
 *     参数：s：待查找的字符串
 *           pos：查找起始位置
 *     返回值：找到字符串起始位置
 * 作者：王华清
 * 日期：2013年11月24日
 */
int CharString::index(CharString &s, int pos)
{
	if(head == NULL)  //字符串为空返回-1
		return -1;
	int i, j = 1, k = 0, *next; //计数器

	//计算next[]值
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

	//KMP算法
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
	if(j > s.head->length) //找到字符串
		return(i - s.head->length - 1);
	else //未找到字符串
		return -1;
}

/**
 * 功能：删除部分字符串
 * 参数及返回值说明：
 *     参数：pos：删除起始位置
 *           len：删除长度
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
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
 * 功能：插入字符串
 * 参数及返回值说明：
 *     参数：pos：插入起始位置
 *           s：待插入的字符串
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
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
 * 功能：替换字符串
 * 参数及返回值说明：
 *     参数：s：查找字符串
 *           t：替换字符串
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::replace(CharString s, CharString t)
{
	int i = 0; //计数器
	while(true)
	{
		i = index(s, i);
		if(i == -1) //找不到s，结束
			return;
		strDelete(i, s.head->length);
		strInsert(i, t);
		i += t.head->length;
	}
}

/**
 * 功能：在字符串后加一个字符
 * 参数及返回值说明：
 *     参数：c：待加入的字符
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void CharString::addChar(char c)
{
	if(head == NULL) //字符串为空时初始化
		initString();
	head->length++; //长度+1
	head->ch = (char*)realloc(head->ch, (head->length + 1) * sizeof(char)); //扩大空间
	head->ch[head->length - 1] = c; //赋值
	head->ch[head->length] = '\0';
}