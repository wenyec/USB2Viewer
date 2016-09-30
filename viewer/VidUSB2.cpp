// VidUSB2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VidUSB2.h"

#include "MainFrm.h"
#include "VidUSB2Doc.h"
#include "VidUSB2View.h"

#include "CustomIds.h"
#include "Customize.h"

#pragma comment( lib, "strmiids.lib" )
HINSTANCE g_hInst = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2App

BEGIN_MESSAGE_MAP(CVidUSB2App, CWinApp)
	//{{AFX_MSG_MAP(CVidUSB2App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2App construction

CVidUSB2App::CVidUSB2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CVidUSB2App object

CVidUSB2App theApp;
CCustomize Custom;
CMyCommandLine gCmdInfo;

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2App initialization
BOOL CVidUSB2App::InitInstance()
{
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    AfxEnableControlContainer();

    Custom.Register( theApp.m_hInstance );
    m_strBrand = Custom.Get( IDS_VIEWERTITLE );

    // Change the registry key under which our settings are stored.

    SetRegistryKey(_T("VideologyViewer"));

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CVidUSB2Doc),
        RUNTIME_CLASS(CMainFrame),       // main SDI frame window
        RUNTIME_CLASS(CVidUSB2View));
    AddDocTemplate(pDocTemplate);

    // Parse command line.
    ParseCommandLine(gCmdInfo);
    ProcessShellCommand(gCmdInfo);
    gCmdInfo.Debug();

    // The one and only window has been initialized, so show and update it.
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->SetWindowText( m_strBrand ); // main window text
    m_pMainWnd->UpdateWindow();
    if( gCmdInfo.m_Count )
    {
        CRect rct;
        m_pMainWnd->GetWindowRect( &rct );

        CPoint iDelta(
            rct.left - gCmdInfo.m_One.x,
            rct.top - gCmdInfo.m_One.y
        );

        rct -= iDelta;
        m_pMainWnd->MoveWindow( &rct );
    }
    else
    {
        m_pMainWnd->CenterWindow (NULL);
    }

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strVersion;
	CString	m_strPlugin;
	CString	m_strDriver;
	CString	m_strCompany;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strVersion = Custom.Get( IDS_VIEWERTITLE );
	m_strCompany = Custom.Get( IDS_MANUFACTURER );
	m_strPlugin = _T("Proxy Plugin ");
	m_strDriver = _T("Camera Driver ");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_STATIC_PLUGIN, m_strPlugin);
	DDX_Text(pDX, IDC_STATIC_DRIVER, m_strDriver);
	DDX_Text(pDX, IDC_STATIC_COMPANY, m_strCompany);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString GetVersionString( LPCTSTR szComponent )
{
    CString szVersion;
    DWORD dwHandle, dwLen;

    dwLen = GetFileVersionInfoSize( szComponent, &dwHandle );
    if( dwLen )	{
        char * lpData = new char[ dwLen ];
        if( GetFileVersionInfo(szComponent, dwHandle, dwLen, lpData ) )
        {
            VS_FIXEDFILEINFO *pFileInfo;
            UINT BufLen;
            if( VerQueryValue( lpData, _T("\\"), (void**)&pFileInfo, &BufLen) ) 
            {
                szVersion.Format(
                    _T("Version %d.%d.%d"),
                    HIWORD(pFileInfo->dwFileVersionMS),
                    LOWORD(pFileInfo->dwFileVersionMS),
                    pFileInfo->dwFileVersionLS
                );
            }
        }

        delete [] lpData;
    }

    return szVersion;
}

// App command to run the dialog
void CVidUSB2App::OnAppAbout()
{
    CAboutDlg aboutDlg;
    TCHAR szExe[MAX_PATH];
    GetModuleFileName( NULL, szExe, MAX_PATH );

    CString szDriver;
    GetSystemDirectory( szDriver.GetBufferSetLength(MAX_PATH), MAX_PATH );
    szDriver.ReleaseBuffer();
    szDriver += _T("\\Drivers\\") + Custom.Get(IDS_DRIVERNAME);

    aboutDlg.m_strVersion += GetVersionString( szExe );
    aboutDlg.m_strPlugin += GetVersionString( Custom.Get(IDS_PROXYNAME) );
    aboutDlg.m_strDriver += GetVersionString( szDriver );
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVidUSB2App message handlers

