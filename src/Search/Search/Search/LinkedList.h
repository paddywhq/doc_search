/*
* 文件名：LinkedList.h
*
* 文件中所包含的类或接口等的名称列表：LinkedList<ElemType>
*
* 文件功能：实现链表类（用模板）
*
* 作者：王华清
*
* 日期：2013年11月24日
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * 功能：带头结点的单向循环链表类（用模板）
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
class LinkedList
{
public:
	//链表结点数据类型
	typedef struct LinkNode{
		ElemType data; //储存值
		struct LinkNode *next; //后继指针
	}LinkNode, *pLinkNode;

public:
	pLinkNode head; //链表头结点

public:
	LinkedList();
	~LinkedList();

	void initList();
	void destroyList();
	bool listEmpty();
	int listLength();
	void clearList();
	void putElem(int i, ElemType e);
	void listInsert(int i, ElemType &e);
	ElemType listDelete(int i);
	ElemType getElem(int i);
	ElemType priorElem(ElemType e);
	ElemType nextElem(ElemType e);
	ElemType priorElem(int i, ElemType e);
	ElemType nextElem(int i, ElemType e);
	int locateElem(ElemType &e);
	int locateElem(int i, ElemType &e);
	void operator = (LinkedList &s){head = s.head;}
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
LinkedList<ElemType>::LinkedList()
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
LinkedList<ElemType>::~LinkedList()
{
	destroyList(); //删除链表
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
void LinkedList<ElemType>::initList()
{
	destroyList(); //删除原链表
	head = new(LinkNode);
	head->next = head;
}

/**
 * 功能：删除链表
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void LinkedList<ElemType>::destroyList()
{
	pLinkNode temp;
	if(head != NULL) //头结点不为空时进行操作
	{
		while(head->next != head) //链表不为空时删除结点
		{
			temp = head->next;
			head->next = head->next->next;
			delete temp;
		}
		delete head;
		head = NULL;
	}
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
bool LinkedList<ElemType>::listEmpty()
{
	if(head == NULL || head->next == head)
		return true;
	else
		return false;
}

/**
 * 功能：求链表长度
 * 参数及返回值说明：
 *     参数：无
 *     返回值：链表长度（不含头结点）
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
int LinkedList<ElemType>::listLength()
{
	pLinkNode temp;
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	else
	{
		int i = 0; //计数器
		temp = head;
		while(temp->next != head)
		{
			temp = temp->next;
			i++;
		}
		return i;
	}
}

/**
 * 功能：清空链表
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void LinkedList<ElemType>::clearList()
{
	pLinkNode temp;
	if(head != NULL) //头结点不为空时进行操作
	{
		while(head->next != head) //链表不为空时删除结点
		{
			temp = head->next;
			head->next = head->next->next;
			delete temp;
		}
	}
}

/**
 * 功能：将第i个结点储存的数据改为e，若i大于链表长度则不操作
 * 参数及返回值说明：
 *     参数：i：待修改的结点编号
 *           e：待修改为的数据
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void LinkedList<ElemType>::putElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return;
	pLinkNode temp;
	int j = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(j == i) //找到i时操作
		{
			temp->data = e;
			return;
		}
	}
}

/**
 * 功能：插入第i个结点，储存的数据为e，若i大于（链表长度+1）则不操作
 * 参数及返回值说明：
 *     参数：i：待插入的结点编号
 *           e：插入结点储存的数据
 *     返回值：无
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
void LinkedList<ElemType>::listInsert(int i, ElemType &e)
{
	if(head == NULL) //头结点不为空时进行操作
		return;
	pLinkNode p, q;
	int j = 0; //计数器
	p = head;
	while(p->next != head)
	{
		if(j == i - 1) //找到i时操作
		{
			q = new(LinkNode);
			q->data = e;
			q->next = p->next;
			p->next = q;
			p = NULL;
			q = NULL;
			return;
		}
		p = p->next;
		j++;
	}
	if(j == i - 1) //找到i时操作
	{
		q = new(LinkNode);
		q->data = e;
		q->next = p->next;
		p->next = q;
		p = NULL;
		q = NULL;
		return;
	}
}

/**
 * 功能：删除第i个结点，若i大于链表长度则不操作
 * 参数及返回值说明：
 *     参数：i：待删除的结点编号
 *     返回值：删除结点储存的数据，若i大于链表长度则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::listDelete(int i)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode p, q;
	ElemType x;
	int j = 0; //计数器
	p = head;
	while(p->next != head)
	{
		if(j == i - 1) //找到i时操作
		{
			q = p->next;
			x = q->data;
			p->next = q->next;
			delete q;
			return x;
		}
		p = p->next;
		j++;
	}
	return 0; //未找到
}

/**
 * 功能：获取第i个结点的数据，若i大于链表长度则不操作
 * 参数及返回值说明：
 *     参数：i：待获取的结点编号
 *     返回值：结点储存的数据，若i大于链表长度则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::getElem(int i)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int j = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(j == i) //找到i时操作
			return temp->data;
	}
	return 0; //未找到
}

/**
 * 功能：获取第1个储存数据为e的结点前一个结点的值
 * 参数及返回值说明：
 *     参数：e：待寻找的结点数据
 *     返回值：找到结点前一个结点储存的数据，若结点不存在或为第一个则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::priorElem(ElemType e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int j = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		if(temp->next->data == e && temp != head) //找到e时操作
			return temp->data;
		else if(temp->next->data == e && temp == head) //找到e为头结点
			return 0;
		temp = temp->next;
		j++;
	}
	return 0; //未找到
}

/**
 * 功能：获取第1个储存数据为e的结点后一个结点的值
 * 参数及返回值说明：
 *     参数：e：待寻找的结点数据
 *     返回值：找到结点后一个结点储存的数据，若结点不存在或为最后一个则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::nextElem(ElemType e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int j = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e && temp->next != head) //找到e时操作
			return temp->next->data;
	}
	return 0; //未找到
}

/**
 * 功能：获取第i个储存数据为e的结点前一个结点的值
 * 参数及返回值说明：
 *     参数：i：待寻找的结点个数
 *           e：待寻找的结点数据
 *     返回值：找到结点前一个结点储存的数据，若结点不存在或为第一个则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::priorElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int k = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		if(temp->next->data == e) //找到e时操作
			k++;
		if(temp != head && k == i) //找到第i个e时操作
			return temp->data;
		else if(temp == head && k == i) //找到第i个e为头结点
			return 0;
		temp = temp->next;
	}
	return 0; //未找到
}

/**
 * 功能：获取第i个储存数据为e的结点后一个结点的值
 * 参数及返回值说明：
 *     参数：i：待寻找的结点个数
 *           e：待寻找的结点数据
 *     返回值：找到结点后一个结点储存的数据，若结点不存在或为最后一个则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
ElemType LinkedList<ElemType>::nextElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int k = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		if(temp->data == e) //找到e时操作
			k++;
		if(temp->next != head && k == i) //找到第i个e时操作
			return temp->next->data;
	}
	return 0; //未找到
}

/**
 * 功能：获取第1个储存数据为e的结点编号
 * 参数及返回值说明：
 *     参数：e：待寻找的结点数据
 *     返回值：找到结点的编号，若结点不存在则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
int LinkedList<ElemType>::locateElem(ElemType &e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int j = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e) //找到e时操作
			return j;
	}
	return 0; //未找到
}

/**
 * 功能：获取第i个储存数据为e的结点编号
 * 参数及返回值说明：
 *     参数：i：待寻找的结点个数
 *           e：待寻找的结点数据
 *     返回值：找到结点的编号，若结点不存在则返回0
 * 作者：王华清
 * 日期：2013年11月24日
 */
template<class ElemType>
int LinkedList<ElemType>::locateElem(int i, ElemType &e)
{
	if(head == NULL || head->next == head) //头结点不为空时进行操作
		return 0;
	pLinkNode temp;
	int j = 0, k = 0; //计数器
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e) //找到e时操作
			k++;
		if(k == i) //找到第i个e时操作
			return j;
	}
	return 0; //未找到
}

#endif