
// SameGameDoc.h : interface of the CSameGameDoc class
//


#pragma once
#include "SameGameBoard.h"

class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

// Attributes
public:

// Operations
public:
	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }

	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }

	void SetWidth(int nWidth) { m_board.SetWidth(nWidth); }
	void SetHeight(int nHeight) { m_board.SetHeight(nHeight); }
	void SetColumns(int nColumns) { m_board.SetColumns(nColumns); }
	void SetRows(int nRows) { m_board.SetRows(nRows); }

	void DeleteBoard(void) { m_board.DeleteBoard(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col)
	{
		return m_board.DeleteBlocks(row, col);
	}
	int GetRemainingCount()
	{
		return m_board.GetRemainingCount();
	}

	/* Obter número de cores. */
	int GetNumColors() { 
		return m_board.GetNumColors(); 
	}

	void SetNumColors(int nColors);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/*  Instance of the game board */
	CSameGameBoard m_board;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
