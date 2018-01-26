/*
* �ļ�����WordLibrary.cpp
*
* �ļ��������������ӿڵȵ������б�WordSegmentation.h/WordLibrary.h/CharString.h/LinkedList.h/Stack.h
*
* �ļ����ܣ�ʵ����ҳ��������
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
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
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
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
	dic.preMatch("Dic.txt"); //���شʿ�
	dic.preMatch("Name.txt"); //�������Ǵʿ�
	stop.preMatch("Stop.txt"); //����ͣ�ôʿ�
//	finish = clock();
//	cout<<(double)(finish - start) / CLOCKS_PER_SEC<<"s"<<endl;
}

/**
 * ���ܣ�������ҳ��������ִʽ�����ַ�������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void WordSegmentation::htmlParse()
{
//	clock_t start, finish;
/*
	//ͨ������·�����شʿ�
	cout<<"����ʵ�·����";
	string s;
	getline(cin, s);
	dic.preMatch((char*)s.c_str());
		
	cout<<"����ͣ�ôʵ�·����";
	string s;
	getline(cin, s);
	stop.preMatch((char*)s.c_str());
*/

	addWordLibrary();

/*
	cout<<"������ҳ·����";
	string s;
	getline(cin, s);
	pickOutHtmlMainBody((char*)s.c_str(), "MainBody.txt"); //������ҳ
	wordSegmentation("MainBody.txt"); //�ִ�
	cout<<"����ִʽ������·����";
	getline(cin, s);
	outputWord((char*)s.c_str()); //������
*/

	//��SinaPage\\0001.shtml~SinaPage\\2500.shtml����
	//Ȼ��ִʲ�������SinaPage\\0001.txt~SinaPage\\2500.txt
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
 * ���ܣ�������ҳ
 * ����������ֵ˵����
 *     ������chin����ҳ·��
 *           chout�����ı���·��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
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
	temp3.initString("��������");
	temp4.initString("p");
	input.open(chin);
	output.open(chout);
	bool mainbody = false; //�ж��Ƿ�Ϊ����
	while(!input.eof()) //���ļ�δ����
	{
		input.get(c);
		if(c == '<') //����<
		{
			input.get(c);
			if(c == '/') //Ϊ</****>
			{
				html.pop(s); //��ջ
				s.destroyString();
				s.initString();
				input.get(c);
				while(c != '>') //����</****>���ַ���
				{
					s.addChar(c);
					input.get(c);
				}
				if(mainbody && temp4.strCompare(s) == 0) //Ϊ</p>ʱ���Ļ���
					output<<endl;
			}
			else if(c == '!') //Ϊ<!--****-->
			{
				s.destroyString();
				s.initString();
				while(c != '>') //����<!--****-->���ַ���
				{
					s.addChar(c);
					input.get(c);
				}
				if(s.index(temp3) >= 0) //Ϊ<!-- �������� being/end -->ʱ�����жϱ����л�
					mainbody = !mainbody;
			}
			else if(c != '!') //�������
			{
				s.destroyString();
				s.initString();
				while(c != '>') //����<****>���ַ���
				{
					s.addChar(c);
					input.get(c);
				}
				html.push(s); //��ջ
				if(s.head->ch[s.head->length - 1] == '/') //Ϊ<****/>
					html.pop(s); //��ջ
				else if(s.index(temp2) == 0) //Ϊ<meta ****>
					html.pop(s); //��ջ
				else if(s.index(temp1) == 0) //Ϊ<script ****>
					while(true) //ѭ������</script>
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
						if(c == '>') //Ϊ</script>
						{
							html.pop(s); //��ջ
							break;
						}
					}	
			}
		}
		else if(mainbody && !html.stackEmpty())
		{
			html.getTop(s);
			if(temp4.strCompare(s) == 0 || html.head->next->data == temp4) //Ϊ<p>��<p><strong>ʱ�����������
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
 * ���ܣ��ִ�
 * ����������ֵ˵����
 *     ������ch���ִ��ı�
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
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
/*		if(c >= 0) //����Ӣ�Ļ����ֻ�Ӣ�ķ���
		{
			while(s.strLength() != 0) //���Ѵ���ַ����ִ���
				segmentation(s);
			s.destroyString();
			s.initString(); //��ʼ��
			while(c >= 0 && (c != ' ' && c != '\n' && c != '\r' && c != '\0') && !input.eof()) //��Ϊ�ո��еȷ����ַ���
			{
				s.addChar(c);
				input.get(c);
			}
			do
			{
				pos = s.index(temp);
				if(pos >= 0)
					s.strDelete(pos, 6);
			}while(pos >= 0); //ɾ������&nbsp;
			if(s.strLength() != 0) 
				word.listInsert(1, s); //���õ���Ӣ�ĵ��ʻ�����ֱ�Ӵ���
			s.destroyString();
			s.initString(); //��ʼ��
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
			chinese[2] = '\0'; //���һλ����
			if(strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0  || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "�C") == 0 || strcmp(chinese, "��") == 0
				|| strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0 || strcmp(chinese, "��") == 0)
			{ //��Ϊ���
				while(s.strLength() != 0) //���Ѵ���ַ����ִ���
					segmentation(s);
			}
			else
			{
				s.addChar(chinese[0]);
				s.addChar(chinese[1]);
				if(s.strLength() >= 40) //�ﵽ���ʳ�ʱ�����Ѵ���ַ����ִ�һ��
					segmentation(s);
			}
			input.get(c);
		}
	}
	while(s.strLength() != 0) //���Ѵ���ַ����ִ���
		segmentation(s);
	s.destroyString();
	temp.destroyString();
	delete []chinese;
	input.sync();
	input.clear();
	input.close();
}

/**
 * ���ܣ��ִ�һ��
 * ����������ֵ˵����
 *     ������s�����ִʵ��ַ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
void WordSegmentation::segmentation(CharString &s)
{
	int i = s.strLength(); //�ַ�������
	if(i == 0)
		return;
	CharString temp;
	while(i > 0)
	{
		s.subString(0, i, temp); //ǰi/2������
		if(dic.dic[dic.hash(temp.head->ch)].locateElem(temp) > 0) //�������
		{
			word.listInsert(1, temp);
			s.strDelete(0, i);
			return;
		}
		if(stop.dic[stop.hash(temp.head->ch)].locateElem(temp) > 0) //Ϊͣ�ô�
		{
			s.strDelete(0, i);
			return;
		}
		i -= 2; //����һ������
	}
	word.listInsert(1, temp);
	s.strDelete(0, 2);
	temp.destroyString();
}

/**
 * ���ܣ����
 * ����������ֵ˵����
 *     ������ch������ļ���
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
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
	while(temp->next != word.head) //δ������
	{
		temp = temp->next;
		stack.push(temp->data); //��ջ
	}
	while(!stack.stackEmpty()) //ջ����
	{
		stack.pop(s); //��ջ
		output.write(s.head->ch, s.head->length); //���
		output<<endl;
	}
	stack.clearStack();
	output.clear();
	output.close();
}