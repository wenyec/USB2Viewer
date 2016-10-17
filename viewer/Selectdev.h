#pragma once

#include "VidUSB2.h"
#include "afxwin.h"


class CSelectdev : public CDialog
{
	DECLARE_DYNAMIC(CSelectdev)

public:
	CSelectdev(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectdev();
	static CSelectdev &getInstance();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTDEV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	HRESULT DeviceNameToMenu();
public:
	//CameraAttributes* pAvailableCam;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	AvailableCam_t SelDevIn;
	int uIndex = 0;
private:
	int NumCam;
	CListBox m_DevNameList;
	//CStringW AvailableCameraName[16];
	AvailableCam_t AvailableCam[16];
};
