
// twenty-four-calDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "twenty-four-cal.h"
#include "twenty-four-calDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <list>
#include "Calculate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtwentyfourcalDlg 对话框



CtwentyfourcalDlg::CtwentyfourcalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TWENTYFOURCAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtwentyfourcalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtwentyfourcalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FIND_RESULT, &CtwentyfourcalDlg::OnBnClickedBtnFindResult)
END_MESSAGE_MAP()


// CtwentyfourcalDlg 消息处理程序

BOOL CtwentyfourcalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT_INPUT_NUMS)->SetWindowText(L"1 2 3 4");
	GetDlgItem(IDC_EDIT_INPUT_RESLUT)->SetWindowText(L"24");
	((CEdit *)GetDlgItem(IDC_EDIT_LAST_RESULT))->SetLimitText(UINT_MAX);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtwentyfourcalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtwentyfourcalDlg::OnPaint()
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
HCURSOR CtwentyfourcalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int SplitString(LPCTSTR lpValue, std::vector<CString>& vetString, TCHAR cSplit, bool bRetEmptyStr = false) //分割字符串
{
	const TCHAR* pFirst = lpValue;
	const TCHAR* pLast = lpValue;

	while (*pFirst != 0)
	{
		//跳过cSplit 如果bRetEmptyStr==true就不跳过了
		if (!bRetEmptyStr&&*pFirst == cSplit)
		{
			pFirst++;
			continue;
		}

		pLast = pFirst;

		while (*pLast != 0)
		{
			if (*pLast == cSplit)
			{
				CString str(pFirst, pLast - pFirst);
				str.TrimLeft();
				str.TrimRight();

				//是不是返回cSplit分割的L""
				if (bRetEmptyStr || (!bRetEmptyStr&&str.GetLength() > 0))
					vetString.push_back(str);

				break;
			}

			pLast++;
		}

		if (*pLast == 0)
		{
			CString str(pFirst, pLast - pFirst);
			str.TrimLeft();
			str.TrimRight();

			if (str.GetLength() > 0)
				vetString.push_back(str);
		}

		if (*pLast != 0 && *(pLast + 1) != 0)
			pFirst = pLast + 1;
		else
			break;
	}

	return vetString.size();
}

//递归计算数字全排列
void GenerPermutations(std::vector<CString> vecStrInput, std::vector<std::list<CString>> & vecLstExpression)
{
	if (vecStrInput.size() > 0)
	{
		CString strPopNum = vecStrInput.back();
		vecStrInput.pop_back();
		if (vecLstExpression.size() > 0)
		{
			std::vector<std::list<CString>> vecLstExpressionTmp;
			for (size_t i = 0; i < vecLstExpression.size(); i++)
			{
				for (size_t j = 0; j < vecLstExpression[i].size(); j++)
				{
					std::list<CString> lstTmp = vecLstExpression[i];
					std::list<CString>::iterator it = lstTmp.begin();
					for (size_t k = 0; k < j; k++)
					{
						it++;
					}
					lstTmp.insert(it, strPopNum);
					vecLstExpressionTmp.push_back(lstTmp);
				}
				std::list<CString> lstTmp = vecLstExpression[i];
				lstTmp.push_back(strPopNum);
				vecLstExpressionTmp.push_back(lstTmp);
			}
			vecLstExpression = vecLstExpressionTmp;
		}
		else
		{
			std::list<CString> lstStrExpressionTmp;
			lstStrExpressionTmp.push_back(strPopNum);
			vecLstExpression.push_back(lstStrExpressionTmp);
		}
		GenerPermutations(vecStrInput, vecLstExpression);
	}
	else
	{
		return;
	}
}

//计算符号插入的表达式全排列
void GenerOperator(std::vector<CString> vecStrInputOp, std::vector<std::list<CString>> & vecLstOp, int nOpCount)
{
	if (vecLstOp.size() == 0 || vecLstOp.front().size() != nOpCount)
	{
		if (vecLstOp.size() > 0)
		{
			std::vector<std::list<CString>> vecLstOpTmp;
			for (size_t i = 0; i < vecStrInputOp.size(); i++)
			{
				for (size_t j = 0; j < vecLstOp.size(); j++)
				{
					std::list<CString> lstOp = vecLstOp[j];
					lstOp.push_back(vecStrInputOp[i]);
					vecLstOpTmp.push_back(lstOp);
				}
			}
			vecLstOp = vecLstOpTmp;
			GenerOperator(vecStrInputOp, vecLstOp, nOpCount);
		}
		else
		{
			for (size_t i = 0; i < vecStrInputOp.size(); i++)
			{
				std::list<CString> lstOp;
				lstOp.push_back(vecStrInputOp[i]);
				vecLstOp.push_back(lstOp);
			}
			GenerOperator(vecStrInputOp, vecLstOp, nOpCount);
		}
	}
	else
	{
		return;
	}
}

bool DoubleEqual(double left, double right)
{
	if (abs(left - right) < 0.0001)
	{
		return true;
	}
	return false;
}

void CtwentyfourcalDlg::OnBnClickedBtnFindResult()
{
	CString strNumbers;
	GetDlgItem(IDC_EDIT_INPUT_NUMS)->GetWindowText(strNumbers);

	CString strResult;
	GetDlgItem(IDC_EDIT_INPUT_RESLUT)->GetWindowText(strResult);
	double dResult = atof(CW2A(strResult, CP_UTF8));

	std::vector<CString> vecStrNums;
	SplitString(strNumbers, vecStrNums, L' ');
	if (vecStrNums.size() > 1)
	{
		//计算数字的全排列
		std::vector<std::list<CString>> vecLstExpression;
		GenerPermutations(vecStrNums, vecLstExpression);
		//for (size_t i = 0; i < vecLstExpression.size(); i++)
		//{
		//	for (auto it : vecLstExpression[i])
		//	{
		//		OutputDebugString(it);
		//		OutputDebugString(L" ");
		//	}
		//	OutputDebugString(L"\n");
		//}

		//计算运算符的全排列
		std::vector<CString> vecStrOp;
		std::vector<std::list<CString>> vecLstOp;
		vecStrOp.push_back(L"+");
		vecStrOp.push_back(L"-");
		vecStrOp.push_back(L"×");
		vecStrOp.push_back(L"÷");
		GenerOperator(vecStrOp, vecLstOp, vecStrNums.size() - 1);
		//for (size_t i = 0; i < vecLstOp.size(); i++)
		//{
		//	for (auto it : vecLstOp[i])
		//	{
		//		OutputDebugString(it);
		//		OutputDebugString(L" ");
		//	}
		//	OutputDebugString(L"\n");
		//}

		//拼接表达式同时计算值，如果值符合要求，则加入到表达式结果集合
		std::vector<CString> vecExpressionResult;
		for (auto itNums : vecLstExpression)
		{
			for (auto itOps : vecLstOp)
			{
				CString strExpression;
				std::list<CString>::iterator itOp = itOps.begin();
				for (auto itNum : itNums)
				{
					strExpression += itNum;
					if (itOp != itOps.end())
					{
						strExpression += *itOp;
						itOp++;
					}
					else
					{
						strExpression += L"=";
					}
				}
				double dRet;
				int nErr;
				BOOL bRet = EvaluateExpression(strExpression, dRet, nErr);
				if (bRet)
				{
					if (DoubleEqual(dRet, dResult))
					{
						vecExpressionResult.push_back(strExpression);
					}
				}
			}
		}

		//输出结果
		CString strLastResult;
		for (auto it : vecExpressionResult)
		{
			strLastResult += it;
			strLastResult += strResult;
			strLastResult += L"\r\n";
		}
		CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LAST_RESULT);
		if (pEdit && ::IsWindow(pEdit->GetSafeHwnd()))
		{
			pEdit->SetWindowText(strLastResult);
		}
	}
}
