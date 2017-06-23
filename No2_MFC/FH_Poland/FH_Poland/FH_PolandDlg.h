
// FH_PolandDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CFH_PolandDlg 对话框
class CFH_PolandDlg : public CDialogEx
{
// 构造
public:
	CFH_PolandDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FH_POLAND_DIALOG };
#endif

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
	afx_msg void OnEnChangeE1();
	afx_msg void OnEnChangeE7();
	afx_msg void OnEnChangeE8();
	// 正常形式的str（第一个框）
	CString Normal_Str;
	// 波兰式string（第二个框）
	CString Poland_Str;
	// 逆波兰式str（第三个框）
	CString Rev_Poland_Str;
	// 主析取范式string（第四个框）
	CString Pr_Disj_Str;
	// 主合取范式string（第五个框）
	CString Pri_Conj_Str;
	// 真值表（大表）
	CString Value_Table_Str;
	// 真值表（供输入的）
	CString Values_Str;
	// 真值表对应的变量名，用空格隔开
	CString Value_Names_Str;
};
