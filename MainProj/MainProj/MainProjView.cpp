#include "pch.h"
#include "framework.h"
#include "MainProj.h"
#include "MainProjDoc.h"
#include "MainProjView.h"
#include "resource.h"

#define IDB_BITMAP8 319 // Example resource ID for a gate image

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
    ON_MESSAGE(WM_USER + 2, &CMainProjView::OnGateInsert)
    ON_MESSAGE(WM_USER + 3, &CMainProjView::OnGateInsert)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CMainProjView::CMainProjView() noexcept
    : m_CurrentGateResourceID(0), m_IsPlacingGate(false)
{
}

CMainProjView::~CMainProjView()
{
    for (int i = 0; i < m_PlacedBitmaps.GetSize(); ++i) {
        if (m_PlacedBitmaps[i]->hBitmap)
            ::DeleteObject(m_PlacedBitmaps[i]->hBitmap);
        delete m_PlacedBitmaps[i];
    }
    m_PlacedBitmaps.RemoveAll();
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


void CMainProjView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_IsPlacingGate && m_CurrentGateResourceID != 0)
    {
        // Set the background bitmap to the selected gate's bitmap
       /* if (m_hBackgroundBitmap)
        {
            ::DeleteObject(m_hBackgroundBitmap);
            m_hBackgroundBitmap = nullptr;
        }*/

        GateImage* p = new GateImage;
        p->position = point;
		p->resourceID = IDR_MENU_IMAGES;
        p->hBitmap = (HBITMAP)::LoadImage(
            AfxGetInstanceHandle(),
            MAKEINTRESOURCE(p->resourceID),
            IMAGE_BITMAP,
            0, 0,
			LR_CREATEDIBSECTION);
       /* m_BackgroundResourceID = IDR_MENU_IMAGES;
        m_hBackgroundBitmap = (HBITMAP)::LoadImage(
            AfxGetInstanceHandle(),
            MAKEINTRESOURCE(m_BackgroundResourceID),
            IMAGE_BITMAP,
            0, 0,
            LR_CREATEDIBSECTION);*/

        /*if (!m_hBackgroundBitmap)
        {
            AfxMessageBox(_T("Failed to load background bitmap."), MB_ICONERROR);
        }*/
        if (!p->hBitmap) {
            delete p;
			AfxMessageBox(_T("Failed to load gate bitmap."), MB_ICONERROR);
        }
        else {
			m_PlacedBitmaps.Add(p);
        }
        //m_BitmapPos = point;

        Invalidate();
        m_IsPlacingGate = false;
    }
    CView::OnLButtonDown(nFlags, point);
}

//void CMainProjView::OnDraw(CDC* pDC)
//{
//    // Draw background bitmap if set
//    if (m_hBackgroundBitmap)
//    {
//        CDC memDC;
//        memDC.CreateCompatibleDC(pDC);
//        HBITMAP oldBmp = (HBITMAP)memDC.SelectObject(m_hBackgroundBitmap);
//
//        BITMAP bmpInfo;
//        ::GetObject(m_hBackgroundBitmap, sizeof(BITMAP), &bmpInfo);
//
//        // Stretch to fill the client area
//       /* CRect clientRect;
//        GetClientRect(&clientRect);
//        pDC->StretchBlt(
//            0, 0, clientRect.Width(), clientRect.Height(),
//            &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight,
//            SRCCOPY
//        );*/
//
//        pDC->BitBlt(
//            m_BitmapPos.x, m_BitmapPos.y,
//            bmpInfo.bmWidth*100, bmpInfo.bmHeight*100,
//            &memDC, 0, 0, SRCCOPY
//        );
//
//        memDC.SelectObject(oldBmp);
//    }
//
//    // Optionally, draw gates or other elements here...
//}

void CMainProjView::OnDraw(CDC* pDC)
{
    for (int i = 0; i < m_PlacedBitmaps.GetSize(); ++i)
    {
        GateImage* gate = m_PlacedBitmaps[i];
        if (gate->hBitmap)
        {
            CDC memDC;
            memDC.CreateCompatibleDC(pDC);
            HBITMAP oldBmp = (HBITMAP)memDC.SelectObject(gate->hBitmap);

            BITMAP bmpInfo;
            ::GetObject(gate->hBitmap, sizeof(BITMAP), &bmpInfo);

            pDC->BitBlt(
                gate->position.x, gate->position.y,
                bmpInfo.bmWidth, bmpInfo.bmHeight,
                &memDC, 0, 0, SRCCOPY
            );

            memDC.SelectObject(oldBmp);
        }
    }
}



//void CMainProjView::OnDraw(CDC* pDC)
//{
//    // Try to load the test bitmap resource
//    CBitmap bitmap;
//    if (bitmap.LoadBitmap(IDR_PROPERTIES))
//    {
//        CDC memDC;
//        memDC.CreateCompatibleDC(pDC);
//        CBitmap* pOldBmp = memDC.SelectObject(&bitmap);
//
//        BITMAP bmpInfo;
//        bitmap.GetBitmap(&bmpInfo);
//
//        // Draw at (10,10)
//        pDC->BitBlt(
//            10, 10,
//            bmpInfo.bmWidth, bmpInfo.bmHeight,
//            &memDC, 0, 0, SRCCOPY
//        );
//
//        memDC.SelectObject(pOldBmp);
//    }
//    else
//    {
//        AfxMessageBox(_T("Failed to load test bitmap!"), MB_ICONERROR);
//    }
//}



#ifdef _DEBUG
void CMainProjView::AssertValid() const { CView::AssertValid(); }
void CMainProjView::Dump(CDumpContext& dc) const { CView::Dump(dc); }
CMainProjDoc* CMainProjView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjDoc)));
    return (CMainProjDoc*)m_pDocument;
}
#endif
