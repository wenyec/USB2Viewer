// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <atlpath.h>
#include "VidUSB2.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
//custom the window
	cs.style &= (~(WS_THICKFRAME | WS_MAXIMIZEBOX) );

	return TRUE;
}

// Set the windows size when change the video settings.

void CMainFrame::UpdateWindowSize(CSize siz)
{
    static int nRecurse = 0;
    RECT rcW, rcC;
    int xExtra, yExtra;
    int cxBorder = GetSystemMetrics(SM_CXBORDER);
    int cyBorder = GetSystemMetrics(SM_CYBORDER);

    nRecurse++;

    GetWindowRect(&rcW);
    GetClientRect(&rcC);
    xExtra = rcW.right - rcW.left - rcC.right + cxBorder * 4;
    yExtra = rcW.bottom - rcW.top - rcC.bottom + cyBorder * 4;

    if( gCmdInfo.m_Count )
        yExtra += BUTTON_HEIGHT;

    rcC.right = siz.cx;
    rcC.bottom = siz.cy;
    SetWindowPos(NULL, 0, 0, rcC.right + xExtra,
        rcC.bottom + yExtra, SWP_NOZORDER | SWP_NOMOVE);

    // May need to recurse once.  But more than that means the window cannot
    // be made the size we want, trying will just stack fault.
    //
    if(
        nRecurse == 1 && 
        ((rcC.right + xExtra != rcW.right - rcW.left && siz.cx > GetSystemMetrics(SM_CXMIN)) ||
         (rcC.bottom + yExtra != rcW.bottom - rcW.top))
    )
        UpdateWindowSize(siz);

    nRecurse--;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG
