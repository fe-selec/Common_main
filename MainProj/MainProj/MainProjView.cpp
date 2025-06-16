
// MainProjView.cpp : implementation of the CMainProjView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MainProj.h"
#endif

#include "MainProjDoc.h"
#include "MainProjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainProjView

IMPLEMENT_DYNCREATE(CMainProjView, CView)

BEGIN_MESSAGE_MAP(CMainProjView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainProjView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMainProjView construction/destruction

CMainProjView::CMainProjView() noexcept
{
	// TODO: add construction code here

}

CMainProjView::~CMainProjView()
{
}

BOOL CMainProjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMainProjView drawing

void CMainProjView::OnDraw(CDC* /*pDC*/)
{
	CMainProjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMainProjView printing


void CMainProjView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMainProjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMainProjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMainProjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMainProjView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMainProjView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMainProjView diagnostics

#ifdef _DEBUG
void CMainProjView::AssertValid() const
{
	CView::AssertValid();
}

void CMainProjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainProjDoc* CMainProjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjDoc)));
	return (CMainProjDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainProjView message handlers
