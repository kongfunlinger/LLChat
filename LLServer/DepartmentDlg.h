#pragma once
#include "../Controls/StaticText.h"
#include "../Controls/GlassButton.h"
#include "LLMysqlOperate.h"

// CDepartmentDlg dialog

class CDepartmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDepartmentDlg)

public:
	CDepartmentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDepartmentDlg();

// Dialog Data
	enum { IDD = IDD_DEPARTMENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CTreeCtrl                m_treeDepartment;
	CStaticText              m_staCurNode;
	CStaticText              m_staCurDepartment;
	CEdit                    m_editCurNodeInfo;
	CEdit                    m_editCurDepartmentInfo;
	CGlassButton             m_btnAddDepartment;
	CGlassButton             m_btnDeleteDepartment;

	CLLMysqlOperate          m_mysqlOperate;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAddDepatment();
};
