#include "pch.h"
#include "framework.h"
#include "MainProj.h"
#include "MainProjDoc.h"
#include "MainProjView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainProjView, CView)

BEGIN_MESSAGE_MAP(CMainProjView, CView)
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainProjView::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_MESSAGE(WM_USER + 1, &CMainProjView::OnGateInsert)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CMainProjView::CMainProjView() noexcept
    : m_CurrentGateResourceID(0), m_IsPlacingGate(false)
{
}

CMainProjView::~CMainProjView()
{
    if (m_hBackgroundBitmap)
        ::DeleteObject(m_hBackgroundBitmap);

    for (int i = 0; i < m_GateImages.GetSize(); ++i) {
        delete m_GateImages[i];  // Safe delete
    }
    m_GateImages.RemoveAll();
}

BOOL CMainProjView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

LRESULT CMainProjView::OnGateInsert(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("Control Reached Here!"));
    m_CurrentGateResourceID = static_cast<int>(wParam);
    if (m_CurrentGateResourceID != 0)
    {
        m_IsPlacingGate = true;
        AfxMessageBox(_T("Click on screen to place the gate"));
    }
    return 0;
}

void CMainProjView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CMainProjView::OnPreparePrinting(CPrintInfo* pInfo)
{
    return DoPreparePrinting(pInfo);
}

void CMainProjView::OnBeginPrinting(CDC*, CPrintInfo*) {}
void CMainProjView::OnEndPrinting(CDC*, CPrintInfo*) {}

void CMainProjView::OnRButtonUp(UINT, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CMainProjView::OnContextMenu(CWnd*, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// MainProj/MainProjView.cpp
void CMainProjView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_IsPlacingGate && m_CurrentGateResourceID != 0)
    {
        // Set the background bitmap to the selected gate's bitmap
        if (m_hBackgroundBitmap)
        {
            ::DeleteObject(m_hBackgroundBitmap);
            m_hBackgroundBitmap = nullptr;
        }
        m_BackgroundResourceID = m_CurrentGateResourceID;
        m_hBackgroundBitmap = (HBITMAP)::LoadImage(
            AfxGetInstanceHandle(),
            MAKEINTRESOURCE(m_BackgroundResourceID),
            IMAGE_BITMAP,
            0, 0,
            LR_CREATEDIBSECTION);

        if (!m_hBackgroundBitmap)
        {
            AfxMessageBox(_T("Failed to load background bitmap."), MB_ICONERROR);
        }

        Invalidate();
        m_IsPlacingGate = false;
    }
    CView::OnLButtonDown(nFlags, point);
}

void CMainProjView::OnDraw(CDC* pDC)
{
    // Draw background bitmap if set
    if (m_hBackgroundBitmap)
    {
        CDC memDC;
        memDC.CreateCompatibleDC(pDC);
        HBITMAP oldBmp = (HBITMAP)memDC.SelectObject(m_hBackgroundBitmap);

        BITMAP bmpInfo;
        ::GetObject(m_hBackgroundBitmap, sizeof(BITMAP), &bmpInfo);

        // Stretch to fill the client area
        CRect clientRect;
        GetClientRect(&clientRect);
        pDC->StretchBlt(
            0, 0, clientRect.Width(), clientRect.Height(),
            &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight,
            SRCCOPY
        );

        memDC.SelectObject(oldBmp);
    }

    // Optionally, draw gates or other elements here...
}

#ifdef _DEBUG
void CMainProjView::AssertValid() const { CView::AssertValid(); }
void CMainProjView::Dump(CDumpContext& dc) const { CView::Dump(dc); }
CMainProjDoc* CMainProjView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjDoc)));
    return (CMainProjDoc*)m_pDocument;
}
#endif
