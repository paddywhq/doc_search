
// SearchDlg.cpp : 实现文件
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


// CSearchDlg 对话框




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


// CSearchDlg 消息处理程序

BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	list.ModifyStyle(0L, LVS_REPORT);
    list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list.InsertColumn(0, _T("关键词"), LVCFMT_LEFT, 332);
	list.InsertColumn(1, _T("出现网页编号"), LVCFMT_LEFT, 100);
	list.InsertColumn(2, _T("出现次数"), LVCFMT_LEFT, 100);
	tree.buildSBT();
	segment.addWordLibrary();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * 功能：单击退出
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(); 
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
	//PostQuitMessage(0);
	UpdateData(FALSE);
}

/**
 * 功能：单击打开
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	char a, b, c, d;
	CString s;
	a = web / 1000 + 48;
	b = web / 100 % 10 + 48;
	c = web / 10 % 10 + 48;
	d = web % 10 + 48;
	s.Format(_T("SinaPage\\%c%c%c%c.shtml\\"), a, b, c, d);
	ShellExecute(NULL, _T("open"), s, NULL, NULL, SW_SHOW); //打开网页
	UpdateData(FALSE);
}

/**
 * 功能：单击查询
 * 参数及返回值说明：单击查询
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(phrase == _T("")) //若未输入短句
	{
		MessageBox(_T("请输入关键字或短句！"));
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

	//短句分词
	while(i < s.strLength())
	{
		if(s.head->ch[i] < 0)
			i += 2;
		else
			s.strDelete(i, 1);
	}
	while(s.strLength() != 0) //将已存的字符串分词完
		segment.segmentation(s);
	
	LinkedList<CharString>::pLinkNode temp = segment.word.head;
	LinkedList<Doc>::pLinkNode p;
	while(temp->next != segment.word.head) //未遍历完
	{
		temp = temp->next;
		stack.push(temp->data); //入栈
	}
	i = 0;
	while(!stack.stackEmpty()) //栈不空
	{
		s.clearString();
		stack.pop(s); //出栈
		doc.term = s;
		if(!tree.indexNode(tree.head, doc)) //若未找到
			continue;
		p = doc.docinfo.head;
		while(p->next != doc.docinfo.head) //未遍历完，加入列表
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
 * 功能：单击回车
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
	OnBnClickedSingle();
}

/**
 * 功能：单击Esc
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	UpdateData(); 
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
	//PostQuitMessage(0);
	UpdateData(FALSE);
}

/**
 * 功能：单击打开查询文档
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedOpenSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(fin == _T("")) //若未输入路径
	{
		MessageBox(_T("请输入查询文件路径！"));
		UpdateData(FALSE);
		return;
	}
	ShellExecute(NULL, _T("open"), fin, NULL, NULL, SW_SHOW);
	UpdateData(FALSE);
}

/**
 * 功能：单击打开结果文档
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedOpenResult()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(fout == _T("")) //若未输入路径
	{
		MessageBox(_T("请输入结果文件路径！"));
		UpdateData(FALSE);
		return;
	}
	ShellExecute(NULL, _T("open"), fout, NULL, NULL, SW_SHOW);
	UpdateData(FALSE);
}

/**
 * 功能：单击生成结果文档
 * 参数及返回值说明：
 *     参数：无
 *     返回值：无
 * 作者：王华清
 * 日期：2014年1月1日
 */
void CSearchDlg::OnBnClickedGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(fin == _T("")) //若未输入查询文件路径
	{
		MessageBox(_T("请输入查询文件路径！"));
		UpdateData(FALSE);
		return;
	}
	if(fout == _T("")) //若未输入结果文件路径
	{
		MessageBox(_T("请输入结果文件路径！"));
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
	while(!input.eof()) //若查询文件未读完
	{
		s.clearString();
		input.get(c);
		while(c < 0) //获得一个关键词
		{
			s.addChar(c);
			input.get(c);
		}
		doc.term = s;
		if(!tree.indexNode(tree.head, doc)) //若未找到
			continue;
		p = doc.docinfo.head;
		output<<"“";
		for(int i = 0; i < doc.term.head->length; i++)
			output<<doc.term.head->ch[i];
		output<<"”出现在"<<doc.df<<"个网页中，共出现"<<doc.occur<<"次：";
		p = doc.docinfo.head->next;
		while(true) //输出文档链表
		{
			if(p == doc.docinfo.head)
				break;
			output<<p->data.head.docID<<"号网页"<<p->data.head.times<<"次；";
			p = p->next;
		}
		output<<endl;
		if(c == '\n') //若一个查询结束
		{
			output<<"第"<<t<<"个查询结束。"<<endl<<endl;
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