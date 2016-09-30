// Selectdev.cpp : implementation file
//

#include "stdafx.h"
#include "Selectdev.h"
#include "afxdialogex.h"
#include "VidUSB2.h"

// Selectdev dialog: create for the selection of a camera --wcheng

IMPLEMENT_DYNAMIC(CSelectdev, CDialog)

CSelectdev::CSelectdev(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectdev::IDD, pParent)
{

}

CSelectdev::~CSelectdev()
{
}

void CSelectdev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectdev, CDialog)
END_MESSAGE_MAP()


// Selectdev message handlers
