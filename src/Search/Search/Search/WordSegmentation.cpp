/*
* 文件名：WordLibrary.cpp
*
* 文件中所包含的类或接口等的名称列表：WordSegmentation.h/WordLibrary.h/CharString.h/LinkedList.h/Stack.h
*
* 文件功能：实现网页解析函数
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#include "StdAfx.h"
#include<iostream>
#include"WordSegmentation.h"
#include"WordLibrary.h"
#include"CharString.h"
#include"LinkedList.h"
#include"Stack.h"
#include<fstream>
#include<string>
//#include<ctime>
using namespace std;

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
WordSegmentation::WordSegmentation()
{
	html.initStack();
	word.initList();
	dic.initWordLibrary();
	stop.initWordLibrary();
}

WordSegmentation::~WordSegmentation()
{
	html.clearStack();
	word.destroyList();
	dic.~WordLibrary();
	stop.~WordLibrary();
}

void WordSegmentation::addWordLibrary()
{
//	start = clock();
	dic.preMatch("Dic.txt"); //加载词库
	dic.preMatch("Name.txt"); //加载人们词库
	stop.preMatch("Stop.txt"); //加载停用词库
//	finish = clock();
//	cout<<(double)(finish - start) / CLOCKS_PER_SEC<<"s"<<endl;
}

/**
 * 功能：输入网页名，输出分词结果的字符串链表
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordSegmentation::htmlParse()
{
//	clock_t start, finish;
/*
	//通过输入路径加载词库
	cout<<"输入词典路径：";
	string s;
	getline(cin, s);
	dic.preMatch((char*)s.c_str());
		
	cout<<"输入停用词典路径：";
	string s;
	getline(cin, s);
	stop.preMatch((char*)s.c_str());
*/

	addWordLibrary();

/*
	cout<<"输入网页路径：";
	string s;
	getline(cin, s);
	pickOutHtmlMainBody((char*)s.c_str(), "MainBody.txt"); //解析网页
	wordSegmentation("MainBody.txt"); //分词
	cout<<"输入分词结果保存路径：";
	getline(cin, s);
	outputWord((char*)s.c_str()); //输出结果
*/

	//将SinaPage\\0001.shtml~SinaPage\\2500.shtml解析
	//然后分词并保存至SinaPage\\0001.txt~SinaPage\\2500.txt
//	start = clock();
	CharString file;
	char m, n, o, p;
	for(int i = 1; i <= 2500; i++)
	{
		html.initStack();
		word.initList();
		m = i / 1000 + 48;
		n = i / 100 % 10 + 48;
		o = i / 10 % 10 + 48;
		p = i % 10 + 48;
		file.strAssign("SinaPage\\0001.shtml\0");
		file.head->ch[9] = m;
		file.head->ch[10] = n;
		file.head->ch[11] = o;
		file.head->ch[12] = p;
		pickOutHtmlMainBody(file.head->ch, "MainBody.txt");
		wordSegmentation("MainBody.txt");
		file.strAssign("SinaPage\\0001.txt\0");
		file.head->ch[9] = m;
		file.head->ch[10] = n;
		file.head->ch[11] = o;
		file.head->ch[12] = p;
		outputWord(file.head->ch);
		word.destroyList();
		html.clearStack();
	}
//	finish = clock();
//	cout<<(double)(finish - start) / CLOCKS_PER_SEC<<"s"<<endl;

}

/**
 * 功能：解析网页
 * 参数及返回值说明：
 *     参数：chin：网页路径
 *           chout：正文保存路径
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordSegmentation::pickOutHtmlMainBody(char* chin, char* chout)
{
	char c;
	ifstream input;
	ofstream output;
	CharString s, temp1, temp2, temp3, temp4;
	s.initString();
	temp1.initString("script");
	temp2.initString("meta");
	temp3.initString("正文内容");
	temp4.initString("p");
	input.open(chin);
	output.open(chout);
	bool mainbody = false; //判断是否为正文
	while(!input.eof()) //若文件未读完
	{
		input.get(c);
		if(c == '<') //读到<
		{
			input.get(c);
			if(c == '/') //为</****>
			{
				html.pop(s); //出栈
				s.destroyString();
				s.initString();
				input.get(c);
				while(c != '>') //分离</****>内字符串
				{
					s.addChar(c);
					input.get(c);
				}
				if(mainbody && temp4.strCompare(s) == 0) //为</p>时正文换行
					output<<endl;
			}
			else if(c == '!') //为<!--****-->
			{
				s.destroyString();
				s.initString();
				while(c != '>') //分离<!--****-->内字符串
				{
					s.addChar(c);
					input.get(c);
				}
				if(s.index(temp3) >= 0) //为<!-- 正文内容 being/end -->时正文判断变量切换
					mainbody = !mainbody;
			}
			else if(c != '!') //其他情况
			{
				s.destroyString();
				s.initString();
				while(c != '>') //分离<****>内字符串
				{
					s.addChar(c);
					input.get(c);
				}
				html.push(s); //入栈
				if(s.head->ch[s.head->length - 1] == '/') //为<****/>
					html.pop(s); //出栈
				else if(s.index(temp2) == 0) //为<meta ****>
					html.pop(s); //出栈
				else if(s.index(temp1) == 0) //为<script ****>
					while(true) //循环读到</script>
					{
						while(c != '<')
							input.get(c);
						input.get(c);
						if(c != '/')
							continue;
						input.get(c);
						if(c != 's')
							continue;
						input.get(c);
						if(c != 'c')
							continue;
						input.get(c);
						if(c != 'r')
							continue;
						input.get(c);
						if(c != 'i')
							continue;
						input.get(c);
						if(c != 'p')
							continue;
						input.get(c);
						if(c != 't')
							continue;
						input.get(c);
						if(c == '>') //为</script>
						{
							html.pop(s); //出栈
							break;
						}
					}	
			}
		}
		else if(mainbody && !html.stackEmpty())
		{
			html.getTop(s);
			if(temp4.strCompare(s) == 0 || html.head->next->data == temp4) //为<p>或<p><strong>时输出正文内容
				output.put(c);
		}
	}
	s.destroyString();
	temp1.destroyString();
	temp2.destroyString();
	temp3.destroyString();
	temp4.destroyString();
	input.sync();
	input.clear();
	output.clear();
	input.close();
	output.close();
}

/**
 * 功能：分词
 * 参数及返回值说明：
 *     参数：ch：分词文本
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordSegmentation::wordSegmentation(char* ch)
{
	ifstream input;
	input.open(ch);
	char c;
	char* chinese;
	CharString s, temp;
	temp.initString("&nbsp;");
	s.initString();
	chinese = new(char[3]); 
	input.get(c);
	while(!input.eof())
	{
/*		if(c >= 0) //读到英文或数字或英文符号
		{
			while(s.strLength() != 0) //将已存的字符串分词完
				segmentation(s);
			s.destroyString();
			s.initString(); //初始化
			while(c >= 0 && (c != ' ' && c != '\n' && c != '\r' && c != '\0') && !input.eof()) //不为空格换行等分离字符串
			{
				s.addChar(c);
				input.get(c);
			}
			do
			{
				pos = s.index(temp);
				if(pos >= 0)
					s.strDelete(pos, 6);
			}while(pos >= 0); //删除所有&nbsp;
			if(s.strLength() != 0) 
				word.listInsert(1, s); //将得到的英文单词或数字直接存入
			s.destroyString();
			s.initString(); //初始化
			if(c == ' ' || c == '\n' || c == '\r' || c == '\0')
				input.get(c);
		}
*/
		if(c >= 0)
			input.get(c);
		else
		{
			chinese[0] = c;
			input.get(c);
			chinese[1] = c;
			chinese[2] = '\0'; //获得一位中文
			if(strcmp(chinese, "。") == 0 || strcmp(chinese, "，") == 0  || strcmp(chinese, "：") == 0 || strcmp(chinese, "；") == 0 || strcmp(chinese, "？") == 0
				|| strcmp(chinese, "！") == 0 || strcmp(chinese, "（") == 0 || strcmp(chinese, "）") == 0 || strcmp(chinese, "‘") == 0
				|| strcmp(chinese, "’") == 0 || strcmp(chinese, "“") == 0 || strcmp(chinese, "”") == 0 || strcmp(chinese, "【") == 0
				|| strcmp(chinese, "】") == 0 || strcmp(chinese, "—") == 0 || strcmp(chinese, "…") == 0 || strcmp(chinese, "￥") == 0
				|| strcmp(chinese, "《") == 0 || strcmp(chinese, "》") == 0 || strcmp(chinese, "、") == 0 || strcmp(chinese, "·") == 0
				|| strcmp(chinese, "「") == 0 || strcmp(chinese, "」") == 0 || strcmp(chinese, "『") == 0 || strcmp(chinese, "』") == 0
				|| strcmp(chinese, "〔") == 0 || strcmp(chinese, "〕") == 0 || strcmp(chinese, "–") == 0 || strcmp(chinese, "〈") == 0
				|| strcmp(chinese, "〉") == 0 || strcmp(chinese, "．") == 0 || strcmp(chinese, "　") == 0 || strcmp(chinese, "♂") == 0)
			{ //若为标点
				while(s.strLength() != 0) //将已存的字符串分词完
					segmentation(s);
			}
			else
			{
				s.addChar(chinese[0]);
				s.addChar(chinese[1]);
				if(s.strLength() >= 40) //达到最大词长时，将已存的字符串分词一次
					segmentation(s);
			}
			input.get(c);
		}
	}
	while(s.strLength() != 0) //将已存的字符串分词完
		segmentation(s);
	s.destroyString();
	temp.destroyString();
	delete []chinese;
	input.sync();
	input.clear();
	input.close();
}

/**
 * 功能：分词一次
 * 参数及返回值说明：
 *     参数：s：待分词的字符串
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordSegmentation::segmentation(CharString &s)
{
	int i = s.strLength(); //字符串长度
	if(i == 0)
		return;
	CharString temp;
	while(i > 0)
	{
		s.subString(0, i, temp); //前i/2个汉字
		if(dic.dic[dic.hash(temp.head->ch)].locateElem(temp) > 0) //词语存在
		{
			word.listInsert(1, temp);
			s.strDelete(0, i);
			return;
		}
		if(stop.dic[stop.hash(temp.head->ch)].locateElem(temp) > 0) //为停用词
		{
			s.strDelete(0, i);
			return;
		}
		i -= 2; //减少一个汉字
	}
	word.listInsert(1, temp);
	s.strDelete(0, 2);
	temp.destroyString();
}

/**
 * 功能：输出
 * 参数及返回值说明：
 *     参数：ch：输出文件名
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
void WordSegmentation::outputWord(char* ch)
{
	ofstream output;
	output.open(ch); 
	LinkedList<CharString>::pLinkNode temp;
	Stack<CharString> stack;
	stack.initStack();
	CharString s;
	temp = word.head;
	while(temp->next != word.head) //未遍历完
	{
		temp = temp->next;
		stack.push(temp->data); //入栈
	}
	while(!stack.stackEmpty()) //栈不空
	{
		stack.pop(s); //出栈
		output.write(s.head->ch, s.head->length); //输出
		output<<endl;
	}
	stack.clearStack();
	output.clear();
	output.close();
}