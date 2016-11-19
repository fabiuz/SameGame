
// SameGameView.cpp : implementation of the CSameGameView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_3CORES, &CSameGameView::OnLevel3cores)
	ON_COMMAND(ID_LEVEL_4CORES, &CSameGameView::OnLevel4cores)
	ON_COMMAND(ID_LEVEL_5CORES, &CSameGameView::OnLevel5cores)
	ON_COMMAND(ID_LEVEL_6CORES, &CSameGameView::OnLevel6cores)
	ON_COMMAND(ID_LEVEL_7CORES, &CSameGameView::OnLevel7cores)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3CORES, &CSameGameView::OnUpdateLevel3cores)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4CORES, &CSameGameView::OnUpdateLevel4cores)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5CORES, &CSameGameView::OnUpdateLevel5cores)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6CORES, &CSameGameView::OnUpdateLevel6cores)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7CORES, &CSameGameView::OnUpdateLevel7cores)
END_MESSAGE_MAP()

// CSameGameView construction/destruction

CSameGameView::CSameGameView()
{
	// TODO: add construction code here

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSameGameView drawing

void CSameGameView::OnDraw(CDC* pDC)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//  Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	
	//  Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	
	//  Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	
	//	Draw the background first
	pDC->FillSolidRect(&rcClient, clr);

	//  Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			//  Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			//  Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			//  Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// CSameGameView diagnostics

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CSameGameView message handlers


void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	// Redimensiona a janela.
	ResizeWindow();
}

void CSameGameView::ResizeWindow()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);

	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;

	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

/*
	Quando o usuário clicar no menu, conforme a opção do menu.
	A quantidade de cores alterará.
*/
void CSameGameView::setColorCount(int numColors)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(numColors);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

/*
	Os eventos de que começam com 'OnUpdateLeve' 
	ao serem chamados dentro da função haverá uma chamada
	para este comando.
*/
void CSameGameView::setAtivarDesativarMenu(CCmdUI *pCmdUI, int numColors) {
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == numColors);
}



void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//  Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();

	//  Delete the blocks from the document
	int count = pDoc->DeleteBlocks(row, col);

	//  Check if there were any blocks deleted
	if (count > 0)
	{
		//  Force the view to redraw
		Invalidate();
		UpdateWindow();

		//  Check if the game is over
		if (pDoc->IsGameOver())
		{
			//  Get the count remaining
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),
				remaining);
			//  Display the results to the user
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::OnLevel3cores()
{
	setColorCount(3);
}


void CSameGameView::OnLevel4cores()
{
	setColorCount(4);
}


void CSameGameView::OnLevel5cores()
{
	setColorCount(5);
}


void CSameGameView::OnLevel6cores()
{
	setColorCount(6);
}

void CSameGameView::OnLevel7cores()
{
	setColorCount(7);
}

void CSameGameView::OnUpdateLevel3cores(CCmdUI *pCmdUI)
{
	setAtivarDesativarMenu(pCmdUI, 3);
}

void CSameGameView::OnUpdateLevel4cores(CCmdUI *pCmdUI)
{
	setAtivarDesativarMenu(pCmdUI, 4);
}

void CSameGameView::OnUpdateLevel5cores(CCmdUI *pCmdUI)
{
	setAtivarDesativarMenu(pCmdUI, 5);
}

void CSameGameView::OnUpdateLevel6cores(CCmdUI *pCmdUI)
{
	setAtivarDesativarMenu(pCmdUI, 6);
}

void CSameGameView::OnUpdateLevel7cores(CCmdUI *pCmdUI)
{
	setAtivarDesativarMenu(pCmdUI, 7);
}





