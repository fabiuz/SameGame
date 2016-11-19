
// SameGameView.h : interface of the CSameGameView class
//

#pragma once


class CSameGameView : public CView
{
protected: // create from serialization only
	CSameGameView();
	DECLARE_DYNCREATE(CSameGameView)

// Attributes
public:
	CSameGameDoc* GetDocument() const;

// Operations
public:
	void ResizeWindow();
	void setColorCount(int numColors);
	void setAtivarDesativarMenu(CCmdUI * pCmdUI, int numColors);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();	
	void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLevel3cores();
	afx_msg void OnUpdateLevel3cores(CCmdUI *pCmdUI);
	afx_msg void OnLevel4cores();
	afx_msg void OnUpdateLevel4cores(CCmdUI *pCmdUI);
	afx_msg void OnLevel5cores();
	afx_msg void OnUpdateLevel5cores(CCmdUI *pCmdUI);
	afx_msg void OnLevel6cores();
	afx_msg void OnLevel7cores();
	afx_msg void OnUpdateLevel7cores(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel6cores(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

