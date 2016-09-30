// VidUSB2.h : main header file for the VIDUSB2 application
//

#if !defined(AFX_VIDUSB2_H__3D27B327_748C_479D_97B3_72911CFA0770__INCLUDED_)
#define AFX_VIDUSB2_H__3D27B327_748C_479D_97B3_72911CFA0770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CMyCommandLine :
    public CCommandLineInfo
{
public:
    CPoint m_One;
    CPoint m_Two;
    bool m_SwitchButton;
    bool m_StartSecond;
    int m_Count;

    CMyCommandLine()
        : m_SwitchButton( false )
        , m_StartSecond( false )
        , m_Count( 0 )
    {
    }

    void Debug()
    {
        CString sz;
        sz.Format( _T("CMD: %d, (%d,%d) - (%d,%d)"),
            m_Count,
            m_One.x, m_One.y,
            m_Two.x, m_Two.y
        );
        OutputDebugString( sz );
    }

    void Switch()
    {
        CPoint temp = m_One;
        m_One = m_Two;
        m_Two = temp;
    }

    void ParseParam( const TCHAR* pszParam, BOOL bFlag, BOOL bLast )
    {
        switch( m_Count++ )
        {
            case 0:
                m_One.x = _ttoi( pszParam );
                if( bFlag ) m_One.x = -m_One.x;
                break;
            case 1:
                m_One.y = _ttoi( pszParam );
                if( bFlag ) m_One.y = -m_One.y;
                break;
            case 2:
                m_SwitchButton = true;
                m_Two.x = _ttoi( pszParam );
                if( bFlag ) m_Two.x = -m_Two.x;
                break;
            case 3:
                m_Two.y = _ttoi( pszParam );
                if( bFlag ) m_Two.y = -m_Two.y;
                break;
            case 4:
                Switch();
                break;
        }
    }
};

extern CMyCommandLine gCmdInfo;

#define BUTTON_WIDTH    120
#define BUTTON_HEIGHT   32

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2App:
// See VidUSB2.cpp for the implementation of this class
//

class CVidUSB2App : public CWinApp
{
public:
	CVidUSB2App();

	CString m_strBrand;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVidUSB2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVidUSB2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDUSB2_H__3D27B327_748C_479D_97B3_72911CFA0770__INCLUDED_)
