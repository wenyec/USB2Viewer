/*----------------------------------------------------------------------------*\
|   TweetyFeatureControl.cpp : implementation of the CTweetyFeatureControl class |
|                                                                              |
|   Author: Julia Zhu                                                          |
|                                                                              |
|   Company: Videology Imaging Solutions							           |
|                                                                              |
|   Revision History:                                                          |
|                                                                              |
\*----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "VidUSB2.h"
#include "TweetyFeatureControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTweetyFeatureControl dialog

CTweetyFeatureControl::CTweetyFeatureControl(
    CVidUSB2Prop *pVidUSB2,
    bool* PortReady,
    CWnd* pParent /*=NULL*/
)
    : CDialog( CTweetyFeatureControl::IDD, pParent )
    , m_VidUSB2(*pVidUSB2)
    , m_ulCamID( CAMID_D14X_MR_NTSC )
    , m_intLastBLCWindowPos(-1)
    , m_boPortReady(true)
    , m_boMotionStab(false)
{
    //{{AFX_DATA_INIT(CTweetyFeatureControl)
		m_strEditRgain = _T("");
		m_strEditBgain = _T("");
		m_boBLC = FALSE;
		m_boMirror = FALSE;
		m_boGain = TRUE;
		m_strEditGain = _T("");
		m_strEditBLCWeigh = _T("");
		m_boCheckEdge = FALSE;
		m_strEditEdge = _T("");
		m_boBLCOSD = FALSE;
    //}}AFX_DATA_INIT

#ifdef _DEBUG
    m_intDLLTestingIndex = 0;
#endif
    m_VidUSB2.vidGetCamID( &m_ulCamID );

    *PortReady = m_boPortReady;
}


void CTweetyFeatureControl::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTweetyFeatureControl)
    DDX_Control(pDX, IDC_SLIDER_GAIN, m_ctrlSlider_Gain);
    DDX_Control(pDX, IDC_SLIDER_EDGE, m_ctrlSlider_Edge);
    DDX_Control(pDX, IDC_SLIDER_BLC, m_ctrlSlider_BLC);
    DDX_Control(pDX, IDC_SLIDER_REDGAIN, m_ctrlSlider_RGain);
    DDX_Control(pDX, IDC_SLIDER_BGAIN, m_ctrlSlider_BGain);
    DDX_Control(pDX, IDC_PROGRESS1, m_ctrlPress);
    DDX_Control(pDX, IDC_COMBO_WBM, m_ctrlComboBoxWB);
    DDX_Control(pDX, IDC_EDIT_RGAIN, m_ctrlEditRgain);
    DDX_Text(pDX, IDC_EDIT_RGAIN, m_strEditRgain);
    DDX_Control(pDX, IDC_EDIT_BGAIN, m_ctrlEditBgain);
    DDX_Text(pDX, IDC_EDIT_BGAIN, m_strEditBgain);
    DDX_Check(pDX, IDC_CHECK_BLC, m_boBLC);
    DDX_Check(pDX, IDC_CHECK_MIRROR, m_boMirror);
    DDX_Control(pDX, IDC_COMBO_SHUTTER, m_ctrlComboBoxShutter);
    DDX_Check(pDX, IDC_CHECK_GAIN, m_boGain);
    DDX_Text(pDX, IDC_EDIT_GAIN, m_strEditGain);
    DDX_Text(pDX, IDC_EDIT_BLCWEIGH, m_strEditBLCWeigh);
    DDX_Control(pDX, IDC_EDIT_GAIN, m_ctrlEditGain);
    DDX_Control(pDX, IDC_EDIT_BLCWEIGH, m_ctrlEditBLCWeigh);
    DDX_Check(pDX, IDC_CHECK_EDGE, m_boCheckEdge);
    DDX_Control(pDX, IDC_EDIT_EDGE, m_ctrlEditEdge);
    DDX_Text(pDX, IDC_EDIT_EDGE, m_strEditEdge);
    DDX_Control(pDX, IDC_COMBO_BLCSIZE, m_ctrlBLCSize);
    DDX_Control(pDX, IDC_COMBO_BLCPOS, m_ctrlBLCPos);
    DDX_Control(pDX, IDC_COMBO_BLCPOS_Y, m_ctrlBLCPos_Y);
    DDX_Control(pDX, IDC_BUTTON_RESET, m_bnReset);
    DDX_Check(pDX, IDC_CHECK_BLCOSD, m_boBLCOSD);
    DDX_Check(pDX, IDC_CHECK_INTERLEAVE, m_boMotionStab);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTweetyFeatureControl, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_MIRROR, OnCheckMirror)
	ON_BN_CLICKED(IDC_CHECK_GAIN, OnCheckGain)
	ON_BN_CLICKED(IDC_CHECK_EDGE, OnCheckEdge)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_CHECK_BLC, OnCheckBlc)
	ON_BN_CLICKED(IDC_CHECK_BLCOSD, OnCheckBlcOSD)
	ON_BN_CLICKED(IDC_CHECK_INTERLEAVE, OnCheckInterlace)
	ON_EN_UPDATE(IDC_EDIT_GAIN, OnUpdateEditGain)
	ON_EN_UPDATE(IDC_EDIT_BLCWEIGH, OnUpdateEditBLCWeigh)
	ON_EN_UPDATE(IDC_EDIT_EDGE, OnUpdateEditEdge)
	ON_EN_UPDATE(IDC_EDIT_RGAIN, OnUpdateEditRgain)
	ON_EN_UPDATE(IDC_EDIT_BGAIN, OnUpdateEditBgain)
	ON_CBN_SELCHANGE(IDC_COMBO_WBM, OnSelchangeComboWbm)
	ON_CBN_SELCHANGE(IDC_COMBO_SHUTTER, OnSelchangeComboShutter)
	ON_CBN_SELCHANGE(IDC_COMBO_BLCSIZE, OnSelchangeComboBlcsize)
	ON_CBN_SELCHANGE(IDC_COMBO_BLCPOS, OnSelchangeComboBlcpos)
	ON_CBN_SELCHANGE(IDC_COMBO_BLCPOS_Y, OnSelchangeComboBlcpos)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BGAIN, OnReleasedcaptureSliderBgain)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLC, OnReleasedcaptureSliderBlc)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EDGE, OnReleasedcaptureSliderEdge)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GAIN, OnReleasedcaptureSliderGain)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_REDGAIN, OnReleasedcaptureSliderRedgain)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTweetyFeatureControl message handlers
void CTweetyFeatureControl::OnDestroy()
{
	CDialog::OnDestroy();

#ifdef _DEBUG
	m_DLLTestingFile.Close();
#endif
}


LRESULT CTweetyFeatureControl::WindowProc(
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch( message )
    {
        case WM_COMMAND:
            if( wParam == IDCANCEL && lParam == 0 )
                m_pParentWnd->PostMessage(MSGFEATURE_ESCKEY, 0, 0L);
            break;
        case MSGFEATURE_I2CFAIL:
            m_pParentWnd->PostMessage( MSGFEATURE_I2CFAIL, 0, 0L );
            DestroyWindow();
            break;
    }
    return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CTweetyFeatureControl::OnInitDialog()
{
    CDialog::OnInitDialog();

#ifdef _DEBUG
    m_DLLTestingFile.Create(
        _T("c:\\SDKtesting_WiewerLogFile.txt"), 
        GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS 
    );
    m_DLLTestingFile.Printf( "%s\n\n", "Videology USB2.0 Camera Viewer Log File (for DLL testing)");
#endif

    m_hThreadFinished1 = CreateEvent( NULL, TRUE, TRUE, NULL );

    // Set the control range and positions and properties.

    InitializeControls();

    // Create the new object for I2C communication.

    m_VidUSB2.vidGetAllFeatures(m_ulData);
    UpdateFeatureControls();
    ShowControlWindows(TRUE);

    return TRUE;
}

// Set the initial state of all of the controls, including ranges for
// the sliders.

void CTweetyFeatureControl::InitializeControls()
{
	m_ctrlPress.SetRange(0,100);

	m_ctrlSlider_Gain.SetRange(0x0,0xff,TRUE);
	m_ctrlSlider_Edge.SetRange(0,0x1f,TRUE);
	m_ctrlSlider_BLC.SetRange(1,0x40,TRUE);
	m_ctrlSlider_RGain.SetRange(0,0xff,TRUE);
	m_ctrlSlider_BGain.SetRange(0,0xff,TRUE);
}

void CTweetyFeatureControl::UpdateFeatureWBM()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-WBM\n", ++m_intDLLTestingIndex);
#endif

    // White balance mode.

    if( IsColor(m_ulCamID) )
    {
        if(m_ulData[D14_WBM] < 4)
            m_ctrlComboBoxWB.SetCurSel(m_ulData[D14_WBM]);

        if(m_ulData[D14_WBM] == 1 || m_ulData[D14_WBM] == 0)
        {
            m_strEditRgain.Format(_T("0x%x"), (byte)m_ulData[D14_RGAIN]);
            m_strEditBgain.Format(_T("0x%x"), (byte)m_ulData[D14_BGAIN]);
            m_ctrlSlider_RGain.SetPos((int)m_ulData[D14_RGAIN]);
            m_ctrlSlider_BGain.SetPos((int)m_ulData[D14_BGAIN]);
        }
    }

    EnableAWBControls();
}

void CTweetyFeatureControl::EnableAWBControls()
{
	BOOL bOn = 
        IsColor(m_ulCamID) &&
        (m_ctrlComboBoxWB.GetCurSel() == 1) && 
        m_boPortReady;
	GetDlgItem(IDC_EDIT_RGAIN)->EnableWindow( bOn );
	GetDlgItem(IDC_SLIDER_REDGAIN)->EnableWindow( bOn );
	GetDlgItem(IDC_EDIT_BGAIN)->EnableWindow( bOn );
	GetDlgItem(IDC_SLIDER_BGAIN)->EnableWindow( bOn );
}



void CTweetyFeatureControl::UpdateFeatureControls()
{
    CString strC;
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-Update all features\n", ++m_intDLLTestingIndex);
#endif
    UpdateData(TRUE);

    // Mirroring.

    m_boMirror = (m_ulData[D14_MIRROR] >0 ) ? TRUE: FALSE;

    // Shutter speed.

    if(m_ulData[D14_SHUTTERMODE] < ssMax )
        m_ctrlComboBoxShutter.SetCurSel(m_ulData[D14_SHUTTERMODE]);

    // Backlight compensation.

    m_boBLC = (m_ulData[D14_BLCWEIGH] == 0x00000000) ? FALSE : TRUE;
    m_strEditBLCWeigh.Format(_T("0x%x"), (byte)m_ulData[D14_BLCWEIGH]);
    m_ctrlSlider_BLC.SetPos((int)m_ulData[D14_BLCWEIGH]);
    turnBLCOSD( m_boBLC );
    EnableBLCControls( m_boBLC );

    // White balance mode.

    UpdateFeatureWBM();

    // Gain.

    m_boGain = !(m_ulData[D14_GAIN] >> 31);
    m_strEditGain.Format(_T("0x%x"), (byte)m_ulData[D14_GAIN]);

    m_ctrlSlider_Gain.SetPos((int)(m_ulData[D14_GAIN] & 0x7fffffff));
    EnableGainControls(m_boGain);

    // BLC size.

    if(m_ulData[D14_BLCWINSIZE] < 15)	 {
        m_ctrlBLCSize.SetCurSel(m_ulData[D14_BLCWINSIZE]);	}

    // BLC position.

    if(m_ulData[D14_BLCWINPOS] < 64)
    {
        int intT = m_ulData[D14_BLCWINPOS];
        m_ctrlBLCPos.SetCurSel(intT / 8);
        m_ctrlBLCPos_Y.SetCurSel(intT % 8);
    }

    // Edge enhancement.

    m_boCheckEdge = (m_ulData[D14_EDGEENHANCE] < 0xc0);
    if( !m_boCheckEdge )
        m_ulData[D14_EDGEENHANCE] = 0xc0;
    m_strEditEdge.Format(_T("0x%x"), m_ulData[D14_EDGEENHANCE]);
    m_ctrlSlider_Edge.SetPos(m_ulData[D14_EDGEENHANCE]);
    EnableEdgeControls(m_boCheckEdge);

    // Interlaced status.

    // 0 = progressive
    // 1 = bob (enhanced)
    // 2 = weave
    m_boMotionStab = (m_ulData[D14_NONINTERLACED] == ilBob);
    UpdateData(FALSE);
}

void CTweetyFeatureControl::UpdateBLCPosControls()
{
	if(m_ulData[D14_BLCWINPOS] < 64)
	{
		int intT = m_ulData[D14_BLCWINPOS];
		intT = intT/8;
		m_ctrlBLCPos.SetCurSel(intT);
		m_ctrlBLCPos_Y.SetCurSel(m_ulData[D14_BLCWINPOS] - intT*8);
		UpdateData(FALSE);

		_CommandWrite(D14_BLCWINPOS);
	}
}

void CTweetyFeatureControl::UpdateBLCSizeControls()
{
	if(m_ulData[D14_BLCWINSIZE] < 15)
	{
		m_ctrlBLCSize.SetCurSel(m_ulData[D14_BLCWINSIZE]);
		UpdateData(FALSE);

		_CommandWrite(D14_BLCWINSIZE);
	}
}

void CTweetyFeatureControl::EnableBLCControls(BOOL boIsEnable)
{
	GetDlgItem(IDC_EDIT_BLCWEIGH)->EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_SLIDER_BLC)->EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_COMBO_BLCSIZE)->EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_COMBO_BLCPOS)->EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_COMBO_BLCPOS_Y)->EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_CHECK_BLCOSD)->EnableWindow(boIsEnable && m_boPortReady);
    if( 
        boIsEnable 
        &&
        (m_ctrlComboBoxShutter.GetCurSel() != ssAuto1)
        &&
        !IsK45(m_ulCamID)
    )
    {
        // Force shutter mode to automatic.

        m_ulData[D14_SHUTTERMODE] = ssAuto1;
        m_ctrlComboBoxShutter.SetCurSel( ssAuto1 );
        UpdateData( FALSE );
        _CommandWrite(D14_SHUTTERMODE);
    }
}

//
// Enable the shutter control scroll bar.
//
void CTweetyFeatureControl::EnableEdgeControls(BOOL boIsEnable)
{
	GetDlgItem(IDC_EDIT_EDGE)->EnableWindow(boIsEnable && m_boPortReady);
	m_ctrlSlider_Edge.EnableWindow(boIsEnable && m_boPortReady);
}

//
// Enable the gain control scroll bar.
//
void CTweetyFeatureControl::EnableGainControls(BOOL boIsEnable)
{
	m_ctrlSlider_Gain.EnableWindow(boIsEnable && m_boPortReady);
	GetDlgItem(IDC_EDIT_GAIN)->EnableWindow(boIsEnable && m_boPortReady);
}

void CTweetyFeatureControl::OnCheckMirror()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-MIRROR\n", ++m_intDLLTestingIndex);
#endif
    UpdateData( TRUE );
    m_boMirror=((CButton*)GetDlgItem(IDC_CHECK_MIRROR))->GetCheck();
    UpdateData( FALSE );

    m_ulData[D14_MIRROR] = m_boMirror ? 0x000000ff: 0;

    _CommandWrite(D14_MIRROR);
}

void CTweetyFeatureControl::OnCheckBlc()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-CHECK BLC WEIGHT\n", ++m_intDLLTestingIndex);
#endif
    // Get the status of the check box.

    UpdateData( TRUE );
    m_boBLC = ((CButton*)GetDlgItem(IDC_CHECK_BLC))->GetCheck();

    // Turn on/off OSD.

    if(!m_boBLC) 
        turnBLCOSD(m_boBLC);

    // Set the value from the status of the check box.

    m_ulData[D14_BLCWEIGH] = m_boBLC ? 0x40 : 0;

    m_strEditBLCWeigh.Format(_T("0x%x"), (byte)m_ulData[D14_BLCWEIGH]);
    m_ctrlSlider_BLC.SetPos((byte)m_ulData[D14_BLCWEIGH]);
    EnableBLCControls(m_boBLC);

    UpdateData( FALSE );

    _CommandWrite(D14_BLCWEIGH);
}

void CTweetyFeatureControl::turnBLCOSD(BOOL boF)
{
    m_boBLCOSD = boF && m_boPortReady;
    ((CButton*)GetDlgItem(IDC_CHECK_BLCOSD))->SetCheck(m_boBLCOSD);

    if(m_boBLCOSD)
        m_pParentWnd->PostMessage(MSGFEATURE_BLCOSDON, 0, 0L);
    else
        m_pParentWnd->PostMessage(MSGFEATURE_BLCOSDOFF, 0, 0L);
}

void CTweetyFeatureControl::OnCheckBlcOSD()
{
    UpdateData( TRUE );
    m_boBLCOSD = ((CButton*)GetDlgItem(IDC_CHECK_BLCOSD))->GetCheck();

    turnBLCOSD(m_boBLCOSD);
    UpdateData( FALSE );
}

void CTweetyFeatureControl::OnButtonReset()
{
    if(_CommandWrite(D14_RESET))
    {
        m_VidUSB2.vidGetAllFeatures(m_ulData);
        UpdateFeatureControls();
        //AfxMessageBox("To finish reset, close this software and restart the camera.");
    }
    else
        AfxMessageBox(_T("Couldn't reset the camera.."));
}
void CTweetyFeatureControl::OnCheckGain()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-CHECK GAIN\n", ++m_intDLLTestingIndex);
#endif
    UpdateData( TRUE );

    // Get the check box status and enable the scroll bar.

    m_boGain = ((CButton*)GetDlgItem(IDC_CHECK_GAIN))->GetCheck();

    // Set the status for the auto mode, when the check box is not checked.

    m_ulData[D14_GAIN] = (m_ulData[D14_GAIN] & 0xff) | (m_boGain ? 0 : 0x80000000);

    m_strEditGain.Format(_T("0x%x"), (byte)m_ulData[D14_GAIN]);
    m_ctrlSlider_Gain.SetPos((byte)m_ulData[D14_GAIN]);
    EnableGainControls(m_boGain);
    UpdateData( FALSE );

    _CommandWrite(D14_GAIN);
}

byte CTweetyFeatureControl::UpdateEditScroll(
    CString strEditValue,
    CEdit* ctrlEditValue,
    byte byMax,
    byte byMin,
    CSliderCtrl* pSlider
)
{
    // Display according to format
    DWORD dwValue = _tcstoul( strEditValue, NULL, 16 );
    byte byValue = (byte)min( max( dwValue, byMax ), byMin );
    // Set the position of the scrollbar.
    pSlider->SetPos((int)byValue);
    ctrlEditValue->SetSel( strEditValue.GetLength(), strEditValue.GetLength());

    return byValue;
}

void CTweetyFeatureControl::OnUpdateEditGain()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-EDIT GAIN \n", ++m_intDLLTestingIndex);
#endif

    UpdateData(TRUE);

    m_ulData[D14_GAIN] = UpdateEditScroll(m_strEditGain, &m_ctrlEditGain, 0xff, 0x00, &m_ctrlSlider_Gain);
    m_strEditGain.Format(_T("0x%x"), (byte)m_ulData[D14_GAIN]);
    UpdateData( FALSE );

    _CommandWrite(D14_GAIN);
}

void CTweetyFeatureControl::OnUpdateEditBLCWeigh()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-EDIT BLC WEIGHT \n", ++m_intDLLTestingIndex);
#endif
    UpdateData(TRUE);
    byte byValue = UpdateEditScroll(m_strEditBLCWeigh, &m_ctrlEditBLCWeigh, 0x40, 0x01, &m_ctrlSlider_BLC);
    m_ulData[D14_BLCWEIGH] = (ULONG)byValue;
    m_strEditBLCWeigh.Format(_T("0x%x"), byValue);
    UpdateData( FALSE );

    _CommandWrite(D14_BLCWEIGH);
}

void CTweetyFeatureControl::OnCheckEdge()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-CHECK EDGE \n", ++m_intDLLTestingIndex);
#endif
    UpdateData( TRUE );

    // Get the check box status and enable the scroll bar.

    m_boCheckEdge=((CButton*)GetDlgItem(IDC_CHECK_EDGE))->GetCheck();

    // Set the status for the auto mode, when the check box is not checked.

    m_ulData[D14_EDGEENHANCE] = (m_boCheckEdge) ? 0 : 0x000000c0;

    m_strEditEdge.Format(_T("0x%x"), (byte)m_ulData[D14_EDGEENHANCE]);
    m_ctrlSlider_Edge.SetPos((int)m_ulData[D14_EDGEENHANCE]);
    EnableEdgeControls(m_boCheckEdge);
    UpdateData( FALSE );

    _CommandWrite(D14_EDGEENHANCE);
}

void CTweetyFeatureControl::OnUpdateEditEdge()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-EDIT EDGE \n", ++m_intDLLTestingIndex);
#endif

    UpdateData(TRUE);
    m_ulData[D14_EDGEENHANCE] = (ULONG)UpdateEditScroll(m_strEditEdge, &m_ctrlEditEdge, 0x1f, 0, &m_ctrlSlider_Edge);
    m_strEditEdge.Format(_T("0x%x"), (byte)m_ulData[D14_EDGEENHANCE]);
    UpdateData( FALSE );

    _CommandWrite(D14_EDGEENHANCE);
}

void CTweetyFeatureControl::OnSelchangeComboShutter()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SHUTTER \n", ++m_intDLLTestingIndex);
#endif
    UpdateData( TRUE );
    m_ulData[D14_SHUTTERMODE] = (ULONG)m_ctrlComboBoxShutter.GetCurSel();
    if( !IsK45(m_ulCamID) && m_boBLC )
    {
        m_boBLC = FALSE;
        m_ulData[D14_BLCWEIGH] = 0;
        turnBLCOSD( m_boBLC );
        EnableBLCControls( m_boBLC );
    }
    UpdateData( FALSE );

    _CommandWrite(D14_SHUTTERMODE);
}

void CTweetyFeatureControl::OnCheckInterlace()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-INTERLACED \n", ++m_intDLLTestingIndex);
#endif

    UpdateData( TRUE );
    m_boMotionStab = ((CButton*)GetDlgItem(IDC_CHECK_INTERLEAVE))->GetCheck();
    m_ulData[D14_NONINTERLACED] = m_boMotionStab ? ilBob : ilWeave;
    _CommandWrite(D14_NONINTERLACED);
    UpdateData( FALSE );
}

void CTweetyFeatureControl::OnSelchangeComboBlcsize()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-BLC SIZE \n", ++m_intDLLTestingIndex);
#endif
    UpdateData(TRUE);
    //set window size
    m_ulData[D14_BLCWINSIZE] = (ULONG)m_ctrlBLCSize.GetCurSel();

    _CommandWrite(D14_BLCWINSIZE);

    UpdateData( FALSE );
}

void CTweetyFeatureControl::OnSelchangeComboBlcpos()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-BLC POSITION \n", ++m_intDLLTestingIndex);
#endif
    UpdateData(TRUE);
    m_ulData[D14_BLCWINPOS] = (ULONG)(m_ctrlBLCPos.GetCurSel() * 8 + m_ctrlBLCPos_Y.GetCurSel());
    UpdateData( FALSE );

    _CommandWrite(D14_BLCWINPOS);
}

void CTweetyFeatureControl::OnSelchangeComboWbm()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-WBM \n", ++m_intDLLTestingIndex);
#endif
    UpdateData( TRUE );

    m_ulData[D14_WBM] = (ULONG)m_ctrlComboBoxWB.GetCurSel();

    if(m_ulData[D14_WBM] == 1 || m_ulData[D14_WBM] == 0)
    {
        if(!_CommandRead(D14_RGAIN)) return;
        if(!_CommandRead(D14_BGAIN)) return;
    }

    UpdateFeatureWBM();
    UpdateData(FALSE);

    _CommandWrite(D14_WBM);
}

void CTweetyFeatureControl::OnUpdateEditRgain()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-EDIT R-GAIN \n", ++m_intDLLTestingIndex);
#endif

    // Change item value
    UpdateData( TRUE );
    if( m_strEditRgain.Find( _T("0x") ) == -1 )
        m_strEditRgain = _T("0x") + m_strEditRgain;

    // Display according to format
    DWORD dwValue = _tcstoul( m_strEditRgain, NULL, 16 );
    byte byValue = (byte) min( dwValue, 255 );
    m_strEditRgain.Format(_T("0x%x"), byValue);

    m_ulData[D14_RGAIN] = (ULONG)byValue;

    // Set the position of the scrollbar
    m_ctrlSlider_RGain.SetPos((int)byValue);

    // Set the cursor position to the last char.
    m_ctrlEditRgain.SetSel( m_strEditRgain.GetLength(), m_strEditRgain.GetLength());
    UpdateData( FALSE );

    _CommandWrite(D14_RGAIN);
}

void CTweetyFeatureControl::OnUpdateEditBgain()
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-EDIT B-GAIN \n", ++m_intDLLTestingIndex);
#endif
    // Change item value
    UpdateData( TRUE );
    if( m_strEditBgain.Find( _T("0x") ) == -1 )
        m_strEditBgain = _T("0x") + m_strEditBgain;

    // Display according to format

    DWORD dwValue = _tcstoul( m_strEditRgain, NULL, 16 );
    byte byValue = (byte) min( dwValue, 255 );
    m_strEditBgain.Format(_T("0x%x"), byValue);

    m_ulData[D14_BGAIN] = (ULONG)byValue;

    // Set the position of the scrollbar

    m_ctrlSlider_BGain.SetPos((int)byValue);

    // Set the cursor position to the last char.

    m_ctrlEditBgain.SetSel( m_strEditBgain.GetLength(), m_strEditBgain.GetLength());
    UpdateData( FALSE );

    _CommandWrite(D14_BGAIN);
}

BOOL CTweetyFeatureControl::_CommandRead(ULONG ulKeyCode)
{
    BeginWaitCursor();

    HRESULT hr = m_VidUSB2.vidGetFeature(ulKeyCode, &m_ulData[ulKeyCode]);

#ifdef _DEBUG
    m_DLLTestingFile.Printf( "Command Read		key = %d, Value = %d, return = %s\n", ulKeyCode, m_ulData[ulKeyCode], FAILED(hr) ? "FAIL" : "OK");
#else
    if(FAILED(hr))
    {
        if(MessageBox(_T("Communication with the camera lost. Try Again?"), _T("Alert!"), MB_OKCANCEL) == IDOK)
        {
            ShowControlWindows(FALSE);
            m_VidUSB2.vidDestroyPort();
            m_boPortReady = m_VidUSB2.vidInitPort(_T("Videology USB Camera"));
            if(m_boPortReady)
            {
                m_VidUSB2.vidGetAllFeatures(m_ulData);
                UpdateFeatureControls();
            }
        }
        else
        {
            PostMessage( MSGFEATURE_I2CFAIL, 0, 0L);
            m_pParentWnd->PostMessage( MSGFEATURE_I2CFAIL, 0, 0L);
        }
        EndWaitCursor();
        return FALSE;
    }
#endif

    EndWaitCursor();
    return TRUE;
}

BOOL CTweetyFeatureControl::_CommandWrite(ULONG ulKeyCode)
{
    BeginWaitCursor();

    ULONG ulValue = m_ulData[ulKeyCode];
    HRESULT hr = m_VidUSB2.vidSetFeature(ulKeyCode, &ulValue);

#ifdef _DEBUG
    m_DLLTestingFile.Printf(
        "Command Write		key = %d, Value = %d, return = %s\n",
        ulKeyCode, ulValue, FAILED(hr) ? "FAIL" : "OK");
#else
    if(FAILED(hr))
    {
        if( MessageBox(
                _T("Communication with the camera lost. Try Again?"),
                _T("Alert!"),
                MB_OKCANCEL) == IDOK
        )
        {
            ShowControlWindows(FALSE);
            m_VidUSB2.vidDestroyPort();
            m_boPortReady = m_VidUSB2.vidInitPort(_T("Videology USB Camera"));
            if(m_boPortReady)
            {
                m_VidUSB2.vidGetAllFeatures(m_ulData);
                UpdateFeatureControls();
            }
        }
        else
        {
            PostMessage(MSGFEATURE_I2CFAIL, 0, 0L);
            m_pParentWnd->PostMessage(MSGFEATURE_I2CFAIL, 0, 0L);
        }
        EndWaitCursor();
        return FALSE;
    }
#endif

    EndWaitCursor();
    return TRUE;
}

void CTweetyFeatureControl::ShowControlWindows(BOOL boF)
{
    GetDlgItem(IDC_STATIC_LOADFEATURES)->ShowWindow(!boF);
    GetDlgItem(IDC_PROGRESS1)->ShowWindow(!boF);

    GetDlgItem(IDC_STATIC_BLCWEIGHT)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_GAINGROUP)->ShowWindow(boF);
    GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_GAIN)->ShowWindow(boF);
    GetDlgItem(IDC_SLIDER_GAIN)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_EDGEGROUP)->ShowWindow(boF);
    GetDlgItem(IDC_SLIDER_EDGE)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_BLCGROUP)->ShowWindow(boF);
    GetDlgItem(IDC_SLIDER_BLC)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_BLC)->ShowWindow(boF);
    GetDlgItem(IDC_SLIDER_REDGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_SLIDER_BGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_BLCOSD)->ShowWindow(boF);

    GetDlgItem(IDC_STATIC_WINPOS)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_BLCPOSY)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_BLCSIZE)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_SHUTTER)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_WBMODE)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_BGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_RGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_STATIC_WBM_ELM)->ShowWindow(boF);
    GetDlgItem(IDC_COMBO_BLCPOS)->ShowWindow(boF);
    GetDlgItem(IDC_COMBO_BLCPOS_Y)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_EDGE)->ShowWindow(boF);
    GetDlgItem(IDC_COMBO_BLCSIZE)->ShowWindow(boF);
    GetDlgItem(IDC_COMBO_SHUTTER)->ShowWindow(boF);
    GetDlgItem(IDC_COMBO_WBM)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_MIRROR)->ShowWindow(boF);
    GetDlgItem(IDC_EDIT_BGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_EDIT_RGAIN)->ShowWindow(boF);
    GetDlgItem(IDC_EDIT_BLCWEIGH)->ShowWindow(boF);
    GetDlgItem(IDC_EDIT_GAIN)->ShowWindow(boF);
    GetDlgItem(IDC_EDIT_EDGE)->ShowWindow(boF);
    GetDlgItem(IDC_CHECK_INTERLEAVE)->ShowWindow(boF);
}

void CTweetyFeatureControl::EnableAllControls(BOOL boF)
{
    GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(boF);
    GetDlgItem(IDC_CHECK_GAIN)->EnableWindow(boF);
    GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(boF);
    GetDlgItem(IDC_SLIDER_EDGE)->EnableWindow(boF);
    GetDlgItem(IDC_SLIDER_BLC)->EnableWindow(boF);
    GetDlgItem(IDC_CHECK_BLC)->EnableWindow(boF);
    GetDlgItem(IDC_SLIDER_REDGAIN)->EnableWindow(boF);
    GetDlgItem(IDC_SLIDER_BGAIN)->EnableWindow(boF);

    GetDlgItem(IDC_COMBO_BLCPOS)->EnableWindow(boF);
    GetDlgItem(IDC_COMBO_BLCPOS_Y)->EnableWindow(boF);
    GetDlgItem(IDC_CHECK_EDGE)->EnableWindow(boF);
    GetDlgItem(IDC_COMBO_BLCSIZE)->EnableWindow(boF);
    GetDlgItem(IDC_CHECK_INTERLEAVE)->EnableWindow(boF);
    GetDlgItem(IDC_COMBO_SHUTTER)->EnableWindow(boF);
    GetDlgItem(IDC_COMBO_WBM)->EnableWindow(boF);
    GetDlgItem(IDC_CHECK_MIRROR)->EnableWindow(boF);
    GetDlgItem(IDC_EDIT_BGAIN)->EnableWindow(boF);
    GetDlgItem(IDC_EDIT_RGAIN)->EnableWindow(boF);
    GetDlgItem(IDC_EDIT_BLCWEIGH)->EnableWindow(boF);
    GetDlgItem(IDC_EDIT_GAIN)->EnableWindow(boF);
    GetDlgItem(IDC_EDIT_EDGE)->EnableWindow(boF);
    UpdateData(FALSE);
}

void CTweetyFeatureControl::OnReleasedcaptureSliderBgain(NMHDR* pNMHDR, LRESULT* pResult)
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SCROLL BGAIN\n", ++m_intDLLTestingIndex);
#endif
    m_ulData[D14_BGAIN] = (ULONG)m_ctrlSlider_BGain.GetPos();
    m_strEditBgain.Format(_T("0x%x"), (byte)m_ulData[D14_BGAIN]);
    UpdateData(FALSE);

    if(_CommandWrite(D14_BGAIN))
        *pResult = 0;
}

void CTweetyFeatureControl::OnReleasedcaptureSliderBlc(NMHDR* pNMHDR, LRESULT* pResult)
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SCROLL BLC WEIGHT\n", ++m_intDLLTestingIndex);
#endif
    m_ulData[D14_BLCWEIGH] = (ULONG)m_ctrlSlider_BLC.GetPos();
    m_strEditBLCWeigh.Format(_T("0x%x"), (byte)m_ulData[D14_BLCWEIGH]);
    UpdateData(FALSE);

    if(_CommandWrite(D14_BLCWEIGH))
        *pResult = 0;
}

void CTweetyFeatureControl::OnReleasedcaptureSliderEdge(NMHDR* pNMHDR, LRESULT* pResult)
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SCROLL EDGE ENHANCEMENT\n", ++m_intDLLTestingIndex);
#endif
    //get the value and save it to array
    m_ulData[D14_EDGEENHANCE] = (ULONG)m_ctrlSlider_Edge.GetPos();
    m_strEditEdge.Format(_T("0x%x"), (byte)m_ulData[D14_EDGEENHANCE]);
    UpdateData(FALSE);

    if(_CommandWrite(D14_EDGEENHANCE))
        *pResult = 0;
}

void CTweetyFeatureControl::OnReleasedcaptureSliderGain(NMHDR* pNMHDR, LRESULT* pResult)
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SCROLL GAIN\n", ++m_intDLLTestingIndex);
#endif
    m_ulData[D14_GAIN] = (ULONG)m_ctrlSlider_Gain.GetPos();
    m_strEditGain.Format(_T("0x%x"), (byte)m_ulData[D14_GAIN]);
    UpdateData(FALSE);

    if(_CommandWrite(D14_GAIN))
        *pResult = 0;
}

void CTweetyFeatureControl::OnReleasedcaptureSliderRedgain(NMHDR* pNMHDR, LRESULT* pResult)
{
#ifdef _DEBUG
    m_DLLTestingFile.Printf( "%d		GUI-SCROLL RGAIN\n", ++m_intDLLTestingIndex);
#endif
    int intValue = (ULONG)m_ctrlSlider_RGain.GetPos();
    m_ulData[D14_RGAIN] = (ULONG)intValue;
    m_strEditRgain.Format(_T("0x%x"), (byte)m_ulData[D14_RGAIN]);
    UpdateData(FALSE);

    if(_CommandWrite(D14_RGAIN))
        *pResult = 0;
}
