#include "pch.h"
#include "CGatePane.h"
#include "resource.h"

// GatePane.cpp
BEGIN_MESSAGE_MAP(CGatePane, CDockablePane)
    ON_WM_CREATE()
    ON_BN_CLICKED(ID_GATE_AND, &CGatePane::OnBnClickedAnd)
    ON_BN_CLICKED(ID_GATE_OR, &CGatePane::OnBnClickedOr)
    ON_BN_CLICKED(ID_GATE_NOT, &CGatePane::OnBnClickedNot)
END_MESSAGE_MAP()

int CGatePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Button dimensions
    const int BUTTON_WIDTH = 60;    // Smaller width
    const int BUTTON_HEIGHT = 30;   // Smaller height
    const int LEFT_MARGIN = 5;      // Small margin from left pane
    const int TOP_MARGIN = 50;      // Starting point from top
    const int BUTTON_SPACING = 10;  // Space between buttons

    // Calculate positions with consistent spacing
    m_btnAND.Create(_T("AND"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        CRect(LEFT_MARGIN, 
              TOP_MARGIN, 
              LEFT_MARGIN + BUTTON_WIDTH, 
              TOP_MARGIN + BUTTON_HEIGHT), 
        this, ID_GATE_AND);

    m_btnOR.Create(_T("OR"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        CRect(LEFT_MARGIN, 
              TOP_MARGIN + BUTTON_HEIGHT + BUTTON_SPACING, 
              LEFT_MARGIN + BUTTON_WIDTH, 
              TOP_MARGIN + (BUTTON_HEIGHT * 2) + BUTTON_SPACING), 
        this, ID_GATE_OR);

    m_btnNOT.Create(_T("NOT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
        CRect(LEFT_MARGIN, 
              TOP_MARGIN + (BUTTON_HEIGHT * 2) + (BUTTON_SPACING * 2), 
              LEFT_MARGIN + BUTTON_WIDTH, 
              TOP_MARGIN + (BUTTON_HEIGHT * 3) + (BUTTON_SPACING * 2)), 
        this, ID_GATE_NOT);

    return 0;
}

void CGatePane::OnBnClickedAnd()
{   
   // AfxMessageBox(_T("AND button clicked!"));
    // AfxGetMainWnd()->SendMessage(WM_USER + 1, ID_GATE_AND);

    CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetMainWnd();
    if (pFrame)
    {
        CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
        if (pChild)
        {
            CView* pView = (CView*)pChild->GetActiveView();
            if (pView)
            {
                pView->SendMessage(WM_USER + 1, ID_GATE_AND);
            }
        }
    }
}

void CGatePane::OnBnClickedOr()
{
    CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
    if (pFrame)
    {
        CView* pView = pFrame->GetActiveView();
        if (pView)
        {
            pView->SendMessage(WM_USER + 1, ID_GATE_OR);
        }
    }
}

void CGatePane::OnBnClickedNot()
{
    CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
    if (pFrame)
    {
        CView* pView = pFrame->GetActiveView();
        if (pView)
        {
            pView->SendMessage(WM_USER + 1, ID_GATE_NOT);
        }
    }
}

void CGatePane::SendGateInsertMessage(UINT gateID)
{
    CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
    if (pFrame)
    {
        CView* pView = pFrame->GetActiveView();
        if (pView)
        {
            pView->SendMessage(WM_USER + 1, gateID);
        }
    }
}




