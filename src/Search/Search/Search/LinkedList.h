/*
* �ļ�����LinkedList.h
*
* �ļ��������������ӿڵȵ������б�LinkedList<ElemType>
*
* �ļ����ܣ�ʵ�������ࣨ��ģ�壩
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * ���ܣ���ͷ���ĵ���ѭ�������ࣨ��ģ�壩
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
class LinkedList
{
public:
	//��������������
	typedef struct LinkNode{
		ElemType data; //����ֵ
		struct LinkNode *next; //���ָ��
	}LinkNode, *pLinkNode;

public:
	pLinkNode head; //����ͷ���

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
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
LinkedList<ElemType>::LinkedList()
{
	head = NULL;
}

/**
 * ���ܣ���������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
LinkedList<ElemType>::~LinkedList()
{
	destroyList(); //ɾ������
}

/**
 * ���ܣ���ʼ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void LinkedList<ElemType>::initList()
{
	destroyList(); //ɾ��ԭ����
	head = new(LinkNode);
	head->next = head;
}

/**
 * ���ܣ�ɾ������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void LinkedList<ElemType>::destroyList()
{
	pLinkNode temp;
	if(head != NULL) //ͷ��㲻Ϊ��ʱ���в���
	{
		while(head->next != head) //����Ϊ��ʱɾ�����
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
 * ���ܣ��ж������Ƿ�Ϊ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ��True��ʾΪ�գ�False��ʾ��Ϊ��
 * ���ߣ�������
 * ���ڣ�2013��11��24��
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
 * ���ܣ���������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ�������ȣ�����ͷ��㣩
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
int LinkedList<ElemType>::listLength()
{
	pLinkNode temp;
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	else
	{
		int i = 0; //������
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
 * ���ܣ��������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void LinkedList<ElemType>::clearList()
{
	pLinkNode temp;
	if(head != NULL) //ͷ��㲻Ϊ��ʱ���в���
	{
		while(head->next != head) //����Ϊ��ʱɾ�����
		{
			temp = head->next;
			head->next = head->next->next;
			delete temp;
		}
	}
}

/**
 * ���ܣ�����i����㴢������ݸ�Ϊe����i�����������򲻲���
 * ����������ֵ˵����
 *     ������i�����޸ĵĽ����
 *           e�����޸�Ϊ������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void LinkedList<ElemType>::putElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return;
	pLinkNode temp;
	int j = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(j == i) //�ҵ�iʱ����
		{
			temp->data = e;
			return;
		}
	}
}

/**
 * ���ܣ������i����㣬���������Ϊe����i���ڣ�������+1���򲻲���
 * ����������ֵ˵����
 *     ������i��������Ľ����
 *           e�������㴢�������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void LinkedList<ElemType>::listInsert(int i, ElemType &e)
{
	if(head == NULL) //ͷ��㲻Ϊ��ʱ���в���
		return;
	pLinkNode p, q;
	int j = 0; //������
	p = head;
	while(p->next != head)
	{
		if(j == i - 1) //�ҵ�iʱ����
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
	if(j == i - 1) //�ҵ�iʱ����
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
 * ���ܣ�ɾ����i����㣬��i�����������򲻲���
 * ����������ֵ˵����
 *     ������i����ɾ���Ľ����
 *     ����ֵ��ɾ����㴢������ݣ���i�����������򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::listDelete(int i)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode p, q;
	ElemType x;
	int j = 0; //������
	p = head;
	while(p->next != head)
	{
		if(j == i - 1) //�ҵ�iʱ����
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
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��i���������ݣ���i�����������򲻲���
 * ����������ֵ˵����
 *     ������i������ȡ�Ľ����
 *     ����ֵ����㴢������ݣ���i�����������򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::getElem(int i)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int j = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(j == i) //�ҵ�iʱ����
			return temp->data;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��1����������Ϊe�Ľ��ǰһ������ֵ
 * ����������ֵ˵����
 *     ������e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ����ǰһ����㴢������ݣ�����㲻���ڻ�Ϊ��һ���򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::priorElem(ElemType e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int j = 0; //������
	temp = head;
	while(temp->next != head)
	{
		if(temp->next->data == e && temp != head) //�ҵ�eʱ����
			return temp->data;
		else if(temp->next->data == e && temp == head) //�ҵ�eΪͷ���
			return 0;
		temp = temp->next;
		j++;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��1����������Ϊe�Ľ���һ������ֵ
 * ����������ֵ˵����
 *     ������e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ�����һ����㴢������ݣ�����㲻���ڻ�Ϊ���һ���򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::nextElem(ElemType e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int j = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e && temp->next != head) //�ҵ�eʱ����
			return temp->next->data;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��i����������Ϊe�Ľ��ǰһ������ֵ
 * ����������ֵ˵����
 *     ������i����Ѱ�ҵĽ�����
 *           e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ����ǰһ����㴢������ݣ�����㲻���ڻ�Ϊ��һ���򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::priorElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int k = 0; //������
	temp = head;
	while(temp->next != head)
	{
		if(temp->next->data == e) //�ҵ�eʱ����
			k++;
		if(temp != head && k == i) //�ҵ���i��eʱ����
			return temp->data;
		else if(temp == head && k == i) //�ҵ���i��eΪͷ���
			return 0;
		temp = temp->next;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��i����������Ϊe�Ľ���һ������ֵ
 * ����������ֵ˵����
 *     ������i����Ѱ�ҵĽ�����
 *           e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ�����һ����㴢������ݣ�����㲻���ڻ�Ϊ���һ���򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
ElemType LinkedList<ElemType>::nextElem(int i, ElemType e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int k = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		if(temp->data == e) //�ҵ�eʱ����
			k++;
		if(temp->next != head && k == i) //�ҵ���i��eʱ����
			return temp->next->data;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��1����������Ϊe�Ľ����
 * ����������ֵ˵����
 *     ������e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ����ı�ţ�����㲻�����򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
int LinkedList<ElemType>::locateElem(ElemType &e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int j = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e) //�ҵ�eʱ����
			return j;
	}
	return 0; //δ�ҵ�
}

/**
 * ���ܣ���ȡ��i����������Ϊe�Ľ����
 * ����������ֵ˵����
 *     ������i����Ѱ�ҵĽ�����
 *           e����Ѱ�ҵĽ������
 *     ����ֵ���ҵ����ı�ţ�����㲻�����򷵻�0
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
int LinkedList<ElemType>::locateElem(int i, ElemType &e)
{
	if(head == NULL || head->next == head) //ͷ��㲻Ϊ��ʱ���в���
		return 0;
	pLinkNode temp;
	int j = 0, k = 0; //������
	temp = head;
	while(temp->next != head)
	{
		temp = temp->next;
		j++;
		if(temp->data == e) //�ҵ�eʱ����
			k++;
		if(k == i) //�ҵ���i��eʱ����
			return j;
	}
	return 0; //δ�ҵ�
}

#endif