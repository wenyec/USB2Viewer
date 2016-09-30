// VidUSB2Doc.cpp : implementation of the CVidUSB2Doc class
//

#include "stdafx.h"
#include "VidUSB2.h"

#include "VidUSB2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2Doc

IMPLEMENT_DYNCREATE(CVidUSB2Doc, CDocument)

BEGIN_MESSAGE_MAP(CVidUSB2Doc, CDocument)
	//{{AFX_MSG_MAP(CVidUSB2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2Doc construction/destruction

CVidUSB2Doc::CVidUSB2Doc()
{
	// TODO: add one-time construction code here

}

CVidUSB2Doc::~CVidUSB2Doc()
{
}

BOOL CVidUSB2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVidUSB2Doc serialization

void CVidUSB2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2Doc diagnostics

#ifdef _DEBUG
void CVidUSB2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVidUSB2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2Doc commands
