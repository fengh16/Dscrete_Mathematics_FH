
// FH_PolandDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

// CFH_PolandDlg �Ի���
class CFH_PolandDlg : public CDialogEx
{
// ����
public:
	CFH_PolandDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FH_POLAND_DIALOG };
#endif

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
	afx_msg void OnEnChangeE1();
	afx_msg void OnEnChangeE7();
	afx_msg void OnEnChangeE8();
	// ������ʽ��str����һ����
	CString Normal_Str;
	// ����ʽstring���ڶ�����
	CString Poland_Str;
	// �沨��ʽstr����������
	CString Rev_Poland_Str;
	// ����ȡ��ʽstring�����ĸ���
	CString Pr_Disj_Str;
	// ����ȡ��ʽstring���������
	CString Pri_Conj_Str;
	// ��ֵ�����
	CString Value_Table_Str;
	// ��ֵ��������ģ�
	CString Values_Str;
	// ��ֵ���Ӧ�ı��������ÿո����
	CString Value_Names_Str;
};
