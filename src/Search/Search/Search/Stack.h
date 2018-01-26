/*
* �ļ�����Stack.h
*
* �ļ��������������ӿڵȵ������б�Stack<ElemType>
*
* �ļ����ܣ�ʵ��ջ�ࣨ��ģ�壩
*
* ���ߣ�������
*
* ���ڣ�2013��11��24��
*/
#ifndef STACK_H
#define STACK_H

/**
 * ���ܣ���������ջ�ࣨ��ģ�壩
 *       ʵ���ַ���ջʱʹ�����"Stack<�ַ�����> ������;"����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
class Stack
{
public:
	//ջ�����������
	typedef struct StackNode{
		ElemType data; //����ֵ
		struct StackNode *next; //���ָ��
	}StackNode, *pStackNode;

public:
	pStackNode head; //ջͷ���

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
 * ���ܣ����캯��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
Stack<ElemType>::Stack()
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
Stack<ElemType>::~Stack()
{
	pStackNode temp;
	while(head != NULL) //ջ��Ϊ��ʱɾ�����
	{
		temp = head;
		head = head->next;
		delete temp;
	}
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
void Stack<ElemType>::initStack()
{
	head = NULL;
}

/**
 * ���ܣ�ѹ��Ԫ��x��ջ��
 * ����������ֵ˵����
 *     ������x����ѹ���Ԫ��
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void Stack<ElemType>::push(ElemType &x)
{
	pStackNode temp;
	temp = new(StackNode); //�½����
	temp->data = x;
	temp->next = head;
	head = temp;
}

/**
 * ���ܣ�ȡ��ջ��Ԫ��
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ��ȡ����ջ��Ԫ��ֵ
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void Stack<ElemType>::pop(ElemType &x)
{
	pStackNode temp;
	temp = head;
	if(temp != NULL) //ͷ��㲻Ϊ��ʱ���в���
	{
		x = temp->data;
		head = head->next;
		delete temp;
		temp = NULL;
	}
	else //ͷ���Ϊ��ʱ
		x = 0;
}

/**
 * ���ܣ���ջ��Ԫ�ص�ֵ
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ��ջ��Ԫ��ֵ
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void Stack<ElemType>::getTop(ElemType &x)
{
	if(head == NULL) //ͷ���Ϊ��ʱ
		x = 0;
	else
		x = head->data; //ͷ��㲻Ϊ��ʱ���в���
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
bool Stack<ElemType>::stackEmpty()
{
	if(head == NULL)
		return true;
	return false;
}

/**
 * ���ܣ���ջ����
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ��ջ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
int Stack<ElemType>::stackLength()
{
	pStackNode temp;
	int i = 0; //������
	temp = head;
	while(temp != NULL) //δ��ջ��ʱ���в���
	{
		temp = temp->next;
		i++;
	}
	return i;
}

/**
 * ���ܣ����ջ
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2013��11��24��
 */
template<class ElemType>
void Stack<ElemType>::clearStack()
{
	pStackNode temp;
	while(head != NULL) //ջ��Ϊ��ʱɾ�����
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

#endif