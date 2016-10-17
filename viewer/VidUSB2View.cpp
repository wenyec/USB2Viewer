// VidUSB2View.cpp : implementation of the CVidUSB2View class
//
// Author: Julia Zhu
//
// Company: Videology Imaging Solutions
//

#include "stdafx.h"
#pragma warning( disable: 4995 )
#include <atlstr.h>
#include <atlpath.h>
#include <atlfile.h>
#include <atltime.h>
#include <dshowutil.h>
#include <qedit.h>
#include <vector>
#include <algorithm>

#include "mygdiplus.h"
using namespace Gdiplus;
#pragma comment( lib, "gdiplus.lib" )

#include "VidUSB2.h"
#include "VidUSB2Doc.h"
#include "VidUSB2View.h"
#include "AltSettingDlg.h"
#include "MainFrm.h"
#include "XMessageBox.h"

#include <math.h>
#include <Windows.h>
#include <shlobj.h>

#include <ks.h>

#include "CustomIDs.h"
#include "Customize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const short gBLCSize2Index[9][9] =
	{ // H =   1   2       4               8
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  1, -1,  2, -1, -1, -1,  3 }, // V = 1
		{ -1,  4,  5, -1,  6, -1, -1, -1,  7 }, // V = 2
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  8,  9, -1, 10, -1, -1, -1, 11 }, // V = 4
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1, 12, 13, -1, 14, -1, -1, -1, 15 }  // V = 8
	};

static unsigned char NeedsPortrait[] = { 0, 1, 0, 1, 0, 0 };

struct Formats {
    const TCHAR * Name;
    const TCHAR * Extension;
    const GUID * FormatID;
} ImageFormats[] = {
    { _T("BMP"), _T(".bmp"), &ImageFormatBMP },
    { _T("GIF"), _T(".gif"), &ImageFormatGIF },
    { _T("JPEG"), _T(".jpg"), &ImageFormatJPEG },
    { _T("PNG"), _T(".png"), &ImageFormatPNG }
};

//static CSelectdev &SelDev = CSelectdev::getInstance();
// BrowseCallbackProc( )
//
// Description:  Callback function for SHBrowseForFolder.
//
// Arguments:
//
// Returns:
//


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    CString* strFolderStill = (CString*)lpData;
    switch(uMsg){
        case BFFM_INITIALIZED:
            SendMessage(
                hwnd,
                BFFM_SETSELECTION,
                TRUE,
                (LPARAM)strFolderStill->GetBuffer()
            );
            strFolderStill->ReleaseBuffer();
            break;
        case BFFM_SELCHANGED:
            {
                TCHAR szDir[MAX_PATH];
                if (SHGetPathFromIDList((LPITEMIDLIST) lParam ,szDir))
                {
                    SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);
                }
            }
            break;
    }
    return 0;
}

// GetFolder( )
//
// Description: get selected folder from the browse dialog
//
// Arguments:
//
// Returns:
//

BOOL GetFolder( CString* strSelectedFolder,
				   LPCTSTR lpszTitle,
				   const HWND hwndOwner,
				   const char* strRootFolder,
				   const char* strStartFolder)
{
    TCHAR pszDisplayName[MAX_PATH];
    LPITEMIDLIST lpID;
    BROWSEINFO bi;

    bi.hwndOwner = hwndOwner;
    bi.pidlRoot = NULL;
    if( strRootFolder )
    {
        LPITEMIDLIST  pIdl = NULL;
        CComPtr<IShellFolder> pDesktopFolder;

        if( SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)) )
        {
            ULONG chEaten;
            ULONG dwAttributes;
            CStringW szwPath = strRootFolder;

            // The path name is actually an IN parameter, so it is safe to
            // cast away the const here.

            pDesktopFolder->ParseDisplayName(
                NULL, NULL,
                const_cast<LPWSTR>((LPCWSTR)szwPath),
                &chEaten,
                &pIdl,
                &dwAttributes
            );
        }
        bi.pidlRoot = pIdl;
    }
    bi.pszDisplayName = pszDisplayName;
    bi.lpszTitle = lpszTitle;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    bi.lpfn = BrowseCallbackProc;
    bi.lParam = (ULONG_PTR)(void*)strSelectedFolder;
    bi.iImage = NULL;
    lpID = SHBrowseForFolder(&bi);
    if( lpID )
    {
        if( SHGetPathFromIDList(lpID, pszDisplayName) )
        {
            *strSelectedFolder = pszDisplayName;
            return TRUE;
        }
    }
    return FALSE;
}




/////////////////////////////////////////////////////////////////////////////
// CVidUSB2View

IMPLEMENT_DYNCREATE(CVidUSB2View, CFormView)

BEGIN_MESSAGE_MAP(CVidUSB2View, CFormView)
    //{{AFX_MSG_MAP(CVidUSB2View)
    ON_COMMAND(ID_FILE_SETSNAPIMAGEFOLDER, OnFileSetsnapimagefolder)
    ON_COMMAND(ID_CAPTURE_SNAP, OnCaptureSnap)
    ON_COMMAND_RANGE(ID_FILE_SNAP_BMP, ID_FILE_SNAP_PNG, OnChangeSnapFormat)
    ON_COMMAND(ID_OPTIONS_VIDEOCAPTUREFILTER, OnOptionsVideocapturefilter)
    ON_COMMAND(ID_OPTIONS_VIDEOCAPTUREPIN, OnOptionsVideocapturepin)
    ON_COMMAND(ID_OPTIONS_ADVANCED, OnOptionsAdvanced)
    ON_COMMAND(ID_OPTIONS_RESTART, OnOptionsRestart)
    ON_COMMAND(ID_OPTIONS_FACTORY, OnOptionsFactoryReset)
    ON_COMMAND(ID_CAMERACONTROL_CAMERACONTROL, OnCameracontrolCameracontrol)
	ON_COMMAND(ID_CAMEARA_SLECTING, OnSelectCam) // a selection of the camera -- wcheng
    ON_COMMAND_RANGE(ID_OPTIONS_NORMAL, ID_OPTIONS_MIRROR, OnChangeRotation)
    ON_UPDATE_COMMAND_UI_RANGE(ID_FILE_SNAP_BMP, ID_FILE_SNAP_PNG, OnUpdateSnapFormat)
    ON_UPDATE_COMMAND_UI(ID_CAMERACONTROL_CAMERACONTROL, OnUpdateCameracontrolCameracontrol)
    ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIDEOCAPTUREFILTER, OnUpdateOptionsFilter)
    ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIDEOCAPTUREPIN, OnUpdateOptionsPin)
    ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_NORMAL, ID_OPTIONS_MIRROR, OnUpdateRotation)
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_WM_SIZE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_COMMAND(IDC_BTN_EXIT, OnExitApplication)
    ON_COMMAND(IDC_BTN_SWITCH, OnSwitchMonitors)
    ON_MESSAGE(WM_FGNOTIFY, OnActiveMovieError)
    ON_MESSAGE(MSGFEATURE_I2CFAIL, OnMsgI2CFail)
    ON_MESSAGE(MSGFEATURE_BLCOSDON, OnMsgBLCOSDOn)
    ON_MESSAGE(MSGFEATURE_BLCOSDOFF, OnMsgBLCOSDOff)
    ON_MESSAGE(MSGFEATURE_ESCKEY, OnMsgEscape)

    ON_COMMAND(ID_PIXCORR_AUTO, OnAutoPixelCorrection)
    ON_COMMAND(ID_PIXCORR_CLEAR, OnClearPixelCorrection)
    ON_COMMAND(ID_PIXCORR_REMOVE, OnRemoveResults)
    ON_MESSAGE(WM_PIXELCORRECT_COMPLETE, OnProcessPixelCorrection)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CVidUSB2View( )
//
// Description:  construction
//
// Arguments:
//
// Returns:
//


CVidUSB2View::CVidUSB2View()
    : CFormView(CVidUSB2View::IDD)
    , m_pVidUSB2( NULL )
    , m_Image( 720, 480 )
    , m_Window( 640, 480 )
    , m_CurTimePerFrame( 10000000 / 30 )
    , m_Rotation( rotate0 )
    , m_strFolderStill( "C:" )
    , m_pixcorrState( pcIdle )
{
    //{{AFX_DATA_INIT(CVidUSB2View)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    TRACE( __FUNCTION__ "\n" );

    m_boIsMovingBLCBlocks = FALSE;
    m_boDrawBLCSize = FALSE;

    m_boIsShowDlg = FALSE;
	m_boIsUSB3 = FALSE;    // initialize the flag to false in the object constructor. -- wcheng

    m_intStepH = m_Window.cx/8;
    m_intStepV = m_Window.cy/8;

    m_boDeviceConnected = TRUE;
}

// ~CVidUSB2View( )
//
// Description: destruction
//
// Arguments:
//
// Returns:
//


CVidUSB2View::~CVidUSB2View()
{
    TRACE( __FUNCTION__ "\n" );
    if( ::IsWindow(m_hWnd) )
    {
        KillTimer( ID_TIMER4 );
        KillTimer( ID_TIMER7 );
    }

    if( m_pVidUSB2 )
    {
        m_pVidUSB2->vidDestroyPort();
        m_pVidUSB2 = NULL;
    }
}


////////////////////////////////////////////////////////////////////////
//
// Initialization.
//
////////////////////////////////////////////////////////////////////////


void CVidUSB2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVidUSB2View)
	//}}AFX_DATA_MAP
}


// OnInitialUpdate( )
//
// Description: Called by MFC just before our main window is displayed.
//
// Arguments:
//
// Returns:
//


void CVidUSB2View::OnInitialUpdate()
{
    TRACE( __FUNCTION__ "\n" );

    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout(); 
		//GetParentFreame() searches up the parent chain until a CFrameWnd (or derived class) object is found.
		//RecalcLayout() is the mumber function of a CFrameWnd class. Resize the frame window.
    ResizeParentToFit(); //the member function of the CScrollView class. it lets the size of your view dictate the size of its frame window.

    m_hCursor = GetCursor();

    InitializeData();

    if(FAILED(InitializeGraph(FALSE, FALSE)))
    {
        m_boDeviceConnected = FALSE;
        PostQuitMessage( 0 );
        return;
    }

    // Set timer for monitoring camera status.

    SetTimer(ID_TIMER7, 1000, NULL);

    ((CMainFrame*) AfxGetMainWnd())->UpdateWindowSize(m_Window);
    UpdateData(FALSE);
}



// InitializeData( )
//
// Description: initial default still capture folder
// 				initial flags, directshow objects
//
// Arguments:
//
// Returns:
//

void CVidUSB2View::InitializeData()
{
    TRACE( __FUNCTION__ "\n" );
    LPITEMIDLIST  pidl;
    CComPtr<IMalloc> pShellMalloc;
    TCHAR szDir[MAX_PATH + 16];

    // Launch GDI+, used for saving JPEGs and GIFs.

    GdiplusStartupInput startupInput;
    ULONG_PTR token;
    GdiplusStartup( &token, &startupInput, NULL ); //it initializes Windows GDI+

    m_strFolderStill = AfxGetApp()->GetProfileString( _T("Folders"), _T("Stills"), _T("C:") );
    if( m_strFolderStill == "C:" )
    {
        if(
            SUCCEEDED(SHGetMalloc(&pShellMalloc)) &&
            SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_MYPICTURES, &pidl))
        )
        {
            if(SHGetPathFromIDList(pidl, szDir))
            {
                m_strFolderStill = szDir;
            }
            pShellMalloc->Free(pidl);
        }
        AfxGetApp()->WriteProfileString( _T("Folders"), _T("Stills"), m_strFolderStill );
    }

    m_strFileStill = "";
    m_strFileVideo = "";
    m_strFolderVideo = "C:";

    m_nCapTimesStill = 0;

    m_pGraphBuilder = NULL;
    m_pSrcFilter = NULL;
    m_pCaptureGraph = NULL;
    m_pVSC = NULL;

    m_loNotDropped = 0;

    UpdateData(FALSE);

}


// InitializeGraph( )
//
// Description: Create the DirectShow filter graph, connect the camera,
//     and start the graph running.
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::InitializeGraph(BOOL boShowCaptureProperties, BOOL reselectDev)
{
    TRACE( __FUNCTION__ "\n" );
    HRESULT hr;

    //Create an instance of the filter graph manager.
	if (!reselectDev){

		m_pGraphBuilder.CoCreateInstance(CLSID_FilterGraph);
		if (!m_pGraphBuilder)
		{
			Error(TEXT("Error initializing DirectShow."));
			return E_FAIL;
		}

		// Create the video capture graph.

		m_pCaptureGraph.CoCreateInstance(CLSID_CaptureGraphBuilder2);
		if (!m_pCaptureGraph)
		{
			Error(_T("Error initializing DirectShow."));
			return E_FAIL;
		}

		// Attach the capture graph to the graph builder.

		if (!SUCCEEDED(hr = m_pCaptureGraph->SetFiltergraph(m_pGraphBuilder)))
		{
			Error(_T("Error initializing DirectShow."));
			return hr;
		}
	}
    // Find and create the capture device filter

    for( int i = 0; ; i++ )  // in case of the failure of running the grapph first, so it's trying for different camera. -- wcheng's note
    {
		if (!reselectDev){
			GetDefaultCapDevice(&m_pSrcFilter, i);
			if( !m_pSrcFilter )
			{
				Error(_T("Please check that your camera is plugged in, it was not detected"));
				CloseWindow();
				return E_FAIL;
			}
		}
#if 0 // remove the videology specific support using the CVidUSB2Prop class. -wcheng
        m_pVidUSB2 = new CVidUSB2Prop( m_pSrcFilter );

        if( !m_pVidUSB2->vidInitPort(L"") ) // initialize the Videology USB2 camera. -- wcheng's note 
        {
            m_pVidUSB2->vidDestroyPort();
            m_pVidUSB2 = NULL;
        }
        else if( !m_pVidUSB2->vidIsAvailable() )
        {
            m_pVidUSB2->vidDestroyPort();
            m_pVidUSB2 = NULL;
            continue;
        }
#else
		m_pVidUSB2 = NULL; // setting no m_pVideUSB2 instance
#endif
        // Attach the device to the graph builder.
        JIF(m_pGraphBuilder->AddFilter( m_pSrcFilter, L"Cap" )); //the m_pSrcFilter binds the select IMoniker (pM). --wcheng

        // Find video config interface of video capture filter.

        JIF(m_pCaptureGraph->FindInterface(
                &PIN_CATEGORY_CAPTURE,
                &MEDIATYPE_Video,
                m_pSrcFilter,
                IID_IAMStreamConfig,
                (void **)&m_pVSC)
        );

        // Customize the configuration.

        if(boShowCaptureProperties)
        {
            showPropertyPage(m_pVSC, L"Setup the capture");
        }

        // Build the rest of the graph and start it.

        hr = StartGraph();

        // If we succeeded, break out of the loop.

        if( SUCCEEDED(hr) )
            break;

        // Otherwise, tear it all down and try again with the next camera.

        NukeDownstream(m_pSrcFilter);
        m_pSrcFilter.Release();
    }
    return hr;
}

// SetErrorEvent( )
//
// Description: set up directshow error event
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::SetErrorEvent()
{
    TRACE( __FUNCTION__ "\n" );
    HRESULT hr = S_OK;
    CComQIPtr< IMediaEventEx > pMediaEvent = m_pGraphBuilder;
    if( pMediaEvent )
    {
        hr = pMediaEvent->SetNotifyWindow((LONG)GetSafeHwnd(), WM_FGNOTIFY, 0);
    }
    return hr;
}


int GetBuildNumber( LPCTSTR szComponent )
{
    int iVersion = 0;
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
                iVersion = pFileInfo->dwFileVersionLS;
            }
        }

        delete [] lpData;
    }

    return iVersion;
}


CString AddMessageVersions( LPCTSTR msg )
{
    TCHAR szExe[MAX_PATH];
    GetModuleFileName( NULL, szExe, MAX_PATH );

    CString szDriver;
    GetSystemDirectory( szDriver.GetBufferSetLength(MAX_PATH), MAX_PATH );
    szDriver.ReleaseBuffer();
    szDriver += _T("\\Drivers\\") + Custom.Get(IDS_DRIVERNAME);

    BOOL Is64Bit = FALSE;
    IsWow64Process(GetCurrentProcess(), &Is64Bit);

    CString sz = msg;
    sz.AppendFormat(
        _T("\r\n\r\nViewer %d\r\nProxy %d\r\nDriver %d\r\nOS %d"),
        GetBuildNumber( szExe ),
        GetBuildNumber( Custom.Get(IDS_PROXYNAME) ),
        GetBuildNumber( szDriver ),
        Is64Bit ? 64 : 32
    );
    return sz;
}


int CVidUSB2View::MessageBox( 
        LPCTSTR msg, 
        LPCTSTR cap,
        UINT nStyle
)
{
    XMSGBOXPARAMS xmb;
    CRect rct;
    GetWindowRect( &rct );
    if( !IsWindowVisible() )
    {
        if( gCmdInfo.m_Count )
        {
            // Place it where the window would have gone.

            xmb.x = gCmdInfo.m_One.x;
            xmb.y = gCmdInfo.m_One.y;
        }
        else
        {
            // Place it in the center.
            CRect screen;
            SystemParametersInfo( SPI_GETWORKAREA, 0, &screen, 0 );
            xmb.x = (screen.left + screen.right) / 3;
            xmb.y = (screen.top + screen.bottom) / 3;
        }
    }
    else
    {
        xmb.x = (rct.right + rct.left) / 2;
        xmb.y = (rct.top + rct.bottom) / 3;
    }

    // Add versions.

    CString szMsg = AddMessageVersions( msg );

    return XMessageBox( GetSafeHwnd(), szMsg, cap, nStyle, &xmb );
}

////////////////////////////////////////////////////////////////////////
//
// DirectShow capture graph manipulation.
//
////////////////////////////////////////////////////////////////////////



// OnActiveMovieError( )
//
// Description: Handle notifications from the capture graph.
//
// Arguments:
//
// Returns:
//

LRESULT CVidUSB2View::OnActiveMovieError(WPARAM wParam, LPARAM lParam)
{
    TRACE( __FUNCTION__ "(%d,%d)\n", wParam, lParam );
    CComQIPtr< IMediaEventEx > pMediaEvent = m_pGraphBuilder;
    if( pMediaEvent )
    {
        LONG event, l1, l2;
        while(SUCCEEDED(pMediaEvent->GetEvent(&event, &l1, &l2, 0)))
        {
            pMediaEvent->FreeEventParams(event, l1, l2);
            if( (event == EC_ERRORABORT) || (event == EC_DEVICE_LOST) )
            {
                KillTimer( ID_TIMER4 );
                KillTimer( ID_TIMER7 );

                if( m_pVidUSB2 )
                {
                    m_pVidUSB2->vidDestroyPort();
                    m_pVidUSB2 = NULL;
                }

                m_pDlgCameraControl.reset();

                MessageBox(_T("Lost connection to camera. The application is about to quit."), _T("Viewer"));
                PostMessage( WM_DESTROY, 0, 0 );
                break;
            }
        }
    }

    return FALSE;
}

// GetDefaultCapDevice( )
//
// Description: Enumerate all of the installed video capture devices.
//     Find ours, and instantiate it.
//
// Arguments:
//
// Returns:   error code
//

#define ATTR_24Z        0x0001
#define ATTR_CYPRESS    0x0002
#define ATTR_24C        0x0004
#define ATTR_SCHICK     0x0008
#define ATTR_CYPRFX3    0x0010
#define ATTR_MISUMI     0x0020
#define ATTR_UNKNOW     0x0040
// USB VID/PID of the cameras we will drive.

struct CameraAttributes {
    ULONG VidPid;
    FLONG Attributes;
	CStringW CamName;
};

wchar_t CamName[10][120];

const CameraAttributes CameraPids[] = {
    { 0x1bbd0014, ATTR_CYPRESS, "" },
	{ 0x1bbd0015, ATTR_CYPRESS, "" },
	{ 0x1bbd0042, ATTR_CYPRESS, "" },
	{ 0x1bbd0043, ATTR_CYPRESS, "" },
	{ 0x1bbd0044, ATTR_CYPRESS, "" },
	{ 0x1bbd0052, ATTR_CYPRESS, "" },
	{ 0x1bbd0053, ATTR_CYPRESS, "" },
	{ 0x1bbd0054, ATTR_CYPRESS, "" },
	{ 0x1bbd0055, ATTR_CYPRESS, "" },
	{ 0x1bbd0060, ATTR_CYPRESS, "" },
    { 0x1bbd0061, ATTR_CYPRESS },
	{ 0x1bbd0064, ATTR_CYPRESS | ATTR_24C, "" },
	{ 0x1bbd0065, ATTR_CYPRESS | ATTR_24C, "" },
	{ 0x1bbd0066, ATTR_CYPRESS | ATTR_24C, "" },
	{ 0x1bbd0067, ATTR_CYPRESS | ATTR_24C, "" },
	{ 0x1bbd0142, ATTR_CYPRESS, "" },
	{ 0x1bbd0143, ATTR_CYPRESS, "" },
	{ 0x1bbd0452, ATTR_CYPRESS, "" },
	{ 0x1bbd0453, ATTR_CYPRESS, "" },
	{ 0x1bbd1442, ATTR_CYPRESS, "" },
	{ 0x1bbd1443, ATTR_CYPRESS, "" },
	{ 0x1bbd1452, ATTR_CYPRESS, "" },
	{ 0x1bbd1453, ATTR_CYPRESS, "" },
	{ 0x1bbd1454, ATTR_CYPRESS, "" },
	{ 0x1bbd1455, ATTR_CYPRESS, "" },
	{ 0x1bbd5332, ATTR_CYPRESS, "" },
	{ 0x1bbd6261, ATTR_CYPRESS, "" },
	{ 0x0fbc8117, ATTR_CYPRESS | ATTR_SCHICK, "" },
	{ 0x1bbd3061, ATTR_CYPRFX3, "" },     // for USB3 Camera -- wcheng
	{ 0x1bbd2410, ATTR_MISUMI, "" },      // for Misumi Camera -- wcheng
	{ 0, ATTR_UNKNOW, "" },      // for Other Cameras -- wcheng
	{ 0, 0, "" }
};

CameraAttributes AvailableCameraAttr[10]; // for recording connected camera --wcheng

HRESULT CVidUSB2View::GetDefaultCapDevice( IBaseFilter ** ppCap, int index )
{
    TRACE( __FUNCTION__ "\n" );
    HRESULT hr;
    if (!ppCap)
        return E_POINTER;
    *ppCap = NULL;

    // Create an enumerator.

    CComPtr< ICreateDevEnum > pCreateDevEnum;
    pCreateDevEnum.CoCreateInstance( CLSID_SystemDeviceEnum );

    ASSERT(pCreateDevEnum);
    if( !pCreateDevEnum )
        return E_FAIL;

    // Enumerate the list of video capture devices.

    CComPtr< IEnumMoniker > pEm;
    pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEm, 0 );

    if( !pEm )
        return E_FAIL;

    pEm->Reset( );


    // Enumerate through the list and grab the first video capture device.
	UINT uIndex = 0;
    while( 1 )// the loop runs until no device needs to be checked. -- wcheng's note
    {
		ULONG ulFetched = 0;
        CComPtr< IMoniker > pM;
        hr = pEm->Next( 1, &pM, &ulFetched );
        if( FAILED(hr) || !pM )
            break;

        // Get the property bag interface from the moniker.

        CComPtr< IPropertyBag > pBag;
        hr = pM->BindToStorage( 0, 0, IID_IPropertyBag, (void**) &pBag );
        if( FAILED(hr) )
            continue;

        // Go read the device path from the property bag.

        CComVariant var;
        hr = pBag->Read( L"DevicePath", &var, NULL );
        if( FAILED(hr) )
            continue;

        // If this is one of our devices, go bind to it to get the
        // base filter interface.

        CStringW szName = var.bstrVal;
        szName = szName.MakeLower();
        if( szName.Find(L"usb#") < 0 )
            continue;

        // We have a USB camera.  Extract the VID and PID.
        //
        // \\?\usb#vid_xxxx&pid_xxxx
        // 0123456789012345678901
        //
        // Technically, the format of the device path is undocumented.
        // However, this format has remained stable since Win95 OSR2
        // and is unlikely to change in our lifetime.

        int i = szName.Find(L"vid_");
        ULONG vid = wcstol( szName.Mid(i+4,4), NULL, 16 );
        i = szName.Find(L"pid_");
        ULONG pid = wcstol( szName.Mid(i+4,4), NULL, 16 );

        ULONG VidPid = (vid << 16) | pid;

        FLONG Attributes = 0;
        for( 
            const CameraAttributes* camAttr = CameraPids;
            camAttr->VidPid;  //if camAttr->VidPid == 0, the loop is stopped. -- wcheng's note
            camAttr++
        )
        {
            if( VidPid == camAttr->VidPid ) // check the camera type based on VidPid -- wcheng's note
            {
                // This is one of ours.
                Attributes = camAttr->Attributes;
                break;  // let record all available cameras -- wcheng
            }
        }

        // Have we reached the chosen index?
#if 1 // move following code out of the while loop.
        if( Attributes && !index-- )  //index ??? -wcheng
        {
			if (!(*ppCap)) //check if a camera binded -- wcheng's note
				pM->BindToObject( 0, 0, IID_IBaseFilter, (void**) ppCap );
			CurCam.AvailabeCameraIMo = pM;
			CurCam.AvailableCameraName = var.bstrVal;
			break;
        }
#endif
		/* to get the camera records */
		AvailableCameraAttr[uIndex].VidPid = VidPid;
		AvailableCameraAttr[uIndex].Attributes = Attributes;
		hr = pBag->Read(L"FriendlyName", &var, NULL);
		if (FAILED(hr))
			continue;

		// If this is one of our devices, go bind to it to get the
		// base filter interface.

		AvailableCameraAttr[uIndex].CamName = var.bstrVal;
		uIndex++;
        pM.Release();
        pBag.Release();
    }
    pEm.Release();
    pCreateDevEnum.Release();

    return *ppCap ? S_OK : E_FAIL;
}


// SetupSampleGrabber( )
//
// Description: Add snapshot renderer to the graph and hook it up.
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::SetupSampleGrabber()
{
    TRACE( __FUNCTION__ "\n" );
    HRESULT hr = S_OK;

    // Create a bitmap renderer.
    //
    // This actually demonstrates a little-known but useful technique.  It is
    // quite possible to use filters in a DirectShow graph that are local to
    // the process.  They don't all have to be fully registered COM objects.

    m_pSnapshotter = new CBitmapRenderer( _T("Bitmap renderer"), NULL, &hr );
    if( FAILED(hr) )
    {
        Error(_T("Couldn't create bitmap renderer."));
        return hr;
    }

    m_pSnapshotter->SetCallback( (IBitmapCallback*) this );

    // Add the renderer to the graph.

    CComQIPtr< IBaseFilter > pGrabBase( m_pSnapshotter );
    hr = m_pGraphBuilder->AddFilter( pGrabBase, L"Snapshot" );

    return hr;
}



//  Snapshot-related stuff.

bool GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num, size;
    GetImageEncodersSize(&num, &size);
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*) new char[size];
    GetImageEncoders(num, size, pImageCodecInfo);
    bool found = false;
    for (UINT ix = 0; !found && ix < num; ++ix) {
        if( _wcsicmp(pImageCodecInfo[ix].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[ix].Clsid;
            found = true;
        }
    }
    delete pImageCodecInfo;
    return found;
}


bool GetEncoderClsid(const CLSID* format, CLSID* pClsid)
{
    UINT num, size;
    GetImageEncodersSize(&num, &size);
    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*) new char[size];
    GetImageEncoders(num, size, pImageCodecInfo);
    bool found = false;
    for (UINT ix = 0; !found && ix < num; ++ix) {
        if( pImageCodecInfo[ix].FormatID == *format ) {
            *pClsid = pImageCodecInfo[ix].Clsid;
            found = true;
        }
    }
    delete pImageCodecInfo;
    return found;
}

// Sample()
//
// Description: Called by the bitmap renderer at the end of the snapshot
//    pin when a snapshot image arrives.
//

HRESULT
CVidUSB2View::Sample( IMediaSample* sample )
{
    OutputDebugStringA( __FUNCTION__ "\n" );

    // Figure out where to capture to.

    CString szSnapFormat = m_strFileStill;
    if( szSnapFormat.IsEmpty() )
    {
        CTime now = CTime::GetCurrentTime();
        szSnapFormat = m_strFolderStill;
        szSnapFormat += now.Format( _T("\\Still_%Y%m%d_%H%M%S_") );
        szSnapFormat.AppendFormat( _T("%04d"), m_nCapTimesStill );
        szSnapFormat += ImageFormats[m_SnapFormat].Extension;
    }

    // Increment bitmap number if requested.  Otherwise,
    // we'll reuse the filename next time.

    m_nCapTimesStill++;

    BYTE * pBuffer;
    sample->GetPointer(&pBuffer);
    long lBufferSize = sample->GetActualDataLength();

    Bitmap* bitmap = new Bitmap(
        m_Image.cx, 
        m_Image.cy, 
        -m_Image.cx*3, 
        PixelFormat24bppRGB, 
        pBuffer + (m_Image.cy - 1) * m_Image.cx * 3
    );

    EncoderParameters encoderParameters;
    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;
    long quality = 90;
    encoderParameters.Parameter[0].Value = &quality;

    CLSID encoder;
    GetEncoderClsid(ImageFormats[m_SnapFormat].FormatID, &encoder);

    Status stat = bitmap->Save( szSnapFormat, &encoder, &encoderParameters );

    if(stat != Ok)
    {
        CString sz;
        if( stat == Win32Error )
            sz.Format( _T("Save failed, Win32 error %d"), GetLastError() );
        else
            sz.Format( _T("Save failed, GDI+ error %d"), stat );
        MessageBox( sz, _T(__FUNCTION__) );
    }


#if 0
    // Write out a BMP file.

    CAtlFile hf;
    hf.Create( szSnapFormat, GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS );
    if( !hf )
        return 0;

    // Write out the file header.

    BITMAPFILEHEADER bfh;
    memset( &bfh, 0, sizeof( bfh ) );
    bfh.bfType = 'MB';
    bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
    bfh.bfSize = bfh.bfOffBits + lBufferSize;

    hf.Write( &bfh, sizeof( bfh ) );

    // Write out the bitmap info header.
    // TODO
    // We should fetch the format from the pin at the end of the snapshot 
    // path to get the size.

    BITMAPINFOHEADER bih;
    ZeroMemory( &bih, sizeof( bih ) );
    bih.biSize = sizeof( bih );
    bih.biWidth = m_Image.cx;
    bih.biHeight = m_Image.cy;
    bih.biPlanes = 1;
    bih.biBitCount = 24;

    hf.Write( &bih, sizeof( bih ) );

    // Write out the bits themselves.

    hf.Write( pBuffer, lBufferSize );
#endif

    return S_OK;
}


// SetupRender( )
//
// Description: Render the output pins from the capture filter.
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::SetupRender()
{
    HRESULT hr;
    CString sz;
    CComPtr<IBaseFilter> pEndOfChain = m_pSrcFilter;

    CComPtr<IBaseFilter> pRotateFilter;
    pRotateFilter.CoCreateInstance(CLSID_RotateFilter);
    if( pRotateFilter )
    {
        m_pGraphBuilder->AddFilter( pRotateFilter, L"Rotate Filter" );
        m_MainRotate = pRotateFilter;
        m_MainRotate->SetRotation(m_Rotation);

        ConnectFilters( m_pGraphBuilder, pEndOfChain, pRotateFilter );

        pEndOfChain = pRotateFilter;
    }

    CComPtr<IBaseFilter> pSampleGrabber;
    pSampleGrabber.CoCreateInstance(CLSID_SampleGrabber);
    m_pGraphBuilder->AddFilter( pSampleGrabber, L"Sample Grabber" );

    CComQIPtr<ISampleGrabber> pGrabber( pSampleGrabber );
    pGrabber->SetBufferSamples( FALSE );
    pGrabber->SetOneShot( FALSE );
    pGrabber->SetCallback( this, 1 );

    ConnectFilters( m_pGraphBuilder, pEndOfChain, pSampleGrabber );

    pEndOfChain = pSampleGrabber;

    // Render the preview stream.

    hr = m_pCaptureGraph->RenderStream(
        NULL,
        &MEDIATYPE_Video,
        pEndOfChain,
        NULL,
        NULL
    );

    if( FAILED( hr ) )
    {
        Error( _T("Can't build the graph") );
    }

    pEndOfChain.Release();
    pRotateFilter.Release();
    pSampleGrabber.Release();

    // Go fetch the snapshot pin.
    CComPtr<IPin> pOutPin;
    m_pSrcFilter->FindPin( L"1", &pOutPin );

#if 0 // remove the snapshot feature for test -- wcheng
    // Set the snapshot pin to the same format as the capture pin.

    ASSERT( m_pMediaType );
    CComQIPtr<IAMStreamConfig> pStill( pOutPin );
    pStill->SetFormat( m_pMediaType );
    hr = m_pSnapshotter->SetMediaType( (CMediaType*)m_pMediaType );
    if( FAILED(hr) )
    {
        sz.Format( _T("Could not set format on snap pin, err = %08x"), hr );
        OutputDebugString( sz );
        hr = S_OK;
    }
#endif
    // Rotate this one, too.

    pRotateFilter.CoCreateInstance(CLSID_RotateFilter);
    if( pRotateFilter )
    {
        m_pGraphBuilder->AddFilter( pRotateFilter,  L"Rotate Filter" );
        m_SnapRotate = pRotateFilter;
        m_SnapRotate->SetRotation(m_Rotation);
        ConnectFilters( m_pGraphBuilder, pOutPin, pRotateFilter );
        ConnectFilters( m_pGraphBuilder, pRotateFilter, m_pSnapshotter );
        pRotateFilter.Release();
    }
    else
    {
        ConnectFilters( m_pGraphBuilder, pOutPin, m_pSnapshotter );
    }

    if( FAILED( hr ) )
    {
        sz.Format( _T("Could not connect snapshot pin, err = %08x"), hr );
        OutputDebugString( sz );
        // This is not a tragedy.
        hr = S_OK;
    }

    return hr;
}


// SetVideoWindow( )
//
// Description: set up the preview window
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::SetVideoWindow()
{
    TRACE( __FUNCTION__ "\n" );

    // Get the current video size.

    ASSERT(m_pMediaType->formattype == FORMAT_VideoInfo);

    if( NeedsPortrait[m_Rotation] )
    {
        m_Image.cy = HEADER(m_pMediaType->pbFormat)->biWidth;
        m_Image.cx = abs(HEADER(m_pMediaType->pbFormat)->biHeight);
    }
    else
    {
        m_Image.cx = HEADER(m_pMediaType->pbFormat)->biWidth;
        m_Image.cy = abs(HEADER(m_pMediaType->pbFormat)->biHeight);
    }

    m_Window = m_Image;

    if( IsTweety(m_CamID) && IsNTSC(m_CamID) )
    {
        // 720 becomes 640
        // 640 becomes 568
        if( NeedsPortrait[m_Rotation] )
            m_Window.cy = m_Image.cy * 8 / 9;
        else
            m_Window.cx = m_Image.cx * 8 / 9;
    }
    m_intStepH = m_Window.cx/8;
    m_intStepV = m_Window.cy/8;

    CComQIPtr< IVideoWindow > pVideoWindow( m_pGraphBuilder );
    if( !pVideoWindow )
    {
        Error(TEXT("Could not fetch IVideoWindow."));
        return E_FAIL;
    }

    pVideoWindow->put_Owner((OAHWND)GetSafeHwnd());
    pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
    pVideoWindow->put_MessageDrain((OAHWND)GetSafeHwnd());

    // Resize our window to the new capture size.

    ((CMainFrame*) AfxGetMainWnd())->UpdateWindowSize(m_Window);
    pVideoWindow->SetWindowPosition( 0, 0, m_Window.cx, m_Window.cy);
    pVideoWindow->put_Visible(OATRUE);

    return S_OK;
}

// errorHandler( )
//
// Description: error message output
//
// Arguments:
//
// Returns:
//

void CVidUSB2View::errorHandler(LPCTSTR szFormat, ...)
{
    CString szBuffer;
    va_list pArgs;
    va_start(pArgs, szFormat);
    szBuffer.FormatV( szFormat, pArgs );
    va_end(pArgs);
    // Display the error message
    MessageBox(szBuffer, _T("Alert"), MB_OK | MB_ICONERROR);
}

// Error( )
//
// Description: error message output
//
// Arguments:
//
// Returns:
//

void CVidUSB2View::Error( LPCTSTR pText )
{
    TRACE( __FUNCTION__ "\n" );
    MessageBox( pText, TEXT("Error!"), MB_OK | MB_TASKMODAL | MB_SETFOREGROUND );
}
/////////////////////////////////////////////////////////////////////////////
// CVidUSB2View diagnostics

#ifdef _DEBUG
void CVidUSB2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CVidUSB2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVidUSB2Doc* CVidUSB2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVidUSB2Doc)));  // get a CDocument class that provides the basic functionality for user-defined document classes -- wcheng's note
	return (CVidUSB2Doc*)m_pDocument;
}
#endif //_DEBUG


// OnOptionsVideocapturefilter( )
//
// Description: Open video capture filter property page.
//
// Arguments:
//
// Returns:   error code
//

void CVidUSB2View::OnOptionsVideocapturefilter()
{
    TRACE( __FUNCTION__ "\n" );

    // Setup the camera by property page.

    if (m_pSrcFilter) {
        // Display the property page of source filter.
        showPropertyPage(m_pSrcFilter, L"Video Capture Filter");
    }
}

// showPropertyPage( )
//
// Description: Display the property page of a COM object
//
// Arguments:
// 			pIU:    A interface of the COM object
// 				name:   the name of the dialog box of the property page
//
// Returns:   error code
//

HRESULT CVidUSB2View::showPropertyPage(IUnknown* pIU, const WCHAR* name)
{
    TRACE( __FUNCTION__ "\n" );
    if( !pIU )
        return E_POINTER;

    CComQIPtr<ISpecifyPropertyPages> pispp = pIU;

    CAUUID caGUID;
    if( SUCCEEDED(pispp->GetPages(&caGUID)) )
    {
        OleCreatePropertyFrame(
            m_hWnd, 0, 0,
            name,     // Caption for the dialog box
            1,        // Number of filters
            &pIU,
            caGUID.cElems,
            caGUID.pElems,
            0, 0, NULL
        );
        // Release the memory
        CoTaskMemFree(caGUID.pElems);
    }

    return S_OK;
}


// StopGraph( )
//
// Description: stop preview
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::StopGraph()
{
    CComQIPtr<IMediaControl> pControl ( m_pGraphBuilder );
    if( !pControl )
        return E_POINTER;
    return pControl->Stop();
}


// TearDownGraph( )
//
// Description: tear down directhow graph
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::TearDownGraph()
{
    CComQIPtr< IVideoWindow > pVideoWindow( m_pGraphBuilder );
    if( pVideoWindow )
    {
        pVideoWindow->put_Visible(OAFALSE);
        pVideoWindow->put_Owner(NULL);
        pVideoWindow->put_MessageDrain(0);
        pVideoWindow.Release();
    }

    m_MainRotate.Release();
    m_SnapRotate.Release();

    if(m_pSrcFilter)
        NukeDownstream(m_pSrcFilter);

    if( m_pVidUSB2 )
    {
        m_pVidUSB2->vidDestroyPort();
        m_pVidUSB2 = NULL;
    }

    if(m_dwGraphRegister)
    {
        RemoveGraphFromRot(m_dwGraphRegister);
        m_dwGraphRegister = 0;
    }

    DeleteMediaType( m_pMediaType );
    m_pMediaType = NULL;
}

// OneTimeStartup
//
// Description: Tasks that need to be done the very first time the graph
//      is constructed.

HRESULT CVidUSB2View::OneTimeStartup()
{
    HRESULT hr = NOERROR;

    // For cameras with adjustable sizes, go read the last size from
    // the registry.  I don't like this feature, but the client does.

    if( (m_CamID == CAMID_24B13X) || (m_CamID == CAMID_24C13X) )
    {
        CString szSet;
        szSet.Format( _T("Settings%02d"), m_CamID );
        long Width = AfxGetApp()->GetProfileInt( szSet, _T("Width"), 0 );
        long Height = AfxGetApp()->GetProfileInt( szSet, _T("Height"), 0 );
        long Rate = AfxGetApp()->GetProfileInt( szSet, _T("FrameTime"), 0 );

        if( Width && Height )
        {
            VIDEOINFOHEADER* pHeader = (VIDEOINFOHEADER*) m_pMediaType->pbFormat;
            pHeader->bmiHeader.biWidth = Width;
            pHeader->bmiHeader.biHeight = Height;

            if( pHeader->rcSource.right )
            {
                pHeader->rcSource.right = Width;
                pHeader->rcSource.bottom = Height;
            }
            if( pHeader->rcTarget.right )
            {
                pHeader->rcTarget.right = Width;
                pHeader->rcTarget.bottom = Height;
            }

            if( Rate )
                pHeader->AvgTimePerFrame = Rate;

            CComPtr<IPin> pOutPin;
            m_pSrcFilter->FindPin( L"0", &pOutPin );

            CComQIPtr<IAMStreamConfig> pConfig ( pOutPin );
            hr = pConfig ->SetFormat( m_pMediaType );
            if( !SUCCEEDED(hr) )
            {
                szSet.Format( L"SetFormat err %08x\n", hr );
                MessageBox( szSet );
            }
        }
    }

    // For Diebold, remove the menu altogether.

    if( gCmdInfo.m_Count )
    {
        GetParent()->GetMenu()->DestroyMenu();
        GetParent()->SetMenu(NULL);

        CRect rct1( 10, 10, 30, 30 );

        m_exitBtn.Create(_T("Exit"), WS_CHILD, rct1, this, IDC_BTN_EXIT );
        m_exitBtn.ShowWindow( SW_NORMAL );

        if( gCmdInfo.m_SwitchButton )
        {
            // Display the switch button, lower left.

            m_switchBtn.Create( _T("Switch"), WS_CHILD, rct1, this, IDC_BTN_SWITCH );
            m_switchBtn.ShowWindow( SW_NORMAL );
        }
    }

    // For all but the color 24C cameras, remove the "Factory Reset" option.

    else if( m_CamID != CAMID_24C13X )
    {
        Menu()->
            GetSubMenu(1)->
                RemoveMenu( ID_OPTIONS_FACTORY, MF_BYCOMMAND );
        DrawMenuBar();
    }

    // If rotate filter is not available, remove that menu.

    int MenuCount = 5;

    CComQIPtr<IVideoRotation> pRotate;
    pRotate.CoCreateInstance( CLSID_RotateFilter );
    if( !pRotate )
    {
        Menu()->GetSubMenu( MenuCount-2 )->DestroyMenu();
        Menu()->RemoveMenu( MenuCount-2, MF_BYPOSITION );
        --MenuCount;
    }

    // Based on some criteria, remove the pixel correction menu.

#ifdef  PIXELCORRECTION
    if( !IsTweety(m_CamID) )
    {
#endif
        Menu()->GetSubMenu( MenuCount-1 )->DestroyMenu();
        Menu()->RemoveMenu( MenuCount-1, MF_BYPOSITION );
#ifdef  PIXELCORRECTION
    }
#endif

    return hr;
}


void CVidUSB2View::OnExitApplication()
{
    PostMessage( WM_DESTROY, 0, 0 );
}


void CVidUSB2View::OnSwitchMonitors()
{
    // We shouldn't get here unless there are 4 parameters.

    CRect rct;
    GetParent()->GetWindowRect( &rct );

    gCmdInfo.Switch();

    CPoint delta = CPoint(
        rct.left - gCmdInfo.m_One.x,
        rct.top - gCmdInfo.m_One.y
    );

    rct -= delta;
    GetParent()->MoveWindow( &rct );
}


// StartGraph( )
//
// Description: Complete the rest of the DirectShow graph.
//
// Arguments:
//
// Returns:   error code
//

HRESULT CVidUSB2View::StartGraph()
{
    TRACE( __FUNCTION__ "\n" );
    HRESULT hr;

    // At this point, our filter has supposedly been added to the graph.
    // Create the library wrapper, if we don't already have one.

    // Connect to the camera control library.

    if( !m_pVidUSB2 ) // the m_pVidUSB2 has been set in InitializeGraph() also -- wcheng's note
    {
        m_pVidUSB2 = new CVidUSB2Prop( m_pSrcFilter );

        if(m_pVidUSB2)
        {
            if(!m_pVidUSB2->vidInitPort())
            {
                m_pVidUSB2->vidDestroyPort();
                m_pVidUSB2 = NULL;
            }
        }
    }

    if( m_pVidUSB2 )
    {
		if( !m_pVidUSB2->vidIsAvailable() )
			return E_FAIL;
		else{
			// Turn on the power so we can fetch the camera ID.
			m_pVidUSB2->vidSetPower(TRUE);
			m_pVidUSB2->vidGetCamID(&m_CamID);
		}
	}
	else { // non Videology USB2 Camera -- wcheng
        //errorHandler(_T("Camera communication error. You may not be able to control the camera"));
		//errorHandler(_T("It is not the Videology USB3 Camera."));
		m_CamID = CAMID_UNKNOWN; // It's a USB3 camera ID -- wcheng
		m_boIsUSB3 = TRUE;  // setting the active camera is USB3 -- wcheng
        //return E_FAIL;
	}

    // Fetch the current video format.

    m_pVSC->GetFormat( &m_pMediaType );

    // We're about to start the graph anyway.

    //static bool bFirst = true;
    if( bFirst )
    {
        OneTimeStartup();
        bFirst = false;
    }

    // Set sample grabber format and add it the graph.

    JIF(SetupSampleGrabber());

    // If there is a VP pin present on the video device, then put the 
    // renderer on CLSID_NullRenderer. Ask for the connection media type so 
    // we know how big it is, so we can write out bitmaps.

    JIF(SetupRender());

    // Set video window style and position.

    JIF(SetVideoWindow());

    // Set error event handler.

    SetErrorEvent();

    // Add the graph to the ROT so we can monitor it from graphedt.
    // We don't care if this fails.

    AddGraphToRot(m_pGraphBuilder, &m_dwGraphRegister);

    // Set it to "run" state.

    return CComQIPtr<IMediaControl>(m_pGraphBuilder)->Run();
}


// NukeDownstream
//
// Description: Tear down everything downstream of a given filter.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::NukeDownstream(IBaseFilter *pf)
{
    TRACE( __FUNCTION__ "\n" );
    IPin *pP=0, *pTo=0;
    ULONG u;
    CComPtr<IEnumPins> pins;
    PIN_INFO pininfo;

    if (!pf)
        return;

    HRESULT hr = pf->EnumPins(&pins);
    pins->Reset();

    while(hr == NOERROR)
    {
        hr = pins->Next(1, &pP, &u);
        if(SUCCEEDED(hr) && pP && u>0)
        {
            pP->ConnectedTo(&pTo);
            if(pTo)
            {
                hr = pTo->QueryPinInfo(&pininfo);
                if(hr == NOERROR)
                {
                    if(pininfo.dir == PINDIR_INPUT)
                    {
                        NukeDownstream(pininfo.pFilter);
                        m_pGraphBuilder->RemoveFilter(pininfo.pFilter);
                    }
                    pininfo.pFilter->Release();
                }
                pTo->Release();
            }
            pP->Release();
        }
    }

    m_pSnapshotter = NULL;
}


// ClearGraphs()
//
// Description: Clear up the DirectShow graph.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::ClearGraphs( )
{
    TRACE( __FUNCTION__ "\n" );

    // Stop the graph.

    StopGraph();
    TearDownGraph();

    m_pVSC.Release();
    m_pSrcFilter.Release();
    m_pCaptureGraph.Release();
    m_pGraphBuilder.Release();
}



LRESULT CVidUSB2View::OnMsgI2CFail(WPARAM wParam, LPARAM lParam)
{
    MessageBox(_T("Port not ready. Please reconnect the camera."), _T("Alert!"), MB_OK);

    m_boIsShowDlg = FALSE;
    KillTimer(ID_TIMER4);
    m_pDlgCameraControl.reset();
    return 1;
}

LRESULT CVidUSB2View::OnMsgBLCOSDOn(WPARAM wParam, LPARAM lParam)
{
    SetTimer(ID_TIMER4, 1, NULL);
    return 1;
}


LRESULT CVidUSB2View::OnMsgBLCOSDOff(WPARAM wParam, LPARAM lParam)
{
    KillTimer(ID_TIMER4);
    Invalidate();
    return 1;
}

LRESULT CVidUSB2View::OnMsgEscape(WPARAM wParam, LPARAM lParam)
{
    m_boIsShowDlg = FALSE;
    return 1;
}


////////////////////////////////////////////////////////////////////////
//
// Menu item handlers.
//
////////////////////////////////////////////////////////////////////////


// OnFileSetsnapimagefolder()
//
// Description: Handle the File->Set Snap Folder menu item by bringing
//     up common dialog for selecting the capture folder.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnFileSetsnapimagefolder()
{
    GetFolder(
        &m_strFolderStill,
        _T("Still Image Capture Folder."),
        GetSafeHwnd(),
        NULL,
        NULL
    );
    AfxGetApp()->WriteProfileString( _T("Folders"), _T("Stills"), m_strFolderStill );
}

// OnCaptureSnap()
//
// Description: Handle the File->Snap menu item by triggering a snapshot.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnCaptureSnap()
{
	TRACE( __FUNCTION__ "\n" );
	static BOOL flag = FALSE;
	unsigned short rData = 0;
#if 1
	m_pVidUSB2->vidReadI2C(0, 0x0D, &rData);
	if (flag){
		m_pVidUSB2->vidWriteI2C(0, 0x0D, 0x8020);
		flag = FALSE;
	}
	else{
		m_pVidUSB2->vidWriteI2C(0, 0x0D, 0x8020);
		flag = TRUE;
	}
	rData = 0;
	m_pVidUSB2->vidReadI2C(0, 0x0D, &rData);
#endif
	Sleep(2500); // sleep 1 second.
	m_pVidUSB2->vidTakeSnapshot();

}


// HaltGraph
//
// Shut things down sufficiently so that we can do something that might
// change the graph configuration.
//
void CVidUSB2View::HaltGraph()
{
    KillTimer(ID_TIMER7);

    HRESULT hr = StopGraph();
    if(FAILED(hr))
    {
        m_boDeviceConnected = FALSE;
        return;
    }

    TearDownGraph();

    if( m_pVidUSB2 )
    {
        m_pVidUSB2->vidDestroyPort();
        m_pVidUSB2 = NULL;
    }
}


// RebuildGraph
//
// Bring things back up to where they were before HaltGraph.
void CVidUSB2View::RestartGraph()
{
    // Fetch the current video format.

    m_pVSC->GetFormat( &m_pMediaType );
    VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)(m_pMediaType->pbFormat);
    if( (m_CamID == CAMID_24B13X) || (m_CamID == CAMID_24C13X))
    {
        CString szSet;
        szSet.Format( _T("Settings%02d"), m_CamID );
        AfxGetApp()->WriteProfileInt( szSet, _T("Width"), vih->bmiHeader.biWidth );
        AfxGetApp()->WriteProfileInt( szSet, _T("Height"), vih->bmiHeader.biHeight );
        AfxGetApp()->WriteProfileInt( szSet, _T("FrameTime"), (int)vih->AvgTimePerFrame );
    }

    HRESULT hr = StartGraph();
    if(FAILED(hr))
    {
        m_boDeviceConnected = FALSE;
        return;
    }

    m_boDeviceConnected = TRUE;

    SetViewerPos();
    if(m_pDlgCameraControl.get() && m_boIsShowDlg)
    {
        SetControDlgPos();
    }

    // Connect to the camera control library.

    m_pVidUSB2 = new CVidUSB2Prop(m_pSrcFilter);
    if( m_pVidUSB2 )
    {
        if(!m_pVidUSB2->vidInitPort())
        {
            m_pVidUSB2->vidDestroyPort();
            m_pVidUSB2 = NULL;
        }
    }

    if( !m_pVidUSB2 )
    {
        errorHandler(_T("Camera communication error. You may not be able to control the camera"));
    }

    if( m_pVidUSB2 )
    {
        // Set time for lost connection detection.

        SetTimer(ID_TIMER7, 1000, NULL);
    }

    ((CMainFrame*) AfxGetMainWnd())->UpdateWindowSize(m_Window);
    UpdateData(FALSE);
}


// OnOptionsVideocapturepin()
//
// Description: Handle the Options->Video Capture Pin menu item by
//     opening the video capture pin property page.  Because the pin
//     property page contains image size, we tear down the graph
//     before bringing up the page, and rebuild it after.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnOptionsVideocapturepin()
{
    TRACE( __FUNCTION__ "\n" );
    if(!m_boDeviceConnected)
        return;

    HRESULT hr = S_OK;

    HaltGraph();

    CComPtr<IPin> pOutPin;
    m_pSrcFilter->FindPin( L"0", &pOutPin );
    if( pOutPin )
    {
        hr = showPropertyPage(pOutPin, L"Video Capture Pin");
    }
    else
    {
        hr = showPropertyPage(m_pVSC, L"Video Capture Pin");
    }

    if(FAILED(hr))
    {
        m_boDeviceConnected = FALSE;
        return;
    }

    RestartGraph();
}



// OnOptionsRestart()
//
// Description: Handle the Options->Restart Graph menu item by
//     tearing down the graph and rebuilding it, possible with a new
//     video size.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnOptionsRestart()
{
    TRACE( __FUNCTION__ "\n" );
    if(!m_boDeviceConnected)
        return;

    HaltGraph();
    RestartGraph();
}

// OnSelectCam()
//
// Description: Handle the File->select a Camera Graph menu item by
//     tearing down the graph and rebuilding it based on the selected camera, 
//     possible with a new video size.
//
// Arguments:
//
// Returns:   void
//
void CVidUSB2View::OnSelectCam(){
	TRACE(__FUNCTION__ "\n");
	HRESULT hr = S_OK;
#if 0
	m_boIsShowDlg = !m_boIsShowDlg;  //trigger the flag record of the dialog openning/closing. -- wcheng

	if (m_boIsShowDlg)
	{
		m_pDlgSelectdev.reset();
	}

	if (!m_pDlgSelectdev.get())
	{
		bool boPortReady;
		m_pDlgSelectdev.reset(new CSelectdev(this));
		m_pDlgSelectdev->Create(IDD_DIALOG_SELECTDEV);  //selec device class ID
	}

	if (1||!m_boIsShowDlg)
	{
		m_pDlgSelectdev->ShowWindow(SW_NORMAL);
	}
	else
	{
		SetViewerPos();
		SetControDlgPos();
	}
#else
	//CSelectdev c_getDevice; // add the get device class --wcheng
	//c_getDevice.pSelDev = &SelDevice;
	//c_getDevice.visCamID = visID;
	hr = m_pDlgSelectdev.DoModal();
#endif
	if (1||CurCam.AvailabeCameraIMo != SelDevice.AvailabeCameraIMo){
		CurCam.AvailabeCameraIMo = SelDevice.AvailabeCameraIMo;
		CurCam.AvailableCameraName = SelDevice.AvailableCameraName;
	}
	bFirst = TRUE;// set firs start flag -wcheng
	TearDownGraph();
	StopGraph();

	m_pVSC.Release();
	CComPtr< IMoniker > pM;
	pM = m_pDlgSelectdev.SelDevIn.AvailabeCameraIMo;//AvailableCam[(UINT32)m_DevNameList.GetItemData(sel)].AvailabeCameraIMo; //(IMoniker*)CurCam.AvailabeCameraIMo;
	m_pSrcFilter = NULL;
	if (!(m_pSrcFilter)) //check if a camera binded -- wcheng's note
		pM->BindToObject(0, 0, IID_IBaseFilter, (void**)&m_pSrcFilter);
	if (!m_pSrcFilter)
	{
		Error(_T("Please check that your camera is plugged in, it was not detected"));
		pM.Release();
		CloseWindow();
		return;
	}
	pM.Release();
#if 0

	//CurCam.AvailabeCameraIMo = pM;
	//CurCam.AvailableCameraName = var.bstrVal;
	// Attach the device to the graph builder.
	m_pGraphBuilder->AddFilter(m_pSrcFilter, L"Cap"); //the m_pSrcFilter binds the select IMoniker (pM). --wcheng

	// Find video config interface of video capture filter.

	m_pCaptureGraph->FindInterface(
		&PIN_CATEGORY_CAPTURE,
		&MEDIATYPE_Video,
		m_pSrcFilter,
		IID_IAMStreamConfig,
		(void **)&m_pVSC);

	// Customize the configuration.
	StartGraph();
#endif
	InitializeGraph(FALSE, TRUE);
	//HaltGraph();
	//RestartGraph();
}

// OnOptionsAdvanced()
//
// Description: Handle the Options->Advanced menu item by opening a
//     dialog to allow them to change the USB alternate setting.  This
//     requires a stop and start to take effect.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnOptionsAdvanced()
{
    TRACE( __FUNCTION__ "\n" );
    if(!m_boDeviceConnected)
        return;

    // Stop the graph.

    KillTimer(ID_TIMER7);
    StopGraph();
    TearDownGraph();

    // Show dialog.

    SetAlternateSetting();

    // Restart the graph.

    StartGraph();
    SetTimer(ID_TIMER7, 1000, NULL);

    UpdateData(FALSE);
}


void CVidUSB2View::SetAlternateSetting()
{
    CAltSettingDlg settingDlg;

    // Fetch old setting.

    CComQIPtr<IVideologyCommon> pKS( m_pSrcFilter ); //it uses the IVideologyCommon that only supports the USB2 cams --wcheng's note
    pKS->GetAltSetting( &settingDlg.m_Setting );

    // Preset dialog.

    if( settingDlg.DoModal() != IDOK )
        return;

    // Set new setting.

    pKS->SetAltSetting( settingDlg.m_Setting );

    if( settingDlg.m_Setting == 0 )
    {
        MessageBox(
            _T("The switch to a bulk pipe will take effect the next time ")
            _T("the camera is plugged in.  Please unplug and replug now.  ")
            _T("The application is about to quit."), 
            _T("Viewer"));
        PostMessage( WM_DESTROY, 0, 0 );
    }
}


void CVidUSB2View::OnChangeSnapFormat(UINT nID)
{
    m_SnapFormat = nID - ID_FILE_SNAP_BMP;
}


void CVidUSB2View::OnUpdateSnapFormat(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_SnapFormat == (pCmdUI->m_nID-ID_FILE_SNAP_BMP));
}



void CVidUSB2View::OnChangeRotation(UINT nID)
{
    TRACE( __FUNCTION__ "\n" );
    if(!m_boDeviceConnected)
        return;

    int iNewOption = nID - ID_OPTIONS_NORMAL;

    // Check to see if we need to rebuild the graph.

    if( NeedsPortrait[iNewOption] != NeedsPortrait[m_Rotation] )
    {
        KillTimer(ID_TIMER7);
        StopGraph();
        TearDownGraph();

        // Make the change permanent.

        m_Rotation = iNewOption;

        // Restart the graph.

        StartGraph();
        SetTimer(ID_TIMER7, 1000, NULL);
    }
    else
    {
        m_MainRotate->SetRotation( iNewOption );
        m_SnapRotate->SetRotation( iNewOption);
        m_Rotation = iNewOption;
    }

    UpdateData(FALSE);
}


void CVidUSB2View::OnUpdateRotation(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_Rotation == (pCmdUI->m_nID-ID_OPTIONS_NORMAL));
}


// OnCameracontrolCameracontrol()
//
// Description: Handle the Camera->Camera Control menu item by
//     toggling the state of the camera control panel dialog.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnCameracontrolCameracontrol()
{
    TRACE( __FUNCTION__ "\n" );

    m_boIsShowDlg = !m_boIsShowDlg;

    if(m_boIsShowDlg)
    {
        m_pVidUSB2->vidDestroyPort();
        m_pVidUSB2 = NULL;

        KillTimer(ID_TIMER7);

        m_pDlgCameraControl.reset();
    }

    if( !m_pVidUSB2 )
    {
        m_pVidUSB2 = new CVidUSB2Prop(m_pSrcFilter);
        if(m_pVidUSB2)
        {
            if(!m_pVidUSB2->vidInitPort())
            {
                m_pVidUSB2->vidDestroyPort();
                m_pVidUSB2 = NULL;
            }
        }
    }

    if( !m_pVidUSB2 )
    {
        KillTimer(ID_TIMER7);
        m_pDlgCameraControl.reset();
        errorHandler(_T("Camera communication error. You may not be able to control the camera. Please reconnect the camera."));
        m_boIsShowDlg = FALSE;
        return;
    }

    if( !m_pDlgCameraControl.get() )
    {
        bool boPortReady;
        m_pDlgCameraControl.reset( 
            new CTweetyFeatureControl(m_pVidUSB2, &boPortReady, this)
        );

        m_pDlgCameraControl->Create(IDD_DIALOG_FEATURECONTROL);
    }

    if( !m_boIsShowDlg )
    {
        m_pDlgCameraControl->ShowWindow(SW_HIDE);
    }
    else
    {
        SetViewerPos();
        SetControDlgPos();
    }
}


// OnOptionsFactoryReset()
//
// Description: Handle the Options->Factory Graph menu item by
//     sending a factory reset command, only for the 24C13.
//
// Arguments:
//
// Returns:   void
//

void CVidUSB2View::OnOptionsFactoryReset()
{
    TRACE( __FUNCTION__ "\n" );
    if( !m_pVidUSB2 )
        return;
    if( m_CamID != CAMID_24C13X )
        return;
    m_pVidUSB2->vidFactoryReset();

    MessageBox(
            _T("Factory reset will take effect the next time the ")
            _T("camera is plugged in.  Please unplug and replug now.  ")
            _T("The application is about to quit."), 
            _T("Viewer"));
    PostMessage( WM_DESTROY, 0, 0 );
}

// OnDestroy()
//
// Description: Handle the destruction of our main window.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnDestroy()
{
    TRACE( __FUNCTION__ "\n" );
    CFormView::OnDestroy();

    ClearGraphs( );
    KillTimer(ID_TIMER4);
    KillTimer(ID_TIMER7);
    PostQuitMessage( 0 );
}


// OnTimer()
//
// Description:  Timer message handler.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == ID_TIMER4)
    {
        if( m_pixcorrState == pcDisplaying )
        {
            DrawResults();
            return;
        }

        CClientDC dc(this);
        CPen pen(PS_SOLID, 2, RGB(100, 100, 100));
        CPen* pOldPen = dc.SelectObject(&pen);

        for(int intI = 1; intI < 8; intI++)
        {
            dc.MoveTo(m_intStepH*intI, 0);
            dc.LineTo(m_intStepH*intI, m_Window.cy);
            dc.MoveTo(0, m_intStepV*intI);
            dc.LineTo(m_Window.cx, m_intStepV*intI);
        }
        if(m_pDlgCameraControl.get())
        {
            DrawBLCSquare();
        }
    }
    else if(nIDEvent == ID_TIMER7)
    {
        LONG GoodFrames = 0;
        UpdateFrameRateStatus(&GoodFrames);
    }
    CFormView::OnTimer(nIDEvent);
}

// UpdateFrameRateStatus()
//
// Description:  caculate frame rate
//
// Arguments:
//
// Returns:  void
//

HRESULT CVidUSB2View::UpdateFrameRateStatus(LONG* plNot)
{
    HRESULT hr=S_OK;
    CString sz;

    if(!m_pCaptureGraph)
        return S_FALSE;

    CComQIPtr< IAMDroppedFrames > pDropFilter( m_pSrcFilter );

    // This filter can't tell us dropped frame info.

    if(!pDropFilter)
    {
        sz += L" -- Err 1";
        AfxGetMainWnd()->SetWindowText( sz );
        return S_FALSE;
    }

    LONG lTempNot = m_loNotDropped;
    JIF(pDropFilter->GetNumNotDropped(&m_loNotDropped));

    // We return good frames in the last second.

    *plNot = m_loNotDropped - lTempNot;

    sz = Custom.Get(m_Window.cx < 400 ? IDS_VIEWERSHORTTITLE : IDS_VIEWERTITLE);

    if( *plNot )
        sz.AppendFormat( L" - %d fr/sec", *plNot );
    else if( m_pVidUSB2->vidIsSnapshotMode() )
        sz += L" - Snapshot Mode";
    else
        sz += L" - Lost communication";
    AfxGetMainWnd()->SetWindowText( sz );

    return hr;
}

////////////////////////////////////////////////////////////////////////
//
// UI update handlers.
//
////////////////////////////////////////////////////////////////////////

void CVidUSB2View::OnSize(UINT nType, int cx, int cy)
{
    if( !gCmdInfo.m_Count )
        return;

    if( m_exitBtn.GetSafeHwnd() )
    {
        m_exitBtn.MoveWindow(
            cx-BUTTON_WIDTH, cy-BUTTON_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT
        );
    }
    if( m_switchBtn.GetSafeHwnd() )
    {
        m_switchBtn.MoveWindow(
            0, cy-BUTTON_HEIGHT,
            BUTTON_WIDTH, BUTTON_HEIGHT
        );
    }
}


// SetViewerPos()
//
// Adjust the location of the viewer window.  We center the window,
// unless the camera control dialog is open, and then we try to line
// them up side by side.
//

void CVidUSB2View::SetViewerPos()
{
    TRACE( __FUNCTION__ "\n" );
    CRect RectDlg;
    CRect RectW;
    (AfxGetApp()->m_pMainWnd)->GetWindowRect(&RectW);
    if( m_pDlgCameraControl.get() && m_boIsShowDlg)
        m_pDlgCameraControl->GetWindowRect( &RectDlg);

    int intScreenX = GetSystemMetrics(SM_CXSCREEN);
    int intScreenY = GetSystemMetrics(SM_CYSCREEN);

    int intStartViewerX =
        (m_boIsShowDlg && m_pDlgCameraControl.get() )
        ? (intScreenX - RectW.Width() - RectDlg.Width())/2
        : (intScreenX - RectW.Width())/2;
    if(intStartViewerX < 0)
        intStartViewerX = 0;
    int intStartViewerY = (intScreenY - RectW.Height())/2;
    if(intStartViewerY < 0 )
        intStartViewerY = 0;

    (AfxGetApp()->m_pMainWnd)->MoveWindow(
        intStartViewerX, intStartViewerY,
        RectW.Width(), RectW.Height(),
        TRUE
    );
}


// SetControDlgPos()
//
// Description: Try to place the camera control dialog side-by-side with
//     the maing window.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::SetControDlgPos()
{
    TRACE( __FUNCTION__ "\n" );
    CRect Rect, RectW;
    (AfxGetApp()->m_pMainWnd)->GetWindowRect(&RectW);
    m_pDlgCameraControl->SetActiveWindow();
    m_pDlgCameraControl->ShowWindow(SW_SHOW);
    m_pDlgCameraControl->GetWindowRect( &Rect);

    int intScreenX = GetSystemMetrics(SM_CXSCREEN);
    int intScreenY = GetSystemMetrics(SM_CYSCREEN);

    // Place the dialog to the right of the app if there is room.
    // Otherwise, butt up against the right edge of the screen.

    int intLeft = min( RectW.right, intScreenX - Rect.Width() );

    // Center the dialog in the app unless it's bigger than the screen.
    // Otherwise butt up against the top edge of the screen.
    int intTop = (Rect.Height() > intScreenY)
        ? 0
        : RectW.top + RectW.Height()/2 - Rect.Height()/2;

    int intHeight = min( intScreenY, Rect.Height() );

    m_pDlgCameraControl->MoveWindow(
        intLeft, intTop,
        Rect.Width(), intHeight, TRUE
    );
}


// OnUpdateCameracontrolCameracontrol()
//
// Description: Update the camera control menu item visibility.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnUpdateCameracontrolCameracontrol(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_boIsShowDlg);
    pCmdUI->Enable( IsTweety(m_CamID) ); // changing for the test cameracontrol function -- wcheng
    UpdateStandbyControls();
}



// OnUpdateOptionsFilter()
//
// Description:  Enable/disable the "Filter Properties" menu item.
//
// Returns:  void

void CVidUSB2View::OnUpdateOptionsFilter(CCmdUI* pCmdUI)
{
    DWORD Allowed = 0;
    CRegKey key;
    if( 
        key.Open( HKEY_CURRENT_USER, _T("Software\\VideologyViewer\\Cameras"), KEY_READ )
        == ERROR_SUCCESS
    )
    {
        key.QueryDWORDValue( _T("EnableI2C"), Allowed );
        key.Close();
    }
    pCmdUI->Enable( !IsTweety(m_CamID) || Allowed );
}


// OnUpdateOptionsPin()
//
// Description:  Enable/disable the "Pin Properties" menu item.
//
// Returns:  void

void CVidUSB2View::OnUpdateOptionsPin(CCmdUI* pCmdUI)
{
    pCmdUI->Enable( !IsTweety(m_CamID) && (m_CamID != CAMID_22C205) );
}


// UpdateStandbyControls()
//
// Description: Update the controls based on the standby status.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::UpdateStandbyControls()
{
}


////////////////////////////////////////////////////////////////////////
//
// Backlight compensation rectangle computations.
//
////////////////////////////////////////////////////////////////////////


// GetBLCBlockSize()
//
// Description:  Get BLC block size in pixels.
//
// Arguments:
//
// Returns:  void
//

CSize CVidUSB2View::GetBLCBlockSize()
{
    if(!m_pDlgCameraControl.get())
        return CSize();

    ULONG ulSize = m_pDlgCameraControl->m_ulData[D14_BLCWINSIZE];
    return CSize(
        m_intStepH << (ulSize >> 2),
        m_intStepV << (ulSize & 3)
    );
}


// GetBLCBlockPos()
//
// Description:  Get BLC block position in pixels.
//
// Arguments:
//
// Returns:  void
//

CPoint CVidUSB2View::GetBLCBlockPos()
{
    if(!m_pDlgCameraControl.get())
        return CPoint();

    ULONG ulPos = m_pDlgCameraControl->m_ulData[D14_BLCWINPOS];
    return CPoint(
        m_intStepH * (ulPos >> 3),
        m_intStepV * (ulPos & 7)
    );
}


// GetBLCBlockPos()
//
// Description:  Draw the BLC region on the screen.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::DrawBLCSquare()
{
    CClientDC dc(this);
    CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SelectStockObject( HOLLOW_BRUSH );

    if(m_boDrawBLCSize)
    {
        CRect rct( m_ptStartDrag, m_ptEndDrag );
        dc.Rectangle( rct );
    }
    else
    {
        CSize size = GetBLCBlockSize();
        CPoint pos = GetBLCBlockPos();

        if( m_boIsMovingBLCBlocks )
        {
            pos += m_ptEndDrag - m_ptStartDrag;
            SnapToBlcGrid(&pos);
        }

        CRect rct( pos, size );
        dc.Rectangle( rct );
    }

    dc.SelectObject(pOldPen);
}


// SnapToBlcGrid()
//
// Description:  Locate the BLC coordinate nearest to the given point.
//
// Arguments:  Point to snap to grid.
//
// Returns:  void
//

void CVidUSB2View::SnapToBlcGrid(POINT* pos)
{
    CSize blocks = GetBLCBlockSize();

    // Round H and V to the nearest multiple of the step size.

    int intH = max( 0, pos->x );
    int intV = max( 0, pos->y );

    intH = (intH + m_intStepH / 2) / m_intStepH * m_intStepH;
    intV = (intV + m_intStepV / 2) / m_intStepV * m_intStepV;

    pos->x = min( intH, m_Window.cx - blocks.cx );
    pos->y = min( intV, m_Window.cy - blocks.cy );
}


// SnapToBlcSize()
//
// Description:  Find the width and height of the BLC rectangle starting
//		at m_ptStartDrag and ending at "point".  Return that size.
//		Also sets m_ptEndDrag to the bottom right grid point of that
//      rectangle.
//
// Arguments:   Mouse position of bottom right of BLC rectangle.
//
// Returns:  Size of nearest full BLC rectangle in blocks.

CSize CVidUSB2View::SnapToBlcSize(const CPoint& point)
{
	m_ptEndDrag.x = (point.x / m_intStepH) * m_intStepH;
	m_ptEndDrag.y = (point.y / m_intStepV) * m_intStepV;

	int intH = abs(m_ptEndDrag.x - m_ptStartDrag.x)/m_intStepH;
	if(intH <= 1)		intH = 1;
	else if(intH <= 3)	intH = 2;
	else if(intH <= 6)	intH = 4;
	else				intH = 8;

	int intV = abs(m_ptEndDrag.y - m_ptStartDrag.y)/m_intStepV;
	if(intV <= 1)		intV = 1;
	else if(intV <= 3)	intV = 2;
	else if(intV <= 6)	intV = 4;
	else				intV = 8;

	if( intH == 8 && intV == 8 )
	{
		intH = intV = 4;
	}

	m_ptEndDrag.x = (point.x > m_ptStartDrag.x)
		? m_ptStartDrag.x + intH * m_intStepH
		: m_ptStartDrag.x - intH * m_intStepH;
	m_ptEndDrag.y = (point.y > m_ptStartDrag.y)
		? m_ptStartDrag.y + intV * m_intStepV
		: m_ptStartDrag.y - intV * m_intStepV;

	return CSize( intH, intV );
}


////////////////////////////////////////////////////////////////////////
//
// Mouse motion and click handlers, mostly handling the BLC grid.
//
////////////////////////////////////////////////////////////////////////


// OnMouseMove()
//
// Description:  Handle mouse motion.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_pDlgCameraControl.get())
    {
        CPoint pos = GetBLCBlockPos();
        CSize blocks = GetBLCBlockSize();

        if(nFlags == MK_LBUTTON)
        {
            if(m_boIsMovingBLCBlocks)
            {
                m_ptEndDrag = point;
                SetCursor(AfxGetApp()->LoadCursor(IDC_HAND1));
            }
            else
                SetCursor(m_hCursor);
        }
        else if(nFlags == MK_RBUTTON)
        {
            if(m_boDrawBLCSize)
            {
                SnapToBlcSize(point);
                SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
            }
        }
        else
        {
            int intX = point.x % m_intStepH;
            int intY = point.y % m_intStepV;
            CRect bounds( pos, blocks );
            if(
                (intX <= THRESHOLD_GRID_SNAP || m_intStepH - intX <= THRESHOLD_GRID_SNAP) &&
                (intY <= THRESHOLD_GRID_SNAP || m_intStepV - intY <= THRESHOLD_GRID_SNAP)
            )
            {
                SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
            }
            else if( bounds.PtInRect( point ) )
            {
                SetCursor(AfxGetApp()->LoadCursor(IDC_HAND1));
            }
            if(m_boIsMovingBLCBlocks)
            {
                pos += m_ptEndDrag - m_ptStartDrag;
                SnapToBlcGrid(&pos);

                m_pDlgCameraControl->m_ulData[D14_BLCWINPOS] = (pos.x/m_intStepH)*8 + pos.y/m_intStepV;
                m_pDlgCameraControl->UpdateBLCPosControls();
                m_boIsMovingBLCBlocks = FALSE;
            }
            if(m_boDrawBLCSize)
            {
                RButtonUp(m_ptEndDrag);
            }
        }
    }

    CFormView::OnMouseMove(nFlags, point);
}

// OnLButtonDown()
//
// Description:  Handle left mouse button going down.  We start our
//     drag here.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnLButtonDown(UINT nFlags, CPoint point)
{
    if(!m_pDlgCameraControl.get() || !m_pDlgCameraControl->m_boBLCOSD)
        return;

    CRect bounds( GetBLCBlockPos(), GetBLCBlockSize() );

    if( !m_boIsMovingBLCBlocks && bounds.PtInRect( point ) )
    {
        m_boIsMovingBLCBlocks = TRUE;
        SetCursor(AfxGetApp()->LoadCursor(IDC_HAND1));
        m_ptStartDrag = point;
        m_ptEndDrag = point;
    }

    CFormView::OnLButtonDown(nFlags, point);
}

// OnLButtonUp()
//
// Description:  Handle release of left button.  We stop dragging the BLC rect.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnLButtonUp(UINT nFlags, CPoint point)
{
    if( !m_pDlgCameraControl.get() || !m_pDlgCameraControl->m_boBLCOSD)
        return;

    if(m_boIsMovingBLCBlocks)
    {
        CPoint pos = GetBLCBlockPos();
        pos += point - m_ptStartDrag;
        SnapToBlcGrid(&pos);

        m_pDlgCameraControl->m_ulData[D14_BLCWINPOS] = (pos.x/m_intStepH)*8 + pos.y/m_intStepV;
        m_pDlgCameraControl->UpdateBLCPosControls();
        m_boIsMovingBLCBlocks = FALSE;
    }
    SetCursor(m_hCursor);
    Invalidate();

    CFormView::OnLButtonUp(nFlags, point);
}

// OnRButtonDown()
//
// Description:  Handle press of right button.  We start allowing the user
//     to drag a BLC rectangle.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnRButtonDown(UINT nFlags, CPoint point)
{
    if( !m_pDlgCameraControl.get() || !m_pDlgCameraControl->m_boBLCOSD )
        return;

    // Are we within THRESHOLD_GRID_SNAP pixels of a grid point?

    int intX = point.x % m_intStepH;
    int intY = point.y % m_intStepV;
    if(
        (intX <= THRESHOLD_GRID_SNAP || (m_intStepH - intX <= THRESHOLD_GRID_SNAP)) &&
        (intY <= THRESHOLD_GRID_SNAP || (m_intStepV - intY <= THRESHOLD_GRID_SNAP))
    )
    {
        // Yes, start dragging.  Remember the starting point in m_ptStartDrag
        // and change the cursor to a cross.

        m_boDrawBLCSize = TRUE;
        m_ptStartDrag.x = (point.x + m_intStepH / 2) / m_intStepH * m_intStepH;
        m_ptStartDrag.y = (point.y + m_intStepV / 2) / m_intStepV * m_intStepV;
        m_ptEndDrag = m_ptStartDrag;
        SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
    }

    CFormView::OnRButtonDown(nFlags, point);
}

// OnRButtonUp()
//
// Description:  Right button up handler.  Stop dragging the BLC rectangle.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::OnRButtonUp(UINT nFlags, CPoint point)
{
    if(m_boDrawBLCSize)
    {
        RButtonUp(point);
    }
    Invalidate();

    CFormView::OnRButtonUp(nFlags, point);
}

// RButtonUp()
//
// Description:  Helper to stop dragging a BLC rect.
//
// Arguments:
//
// Returns:  void
//

void CVidUSB2View::RButtonUp(CPoint point)
{
    CSize size = SnapToBlcSize(point);

    int intX = min( m_ptStartDrag.x, m_ptEndDrag.x );
    int intY = min( m_ptStartDrag.y, m_ptEndDrag.y );

    m_pDlgCameraControl->m_ulData[D14_BLCWINPOS] = (intX/m_intStepH)*8 + intY/m_intStepV;
    m_pDlgCameraControl->UpdateBLCPosControls();
    m_pDlgCameraControl->m_ulData[D14_BLCWINSIZE] = gBLCSize2Index[size.cx][size.cy];
    m_pDlgCameraControl->UpdateBLCSizeControls();

    SetCursor(m_hCursor);
    m_boDrawBLCSize = FALSE;
}


////////////////////////////////////////////////////////////////////////
//
// Hereafter contains the faulty pixel correction code.
//
////////////////////////////////////////////////////////////////////////


// This is the convolution that we do by hand below.

const int g_intFilter[5][5] = 	
{
    { 0, 0,-2, 0, 0},
    { 0, 0, 2, 0, 0},
    {-1, 1, 3,-1, 0},
    { 0, 0,-2, 0, 0},
    { 0, 0, 0, 0, 0}
};

#define THRESHHOLD_ALL_OK       60
#define PIXCORR_NUM_FRAMES      30


void
CVidUSB2View::Fix1Pixel( int x, int y, BYTE loc )
{
    x = 160 + x;
    y = 33 + y / 2;

    BYTE top = (((y >> 8) & 3) << 2) | ((x >> 8) & 3);
    m_pVidUSB2->vidWriteI2C( deviceCamera, loc+0, x&255 );
    m_pVidUSB2->vidWriteI2C( deviceCamera, loc+1, y&255 );
    m_pVidUSB2->vidWriteI2C( deviceCamera, loc+2, top );
}


void
CVidUSB2View::OnClearPixelCorrection( )
{
    OutputDebugString( _T(__FUNCTION__) L"\n" );
    if( m_pixcorrState == pcDisplaying )
    {
        OnRemoveResults();
        m_BadPixels.clear();
    }

    if( m_pixcorrState != pcIdle )
        return;

    for( int i = 0; i < 8; i++ )
    {
        m_pVidUSB2->vidWriteI2C( deviceCamera, 0xA0+i*3, 0x00 );
        m_pVidUSB2->vidWriteI2C( deviceCamera, 0xA1+i*3, 0x00 );
        m_pVidUSB2->vidWriteI2C( deviceCamera, 0xA2+i*3, 0x00 );
    }
}


void
CVidUSB2View::OnAutoPixelCorrection( )
{
    OutputDebugString( _T(__FUNCTION__) L"\n" );

    OnRemoveResults();
    OnClearPixelCorrection();

    m_pixcorrFrameCount = 0;
    m_pixcorrSum.clear();
    m_pixcorrSum.resize( m_Image.cx * m_Image.cy );
    m_pixcorrState = pcGathering;
}


void
CVidUSB2View::OnRemoveResults( )
{
    OutputDebugString( _T(__FUNCTION__) L"\n" );
    KillTimer( ID_TIMER4 );
    m_pixcorrState = pcIdle;
}


LRESULT
CVidUSB2View::OnProcessPixelCorrection( WPARAM wParam, LPARAM lParam)
{
    OutputDebugString( _T(__FUNCTION__) L"\n" );
    m_pixcorrState = pcIdle;

    // Scale down to pixel values.

    int cells = m_Image.cy * m_Image.cx;
    long * pv = &m_pixcorrSum[0];
    for( int i = 0; i < cells; i++ )
        *pv++ /= PIXCORR_NUM_FRAMES;

    // Convolve.

    std::vector<BYTE> convolve( m_pixcorrSum.size() );

    long sum = 0;
    BYTE maxcell = 0;

    for( int y = 2; y < m_Image.cy-2; y++ )
    {
        BYTE * pconv = &convolve[y * m_Image.cx + 2];
        pv = &m_pixcorrSum[y * m_Image.cx + 2];
        for( int x = 2; x < m_Image.cx-2; x++ )
        {
            int cell =
                pv[ -2 * m_Image.cx ] * -2 +
                pv[ -1 * m_Image.cx ] *  2 +
                pv[ -2 ] * -1 + pv[ -1 ] *  1 + pv[  0 ] *  3 + pv[  1 ] * -1 +
                pv[  1 * m_Image.cx ] * -2;
            cell = cell > 255 ? 255 : cell < 0 ? 0 : cell;
            sum += cell;
            *pconv++ = cell;
            *++pv;
            if( cell > maxcell )
                maxcell = cell;
        }
    }

    long average = sum / ((m_Image.cx - 2) * (m_Image.cy - 2));

    CStringA sz;
    sz.Format( "Count=%d max=%d average=%d\n", cells, maxcell, average );
    OutputDebugStringA( sz );

    if( maxcell - average <  THRESHHOLD_ALL_OK )
    {
        MessageBox( L"No hot pixels found.", L"VidUSB2", MB_OK );
        return 1;
    }

    // Find outliers.  A point is included in the list if its raw value is
    // 1/3 closer to the max than it is to the average, and is not within
    // 2 pixels and 1 row of another pixel, unless it is brighter than the
    // other one.

    BYTE threshhold = (BYTE)((maxcell + average * 2) / 3);

    m_BadPixels.clear();

    // We work in units of delta from the center.

    BYTE * pconv = &convolve[0];
    for( int y = 0; y < m_Image.cy; y++ )
        for( int x = 0; x < m_Image.cx; x++ )
        {
            bool found = false;

            if( *pconv > threshhold )
            {
                // This one is above the threshhold.  Is it too close to
                // another known baddie?

                int dist = (x - m_Image.cx / 2) * (x - m_Image.cx / 2) +
                           (y - m_Image.cy / 2) * (y - m_Image.cy / 2);

                for each( BadPixels bp in m_BadPixels )
                {
                    if( abs(bp.x - x) < 3 && abs(bp.y - y) < 2)
                    {
                        found = true;
                        if( bp.value < *pconv )
                        {
                            bp.x = x;
                            bp.y = y;
                            bp.dist = dist;
                            bp.value = *pconv;
                            break;
                        }
                    }
                }

                if( !found )
                    m_BadPixels.push_back( BadPixels( x, y, dist, *pconv ) );
            }
            pconv++;
        }

    // If there are none, boast.

    if( m_BadPixels.empty() )
    {
        MessageBox( L"No hot pixels found.", L"VidUSB2", MB_OK );
        return 1;
    }

    // OK, now sort these in order by distance from the center.
    
    std::sort( m_BadPixels.begin(), m_BadPixels.end() );

    for each( BadPixels bp in m_BadPixels )
    {
        sz.Format( "%d,%d dist %d delta %d\n", bp.x, bp.y, bp.dist, bp.value );
        OutputDebugStringA( sz );
    }

    // If there are too many, then this is probably not legitimate.

    if( m_BadPixels.size() > 250 )
    {
        MessageBox( L"Too many exceptions.  Probably not a black screen.",
            L"VidUSB2",
            MB_OK
        );
        return 1;
    }

    // Program them.

    if( m_BadPixels.size() > 8 )
        m_BadPixels.resize( 8 );

    int iCount = 0xA0;
    for each( BadPixels bp in m_BadPixels )
    {
        Fix1Pixel( bp.x, bp.y, iCount );
        iCount += 3;
        if( iCount >= 0xB8 )
            break;
    }

    while( iCount < 0xB8 )
        m_pVidUSB2->vidWriteI2C( deviceCamera, iCount++, 0 );

    m_pixcorrState = pcDisplaying;
    SetTimer(ID_TIMER4, 1, NULL);
    return 1;
}



HRESULT 
CVidUSB2View::BufferCB( double Timestamp, BYTE* pjBits, long Size )
{
    CString sz;
    if( m_pixcorrState == pcGathering )
    {
        long * pv = &m_pixcorrSum[0];

        for( int y = 0; y < m_Image.cy; y++ )
            for( int x = 0; x < m_Image.cx; x++ )
            {
                *pv++ += pjBits[1];
                pjBits += 2;
            }

        sz.Format( L"Processed frame %d of %d\n", m_pixcorrFrameCount+1, PIXCORR_NUM_FRAMES );
        OutputDebugString(sz);

        if( ++m_pixcorrFrameCount == PIXCORR_NUM_FRAMES )
        {
            m_pixcorrState = pcComputing;
            PostMessage( WM_PIXELCORRECT_COMPLETE );
        }
    }

    if( m_pixcorrState == pcVerifying )
    {
        // Check
    }

    return S_OK;
}



void
CVidUSB2View::DrawResults()
{
    CClientDC dc(this);

    bool scale = IsNTSC(m_CamID);

    CString sz;
    int i = 0;
    for each( BadPixels bp in m_BadPixels )
    {
        sz.Format( L"%d", ++i );
        int x = scale ? bp.x * 8 / 9 : bp.x;
        dc.SetPixel( x, bp.y,   RGB(255,0,0) );
        dc.SetPixel( x, bp.y+1, RGB(255,0,0) );
        dc.TextOut( x, bp.y+2, sz );
    }
}
