#pragma once

// TweetyFeatureControl.h : header file
//
#define	TWEETYFEATURES				0xff
#define MSGFEATURE_I2CFAIL			WM_USER + 10				
#define MSGFEATURE_LOADSUCC			WM_USER + 11				
#define MSGFEATURE_LOADBEGIN		WM_USER + 12
#define MSGFEATURE_BLCOSDON			WM_USER + 14
#define MSGFEATURE_BLCOSDOFF		WM_USER + 15
#define MSGFEATURE_ESCKEY			WM_USER + 16		

#define LOADFEATURE_TIMEOUT			100 * 60

#include <map>
using namespace std;

#include "VidUSB2IO.h"
#include "FormattedFile.h"

/////////////////////////////////////////////////////////////////////////////
// CTweetyFeatureControl dialog

class CTweetyFeatureControl : public CDialog
{
// Construction
public:
	CTweetyFeatureControl(CVidUSB2Prop *pVidUSB2, bool* PortReady = NULL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTweetyFeatureControl)
	enum { IDD = IDD_DIALOG_FEATURECONTROL };
	CSliderCtrl	m_ctrlSlider_Gain;
	CSliderCtrl	m_ctrlSlider_Edge;
	CSliderCtrl	m_ctrlSlider_BLC;
	CSliderCtrl	m_ctrlSlider_RGain;
	CSliderCtrl	m_ctrlSlider_BGain;
	CProgressCtrl	m_ctrlPress;
	CComboBox	m_ctrlComboBoxWB;
	CEdit	m_ctrlEditRgain;
	CString	m_strEditRgain;
	CScrollBar	m_ctrlScrollBarRgain;
	CEdit	m_ctrlEditBgain;
	CString	m_strEditBgain;
	CScrollBar	m_ctrlScrollBarBgain;
	BOOL	m_boBLC;
	BOOL	m_boMirror;
	CComboBox	m_ctrlComboBoxShutter;
	BOOL	m_boGain;
	CString	m_strEditGain;
	CString	m_strEditBLCWeigh;
	CEdit	m_ctrlEditGain;
	CEdit	m_ctrlEditBLCWeigh;
	BOOL	m_boCheckEdge;
	CEdit	m_ctrlEditEdge;
	CString	m_strEditEdge;
	CComboBox	m_ctrlBLCSize;
	CComboBox	m_ctrlBLCPos;
	CComboBox	m_ctrlBLCPos_Y;
	CButton	m_bnReset;
	BOOL	m_boBLCOSD;
        // Motion stablization
        BOOL    m_boMotionStab;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTweetyFeatureControl)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	CVidUSB2Prop& m_VidUSB2;
	ULONG m_ulData[TWEETYFEATURES];//byData: eeprom1-4, dsp, features(commands)
	void EnableAllControls(BOOL boIsEnable);
	void UpdateBLCPosControls();
	void UpdateBLCSizeControls();
// Implementation
protected:

#ifdef _DEBUG
	CFormattedFile m_DLLTestingFile;
	int m_intDLLTestingIndex;
#endif
    ULONG m_unTimerOutCount;
    void turnBLCOSD(BOOL boF);

    byte m_byBLCPOS, m_byBLCSize;
    byte m_byDotC;
    BOOL m_boSetTimer;
    ULONG m_ulRGain, m_ulBGain;
    int m_intLastBLCWindowPos;
    bool m_boPortReady;

    ULONG m_ulCamID;
    HANDLE m_hThreadFinished1;

    BOOL _CommandRead(ULONG ulKeyCode);
    BOOL _CommandWrite(ULONG ulKeyCode);

    void ShowControlWindows(BOOL boF);
    void UpdateFeatureControls();
    void InitializeControls();
    void EnableGainControls(BOOL boIsEnable) ;
    void EnableAWBControls();
    void EnableEdgeControls(BOOL boIsEnable);
    void EnableBLCControls(BOOL boIsEnable) ;
    byte UpdateEditScroll(CString strEditValue,CEdit* ctrlEditValue, byte byMax, byte byMin, CSliderCtrl* pSlider);
    void UpdateFeatureWBM();

public:
	// Generated message map functions
	//{{AFX_MSG(CTweetyFeatureControl)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboWbm();
	afx_msg void OnCheckMirror();
	afx_msg void OnSelchangeComboShutter();
	afx_msg void OnCheckGain();
	afx_msg void OnUpdateEditGain();
	afx_msg void OnUpdateEditBLCWeigh();
	afx_msg void OnCheckEdge();
	afx_msg void OnUpdateEditEdge();
	afx_msg void OnSelchangeComboBlcsize();
	afx_msg void OnCheckInterlace();
	afx_msg void OnSelchangeComboBlcpos();	
	afx_msg void OnButtonReset();
	afx_msg void OnUpdateEditRgain();
	afx_msg void OnUpdateEditBgain();
	afx_msg void OnCheckBlc();
	afx_msg void OnCheckBlcOSD();
	afx_msg void OnReleasedcaptureSliderBgain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderBlc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderEdge(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderGain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRedgain(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

