
// SearchDlg.h : ͷ�ļ�
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

// CSearchDlg �Ի���
class CSearchDlg : public CDialogEx
{
// ����
public:
	CSearchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SEARCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString fin; //�����ļ�
	CString fout; //����ļ�
	CString phrase; //������ѯ����
	int web; //��ҳ���
	CListCtrl list; //�б�ؼ�
	SBT tree; //ƽ�����ĵ�����
	WordSegmentation segment; //�ִʹ���
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSingle();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOpenSearch();
	afx_msg void OnBnClickedOpenResult();
	afx_msg void OnBnClickedGroup();
};
