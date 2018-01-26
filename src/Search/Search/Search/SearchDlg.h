
// SearchDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "sbt.h"
#include "SBT.h"
#include "WordSegmentation.h"
#include "CharString.h"
#include "Doc.h"
#include "DocLink.h"
#include "Hash.h"
#include "LinkedList.h"
#include "WordLibrary.h"

// CSearchDlg 对话框
class CSearchDlg : public CDialogEx
{
// 构造
public:
	CSearchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SEARCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString fin; //输入文件
	CString fout; //输出文件
	CString phrase; //单个查询短语
	int web; //网页编号
	CListCtrl list; //列表控件
	SBT tree; //平衡树文档链表
	WordSegmentation segment; //分词共计
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSingle();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOpenSearch();
	afx_msg void OnBnClickedOpenResult();
	afx_msg void OnBnClickedGroup();
};
