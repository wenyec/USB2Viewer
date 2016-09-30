#pragma once

#include "VidUSB2.h"

// Selectdev dialog: create for the selection of the camera -- wcheng

class CSelectdev : public CDialog
{
	DECLARE_DYNAMIC(CSelectdev)

public:
	CSelectdev(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectdev();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTDEV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
