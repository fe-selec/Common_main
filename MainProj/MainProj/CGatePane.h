#pragma once
#include <afxdockablepane.h>

class CGatePane : public CDockablePane
{
public:
    CButton m_btnAND, m_btnOR, m_btnNOT;

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnBnClickedAnd();
    afx_msg void OnBnClickedOr();
    afx_msg void OnBnClickedNot();
    void SendGateInsertMessage(UINT gateID);
    DECLARE_MESSAGE_MAP()
};

