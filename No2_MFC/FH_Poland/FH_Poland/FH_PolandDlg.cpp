
// FH_PolandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FH_Poland.h"
#include "FH_PolandDlg.h"
#include "afxdialogex.h"
#include "FH_Poland_Main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Proposition* NowProposition = new Proposition("", false, Not, NULL, NULL, false);

// CFH_PolandDlg 对话框



CFH_PolandDlg::CFH_PolandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FH_POLAND_DIALOG, pParent)
	, Normal_Str(_T(""))
	, Poland_Str(_T(""))
	, Rev_Poland_Str(_T(""))
	, Pr_Disj_Str(_T(""))
	, Pri_Conj_Str(_T(""))
	, Value_Table_Str(_T(""))
	, Values_Str(_T(""))
	, Value_Names_Str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFH_PolandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E1, Normal_Str);
	DDX_Text(pDX, IDC_E2, Poland_Str);
	DDX_Text(pDX, IDC_E3, Rev_Poland_Str);
	DDX_Text(pDX, IDC_E4, Pr_Disj_Str);
	DDX_Text(pDX, IDC_E5, Pri_Conj_Str);
	DDX_Text(pDX, IDC_E6, Value_Table_Str);
	DDX_Text(pDX, IDC_E7, Values_Str);
	DDX_Text(pDX, IDC_E8, Value_Names_Str);
}

BEGIN_MESSAGE_MAP(CFH_PolandDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_E1, &CFH_PolandDlg::OnEnChangeE1)
	ON_EN_CHANGE(IDC_E7, &CFH_PolandDlg::OnEnChangeE7)
	ON_EN_CHANGE(IDC_E8, &CFH_PolandDlg::OnEnChangeE8)
END_MESSAGE_MAP()


// CFH_PolandDlg 消息处理程序

BOOL CFH_PolandDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFH_PolandDlg::OnPaint()
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
HCURSOR CFH_PolandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFH_PolandDlg::OnEnChangeE1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData();
	string NewString = (CStringA(Normal_Str)).GetBuffer(0);
	if (NewString.length() == 0)
	{
		Value_Names_Str = Value_Table_Str = Pri_Conj_Str = Pr_Disj_Str = Rev_Poland_Str = Poland_Str = "请输入命题的中缀形式！！";
	}
	else if (NowProposition->check(NewString))
	{
		NowProposition->clear();
		NowProposition = NowProposition->GetProposition(NewString, NewString.length());
		NowProposition->SetName(NewString, NowProposition);
		Poland_Str = NowProposition->ToPoland().c_str();
		Rev_Poland_Str = NowProposition->ToReversePoland().c_str();
		NowProposition->PrincipalDisjunctiveNormalForm();
		Pr_Disj_Str = NowProposition->PriDisNormalForm.c_str();
		NowProposition->PrincipalConjunctiveNormalForm();
		Pri_Conj_Str = NowProposition->PriConjNormalForm.c_str();
		NowProposition->TruthValueTable();
		Value_Table_Str = NowProposition->TruthValueString.c_str();
		Value_Names_Str = NowProposition->TruthValueHead.c_str();
		Values_Str = NowProposition->TruthValueNums.c_str();
	}
	else
	{
		Value_Names_Str = Value_Table_Str = Pri_Conj_Str = Pr_Disj_Str = Rev_Poland_Str = Poland_Str = "括号匹配出错！";
	}
	UpdateData(FALSE);
	// TODO:  Add your control notification handler code here
}


void CFH_PolandDlg::OnEnChangeE7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData();
	NowProposition->clear();
	int AtomsNum = NowProposition->SetHeads((CStringA(Value_Names_Str)).GetBuffer(0));
	if (AtomsNum == 0)
	{
		Normal_Str = Value_Table_Str = Pri_Conj_Str = Pr_Disj_Str = Rev_Poland_Str = Poland_Str = "请输入命题变量（在真值表上方的表内），用空格隔开不同变量！！！";
	}
	else
	{
		string ValuesString = (CStringA(Values_Str)).GetBuffer(0);
		if (ValuesString.length() >= pow(2, AtomsNum))
		{
			NowProposition->SetValuesGetPri(ValuesString);
			string NewString;
			string tempDis = NowProposition->PriDisNormalForm, tempCon = NowProposition->PriConjNormalForm, tempValues = NowProposition->TruthValueNums;
			if ((NowProposition->PriDisNormalForm.length() <= NowProposition->PriConjNormalForm.length() && NowProposition->PriDisNormalForm.length() > 2) || NowProposition->PriConjNormalForm.length() < 2)
				NewString = NowProposition->PriDisNormalForm;
			else
				NewString = NowProposition->PriConjNormalForm;
			Normal_Str = NewString.c_str();
			NowProposition = NowProposition->GetProposition(NewString, NewString.length());
			NowProposition->SetName(NewString, NowProposition);
			Poland_Str = NowProposition->ToPoland().c_str();
			Rev_Poland_Str = NowProposition->ToReversePoland().c_str();
			//NowProposition->PrincipalDisjunctiveNormalForm();
			Pr_Disj_Str = tempDis.c_str();
			//NowProposition->PrincipalConjunctiveNormalForm();
			Pri_Conj_Str = tempCon.c_str();
			NowProposition->TruthValueNums = tempValues;
			Values_Str = NowProposition->TruthValueNums.c_str();
			NowProposition->SetBases(AtomsNum, true);
			Value_Table_Str = NowProposition->TruthValueString.c_str();
		}
		else
		{
			Normal_Str = Value_Table_Str = Pri_Conj_Str = Pr_Disj_Str = Rev_Poland_Str = Poland_Str = "命题变量个数小于真值表真值所需个数！请检查真值！";
			NowProposition->SetBases(AtomsNum, false);
			Value_Table_Str = NowProposition->TruthValueString.c_str();
		}
	}
	UpdateData(FALSE);
	// TODO:  Add your control notification handler code here
}

void CFH_PolandDlg::OnEnChangeE8()
{
	CFH_PolandDlg::OnEnChangeE7();
}