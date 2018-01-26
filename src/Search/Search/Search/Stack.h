/*
* 文件名：Stack.h
*
* 文件中所包含的类或接口等的名称列表：Stack<ElemType>
*
* 文件功能：实现栈类（用模板）
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef STACK_H
#define STACK_H

/**
 * 功能：单向链表栈类（用模板）
 *       实现字符串栈时使用语句"Stack<字符串类> 变量名;"即可
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
class Stack
{
public:
	//栈结点数据类型
	typedef struct StackNode{
		ElemType data; //储存值
		struct StackNode *next; //后继指针
	}StackNode, *pStackNode;

public:
	pStackNode head; //栈头结点

public:
	Stack();
	~Stack();

	void initStack();
	void push(ElemType &x);
	void pop(ElemType &x);
	void getTop(ElemType &x);
	bool stackEmpty();
	int stackLength();
	void clearStack();
};

/**
 * 功能：构造函数
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
Stack<ElemType>::Stack()
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
template<class ElemType>
Stack<ElemType>::~Stack()
{
	pStackNode temp;
	while(head != NULL) //栈不为空时删除结点
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

/**
 * 功能：初始化
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void Stack<ElemType>::initStack()
{
	head = NULL;
}

/**
 * 功能：压入元素x至栈顶
 * 参数及返回值说明：
 *     参数：x：待压入的元素
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void Stack<ElemType>::push(ElemType &x)
{
	pStackNode temp;
	temp = new(StackNode); //新建结点
	temp->data = x;
	temp->next = head;
	head = temp;
}

/**
 * 功能：取出栈顶元素
 * 参数及返回值说明：
 *     参数：无
 *     返回值：取出的栈顶元素值
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void Stack<ElemType>::pop(ElemType &x)
{
	pStackNode temp;
	temp = head;
	if(temp != NULL) //头结点不为空时进行操作
	{
		x = temp->data;
		head = head->next;
		delete temp;
		temp = NULL;
	}
	else //头结点为空时
		x = 0;
}

/**
 * 功能：求栈顶元素的值
 * 参数及返回值说明：
 *     参数：无
 *     返回值：栈顶元素值
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void Stack<ElemType>::getTop(ElemType &x)
{
	if(head == NULL) //头结点为空时
		x = 0;
	else
		x = head->data; //头结点不为空时进行操作
}

/**
 * 功能：判断链表是否为空
 * 参数及返回值说明：
 *     参数：无
 *     返回值：True表示为空，False表示不为空
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
bool Stack<ElemType>::stackEmpty()
{
	if(head == NULL)
		return true;
	return false;
}

/**
 * 功能：求栈长度
 * 参数及返回值说明：
 *     参数：无
 *     返回值：栈长度
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
int Stack<ElemType>::stackLength()
{
	pStackNode temp;
	int i = 0; //计数器
	temp = head;
	while(temp != NULL) //未到栈底时进行操作
	{
		temp = temp->next;
		i++;
	}
	return i;
}

/**
 * 功能：清空栈
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void Stack<ElemType>::clearStack()
{
	pStackNode temp;
	while(head != NULL) //栈不为空时删除结点
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

#endif