
// VidUSB2View.h : interface of the CVidUSB2View class
// 
// Author: Julia Zhu
// Company: Videology Imaging Solutions
// 02/17/2004:	created
// Heavily modified by: 
//     Tim Roberts
//     Providenza & Boekelheide, Inc.
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qedit.h>
#include <memory>
#include "TweetyFeatureControl.h"
#include "VISUSB3FeatureControl.h"
#include "VidUSB2IO.h"
#include "BitmapRender.h"
#include <initguid.h>
#include "../RotateFilter.h"
#include "Selectdev.h"

#define WM_FGNOTIFY	                WM_USER + 3
#define WM_PIXELCORRECT_COMPLETE        WM_USER + 4

#define THRESHOLD_GRID_SNAP		3

// Check for error, return false if failed. (Jump-If-Failed)

#define JIF(x) \
    if (FAILED(hr=(x))) { \
        Error( TEXT("Please check that your Videology camera is plugged in, it was not detected.")); 	\
	CloseWindow(); \
        return hr; \
    }

struct BadPixels {
    int     x;
    int     y;
    int     dist;
    BYTE    value;

    BadPixels( int _x=0, int _y=0, int _dist=0, BYTE _value=0 )
        : x(_x)
        , y(_y)
        , dist(_dist)
        , value(_value)
    {
    }

    bool operator< (BadPixels& other )
    {
        return dist < other.dist;
    }
};


class CVidUSB2View 
    : public CFormView
    , public IBitmapCallback
    , public ISampleGrabberCB
{
protected: // create from serialization only
    CVidUSB2View();
    DECLARE_DYNCREATE(CVidUSB2View)  // DECLARE_DYNCREATE enables objects of CObject-derived classes to be created dynamically at run time. --wcheng's note

public:
    //{{AFX_DATA(CVidUSB2View)
    enum { IDD = IDD_VIDUSB2_FORM };
    //}}AFX_DATA

    // Attributes
public:
    CVidUSB2Doc* GetDocument();  // the method for get a CDocument class --wcheng's note
    CVidUSB2Prop* m_pVidUSB2;

private:
    // Routines and members for managing the UI.

    void    SetViewerPos() ;
    void    SetControDlgPos() ;
    void    UpdateStandbyControls();

    HCURSOR m_hCursor;
    BOOL    m_boIsShowDlg;
    BOOL    m_boIsI2CBusy;
    CString m_strDeviceName;
    BOOL    m_boDeviceConnected;
    ULONG   m_CamID;
	BOOL    m_boIsUSB3;  // the flag for categorying the USB2 and USB3 cameras. -- wcheng

    // Routines and members for managing the backlight compensation.

    void    DrawBLCSquare();
    CSize   GetBLCBlockSize();
    CPoint  GetBLCBlockPos();
    void    SnapToBlcGrid(POINT* pos);
    CSize   SnapToBlcSize(const CPoint& point);
    void    RButtonUp( CPoint );

    BOOL    m_boIsMovingBLCBlocks;
    BOOL    m_boDrawBLCSize;
    CPoint  m_ptStartDrag;
    CPoint  m_ptEndDrag;

    // Routines and members for talking to DirectShow.

    CComPtr< IGraphBuilder >	        m_pGraphBuilder;
    CComPtr< ICaptureGraphBuilder2 >    m_pCaptureGraph;
    CComPtr< IBaseFilter >		m_pSrcFilter;
    CComPtr< IAMStreamConfig >	        m_pVSC;
    AM_MEDIA_TYPE *                     m_pMediaType;

    CSize   m_Image;
    CSize   m_Window;
    int	    m_intStepH;
    int	    m_intStepV;

    int                 m_Rotation;
    CComQIPtr<IVideoRotation>   m_MainRotate;
    CComQIPtr<IVideoRotation>   m_SnapRotate;

    REFERENCE_TIME	m_CurTimePerFrame;
    CString		m_strFolderStill;
    CString		m_strFileStill;
    CString		m_strFolderVideo;
    CString		m_strFileVideo;
    int			m_nCapTimesStill;
    LONG                m_loNotDropped;
    int                 m_SnapFormat;

    CButton m_exitBtn;
    CButton m_switchBtn;

    void    InitializeData();
	HRESULT InitializeGraph(BOOL boShowCaptureProperties, BOOL reselectDev);
    HRESULT GetDefaultCapDevice( IBaseFilter ** ppCap, int index);
    HRESULT SetupSampleGrabber();
    HRESULT SetupRender();
    HRESULT SetVideoWindow();
    void    errorHandler(LPCTSTR szFormat, ...);   // Show Error message
    void    Error( LPCTSTR pText );
    HRESULT showPropertyPage(IUnknown* pIU, const WCHAR* name);
    void    NukeDownstream(IBaseFilter *pf);
    void    ClearGraphs( );
    HRESULT InitCaptureGraph( );
    HRESULT SetErrorEvent();
    HRESULT UpdateFrameRateStatus(LONG* plNot);
    HRESULT StartGraph();
    HRESULT OneTimeStartup();
    DWORD   m_dwGraphRegister;
    HRESULT StopGraph();
    void    HaltGraph();
    void    RestartGraph();
    void    TearDownGraph();
    void    SetAlternateSetting();

    CBitmapRenderer*	m_pSnapshotter;

    std::auto_ptr<CTweetyFeatureControl> m_pDlgCameraControl;
	std::auto_ptr<CVISUsb3FeatureControl> m_pDlgVISUsb3CameraControl;  // the controls for the Videology USB3 Camera -- wcheng
	auto_ptr<CSelectdev> m_pDlgSelectdev;  //the controls for selecting camera -- wcheng

    // State for the pixel correction logic.

    enum {
        pcIdle = 0,
        pcGathering,
        pcComputing,
        pcVerifying,
        pcDisplaying
    };

    std::vector<BadPixels> m_BadPixels;
    long    m_pixcorrFrameCount;
    std::vector<long> m_pixcorrSum;
    int     m_pixcorrState;

    void    DrawResults();
    void    Fix1Pixel( int x, int y, BYTE loc );

    // Operations
public:
    CMenu* Menu() const {
        return GetParent()->GetMenu();
    }

    // Overrides
    int MessageBox( 
        LPCTSTR msg, 
        LPCTSTR cap = NULL, 
        UINT nStyle = MB_OK | MB_ICONEXCLAMATION
    );
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVidUSB2View)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct
    //}}AFX_VIRTUAL

    // Implementation
public:
    virtual ~CVidUSB2View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Fake IUnknown implementation.

    STDMETHODIMP QueryInterface(REFIID riid, __deref_out void **ppv) {
        if( riid == __uuidof(ISampleGrabberCB) )
            return ::GetInterface((ISampleGrabberCB*)this, ppv);
        return E_NOINTERFACE;
    }
    STDMETHODIMP_(ULONG) AddRef() {
        return 2;
    }
    STDMETHODIMP_(ULONG) Release() {
        return 1;
    }

    // ISampleCallbackCB implementation.

    STDMETHODIMP SampleCB( double, IMediaSample* )
    {
        return E_NOTIMPL;
    }

    STDMETHODIMP BufferCB( double, BYTE*, long );

    // IBitmapCallback implementation.

    virtual HRESULT Sample( IMediaSample* sample );

    // Generated message map functions
protected:
    //{{AFX_MSG(CVidUSB2View)
    afx_msg void OnOptionsVideocapturefilter();
    afx_msg void OnOptionsVideocapturepin();
    afx_msg void OnOptionsAdvanced();
    afx_msg void OnOptionsRestart();
	afx_msg void OnSelectCam();
    afx_msg void OnOptionsFactoryReset();
    afx_msg void OnUpdateCameracontrolCameracontrol(CCmdUI* pCmdUI);
    afx_msg void OnFileSetsnapimagefolder();
    afx_msg void OnCaptureSnap();
    afx_msg void OnChangeRotation(UINT nID);
    afx_msg void OnChangeSnapFormat(UINT nID);
    afx_msg void OnUpdateRotation(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSnapFormat(CCmdUI* pCmdUI);
    afx_msg void OnCameracontrolCameracontrol();
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point) ;
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point) ;
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point) ;
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point) ;
    afx_msg void OnUpdateMotion(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsFilter(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPin(CCmdUI* pCmdUI);
    afx_msg void OnSize(UINT, int, int);
    //}}AFX_MSG
    afx_msg LRESULT OnActiveMovieError(WPARAM wParam, LPARAM lParam);
    afx_msg void OnExitApplication();
    afx_msg void OnSwitchMonitors();
    afx_msg LRESULT OnMsgI2CFail(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgBLCOSDOn(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgBLCOSDOff(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgEscape(WPARAM wParam, LPARAM lParam);
    afx_msg void OnAutoPixelCorrection();
    afx_msg LRESULT OnProcessPixelCorrection(WPARAM wParam, LPARAM lParam);
    afx_msg void OnClearPixelCorrection();
    afx_msg void OnRemoveResults();
    DECLARE_MESSAGE_MAP()
public:
	AvailableCam_t CurCam;
};

#ifndef _DEBUG  // debug version in VidUSB2View.cpp
inline CVidUSB2Doc* CVidUSB2View::GetDocument()
   { return (CVidUSB2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

