// VidUSB2Doc.h : interface of the CVidUSB2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDUSB2DOC_H__EA64B6FC_CE8C_4498_A4A2_54E55D750574__INCLUDED_)
#define AFX_VIDUSB2DOC_H__EA64B6FC_CE8C_4498_A4A2_54E55D750574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVidUSB2Doc : public CDocument
{
protected: // create from serialization only
	CVidUSB2Doc();
	DECLARE_DYNCREATE(CVidUSB2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVidUSB2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVidUSB2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVidUSB2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDUSB2DOC_H__EA64B6FC_CE8C_4498_A4A2_54E55D750574__INCLUDED_)
