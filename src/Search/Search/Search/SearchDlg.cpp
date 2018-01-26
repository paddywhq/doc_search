
// SearchDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include "SBT.h"
#include "WordSegmentation.h"
#include "CharString.h"
#include "Doc.h"
#include "DocLink.h"
#include "Hash.h"
#include "LinkedList.h"
#include "WordLibrary.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSearchDlg �Ի���




CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchDlg::IDD, pParent)
	, fin(_T("query.txt"))
	, fout(_T(""))
	, phrase(_T(""))
	, web(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT, fin);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, fout);
	DDX_Text(pDX, IDC_EDIT_PHRASE, phrase);
	DDX_Text(pDX, IDC_EDIT_WEB, web);
	DDV_MinMaxInt(pDX, web, 1, 2500);
	DDX_Control(pDX, IDC_LIST, list);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSE, &CSearchDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_OPEN, &CSearchDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SINGLE, &CSearchDlg::OnBnClickedSingle)
	ON_BN_CLICKED(IDOK, &CSearchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSearchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPEN_SEARCH, &CSearchDlg::OnBnClickedOpenSearch)
	ON_BN_CLICKED(IDC_OPEN_RESULT, &CSearchDlg::OnBnClickedOpenResult)
	ON_BN_CLICKED(IDC_GROUP, &CSearchDlg::OnBnClickedGroup)
END_MESSAGE_MAP()


// CSearchDlg ��Ϣ�������

BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	list.ModifyStyle(0L, LVS_REPORT);
    list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list.InsertColumn(0, _T("�ؼ���"), LVCFMT_LEFT, 332);
	list.InsertColumn(1, _T("������ҳ���"), LVCFMT_LEFT, 100);
	list.InsertColumn(2, _T("���ִ���"), LVCFMT_LEFT, 100);
	tree.buildSBT();
	segment.addWordLibrary();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * ���ܣ������˳�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(); 
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
	//PostQuitMessage(0);
	UpdateData(FALSE);
}

/**
 * ���ܣ�������
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	char a, b, c, d;
	CString s;
	a = web / 1000 + 48;
	b = web / 100 % 10 + 48;
	c = web / 10 % 10 + 48;
	d = web % 10 + 48;
	s.Format(_T("SinaPage\\%c%c%c%c.shtml\\"), a, b, c, d);
	ShellExecute(NULL, _T("open"), s, NULL, NULL, SW_SHOW); //����ҳ
	UpdateData(FALSE);
}

/**
 * ���ܣ�������ѯ
 * ����������ֵ˵����������ѯ
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedSingle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(phrase == _T("")) //��δ����̾�
	{
		MessageBox(_T("������ؼ��ֻ�̾䣡"));
		UpdateData(FALSE);
		return;
	}
	Stack<CharString> stack;
	stack.initStack();
	CharString s;
	CString str, t;
	DocLink doc;
	USES_CONVERSION;
	char* c = T2A(phrase);
	s.initString();
	s.strAssign(c);
	while(list.DeleteItem(0));
	segment.word.clearList();
	int i = 0;

	//�̾�ִ�
	while(i < s.strLength())
	{
		if(s.head->ch[i] < 0)
			i += 2;
		else
			s.strDelete(i, 1);
	}
	while(s.strLength() != 0) //���Ѵ���ַ����ִ���
		segment.segmentation(s);
	
	LinkedList<CharString>::pLinkNode temp = segment.word.head;
	LinkedList<Doc>::pLinkNode p;
	while(temp->next != segment.word.head) //δ������
	{
		temp = temp->next;
		stack.push(temp->data); //��ջ
	}
	i = 0;
	while(!stack.stackEmpty()) //ջ����
	{
		s.clearString();
		stack.pop(s); //��ջ
		doc.term = s;
		if(!tree.indexNode(tree.head, doc)) //��δ�ҵ�
			continue;
		p = doc.docinfo.head;
		while(p->next != doc.docinfo.head) //δ�����꣬�����б�
		{
			p = p->next;
			str = A2T(s.head->ch);
			list.InsertItem(i, str);
			str.Format(_T("%d"), p->data.head.docID);
			list.SetItemText(i, 1, str);
			str.Format(_T("%d"), p->data.head.times);
			list.SetItemText(i, 2, str);
			i++;
		}
	}
	s.destroyString();
	doc.docinfo.head = NULL;
	stack.clearStack();
	UpdateData(FALSE);
}

/**
 * ���ܣ������س�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnOK();
	OnBnClickedSingle();
}

/**
 * ���ܣ�����Esc
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	UpdateData(); 
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
	//PostQuitMessage(0);
	UpdateData(FALSE);
}

/**
 * ���ܣ������򿪲�ѯ�ĵ�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedOpenSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(fin == _T("")) //��δ����·��
	{
		MessageBox(_T("�������ѯ�ļ�·����"));
		UpdateData(FALSE);
		return;
	}
	ShellExecute(NULL, _T("open"), fin, NULL, NULL, SW_SHOW);
	UpdateData(FALSE);
}

/**
 * ���ܣ������򿪽���ĵ�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedOpenResult()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(fout == _T("")) //��δ����·��
	{
		MessageBox(_T("���������ļ�·����"));
		UpdateData(FALSE);
		return;
	}
	ShellExecute(NULL, _T("open"), fout, NULL, NULL, SW_SHOW);
	UpdateData(FALSE);
}

/**
 * ���ܣ��������ɽ���ĵ�
 * ����������ֵ˵����
 *     ��������
 *     ����ֵ����
 * ���ߣ�������
 * ���ڣ�2014��1��1��
 */
void CSearchDlg::OnBnClickedGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(fin == _T("")) //��δ�����ѯ�ļ�·��
	{
		MessageBox(_T("�������ѯ�ļ�·����"));
		UpdateData(FALSE);
		return;
	}
	if(fout == _T("")) //��δ�������ļ�·��
	{
		MessageBox(_T("���������ļ�·����"));
		UpdateData(FALSE);
		return;
	}
	ifstream input;
	ofstream output;
	input.open(fin);
	output.open(fout);
	DocLink doc;
	CharString s;
	int t = 1;
	LinkedList<Doc>::pLinkNode p;
	char c;
	while(!input.eof()) //����ѯ�ļ�δ����
	{
		s.clearString();
		input.get(c);
		while(c < 0) //���һ���ؼ���
		{
			s.addChar(c);
			input.get(c);
		}
		doc.term = s;
		if(!tree.indexNode(tree.head, doc)) //��δ�ҵ�
			continue;
		p = doc.docinfo.head;
		output<<"��";
		for(int i = 0; i < doc.term.head->length; i++)
			output<<doc.term.head->ch[i];
		output<<"��������"<<doc.df<<"����ҳ�У�������"<<doc.occur<<"�Σ�";
		p = doc.docinfo.head->next;
		while(true) //����ĵ�����
		{
			if(p == doc.docinfo.head)
				break;
			output<<p->data.head.docID<<"����ҳ"<<p->data.head.times<<"�Σ�";
			p = p->next;
		}
		output<<endl;
		if(c == '\n') //��һ����ѯ����
		{
			output<<"��"<<t<<"����ѯ������"<<endl<<endl;
			t++;
		}
	}
	s.destroyString();
	doc.docinfo.head = NULL;
	input.sync();
	input.clear();
	output.clear();
	input.close();
	output.close();
	UpdateData(FALSE);
}