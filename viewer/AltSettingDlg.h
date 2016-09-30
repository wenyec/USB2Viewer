
/////////////////////////////////////////////////////////////////////////////
// CAltSetting dialog

class CAltSettingDlg : public CDialog
{
public:
    CAltSettingDlg();

    // Dialog Data
    //{{AFX_DATA(CAltSettingDlg)
    enum { IDD = IDD_DIALOG_ALTSETTING };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

public:
    int m_Setting;

    // Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    // No message handlers
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAltSettingDlg::CAltSettingDlg() 
    : CDialog(CAltSettingDlg::IDD)
{
    //{{AFX_DATA_INIT(CAltSettingDlg)
    //}}AFX_DATA_INIT
}

void CAltSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAltSettingDlg)
    //}}AFX_DATA_MAP
    if( pDX->m_bSaveAndValidate )
        m_Setting = GetCheckedRadioButton( 
            IDC_RADIO_ALTSET0, IDC_RADIO_ALTSET1 
        ) - IDC_RADIO_ALTSET0;
    else
        CheckRadioButton( 
            IDC_RADIO_ALTSET0, 
            IDC_RADIO_ALTSET1,
            IDC_RADIO_ALTSET0 + m_Setting
        );

}

BEGIN_MESSAGE_MAP(CAltSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CAltSettingDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
