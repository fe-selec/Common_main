#pragma once

#include "resource.h"  // For ID_GATE_AND, etc.

//struct GateImage {
//    CPoint position;
//    HBITMAP hBitmap;
//
//    GateImage() : hBitmap(nullptr) {}
//
//    ~GateImage() {
//        if (hBitmap) {
//            ::DeleteObject(hBitmap);  // Proper cleanup
//            hBitmap = nullptr;
//        }
//    }
//
//    // Non-copyable to avoid bitmap ownership issues
//    GateImage(const GateImage&) = delete;
//    GateImage& operator=(const GateImage&) = delete;
//};

struct GateImage {
    CPoint position;
    UINT resourceID;
	HBITMAP hBitmap;
};

class CMainProjView : public CView
{
protected:
    CMainProjView() noexcept;
    DECLARE_DYNCREATE(CMainProjView)

protected:
    CPoint m_BitmapPos;

public:
    CMainProjDoc* GetDocument() const;
   // CArray<GateImage*, GateImage*> m_GateImages;
    int m_CurrentGateResourceID;
    bool m_IsPlacingGate;
    HBITMAP m_hBackgroundBitmap = nullptr;
    UINT m_BackgroundResourceID = 0;
    CArray<GateImage*, GateImage*> m_PlacedBitmaps;

    virtual void OnDraw(CDC* pDC);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
    virtual ~CMainProjView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg LRESULT OnGateInsert(WPARAM wParam, LPARAM lParam);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};
