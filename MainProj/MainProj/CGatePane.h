#pragma once
#include <afxdockablepane.h>

class CGatePane : public CDockablePane
{
public:
    CButton m_btnAND, m_btnOR, m_btnNOT;

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};

