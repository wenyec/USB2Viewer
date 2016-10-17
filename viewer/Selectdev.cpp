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
	, NumCam(0)
	//, SelDevice(0, 0)
{

}

CSelectdev::~CSelectdev()
{
}

void CSelectdev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE_LIST, m_DevNameList);
}


BEGIN_MESSAGE_MAP(CSelectdev, CDialog)
END_MESSAGE_MAP()

static CSelectdev &getInstance(){
	static CSelectdev instance;
	return instance;
}

// Selectdev message handlers

HRESULT CSelectdev::DeviceNameToMenu()
{
	TRACE(__FUNCTION__ "\n");
	HRESULT hr;

	// Create an enumerator.

	CComPtr< ICreateDevEnum > pCreateDevEnum;
	pCreateDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);

	ASSERT(pCreateDevEnum);
	if (!pCreateDevEnum)
		return E_FAIL;

	// Enumerate the list of video capture devices.

	CComPtr< IEnumMoniker > pEm;
	pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);

	if (!pEm)
		return E_FAIL;

	pEm->Reset();


	// Enumerate through the list and grab the first video capture device.
	UINT uIndex = 0;
	ULONG ulFetched = 0;
	CComPtr< IMoniker > pM;
	while ( pEm->Next(1, &pM, &ulFetched) == S_OK)// the loop runs until no device needs to be checked. -- wcheng's note
	{
		//hr = pEm->Next(1, &pM, &ulFetched);
		//if (FAILED(hr) || !pM)
			//break;

		// Get the property bag interface from the moniker.

		CComPtr< IPropertyBag > pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pBag);
		if (FAILED(hr)){
			pM.Release();
			continue;
		}

		// Go read the device path from the property bag.

		CComVariant var;
		hr = pBag->Read(L"DevicePath", &var, NULL);
		if (FAILED(hr))
			continue;

		// If this is one of our devices, go bind to it to get the
		// base filter interface.

		CStringW szName = var.bstrVal;
		szName = szName.MakeLower();
		if (szName.Find(L"usb#") < 0)
			continue;

		// We have a USB camera.  Extract the VID and PID.
		//
		// \\?\usb#vid_xxxx&pid_xxxx
		// 0123456789012345678901
		//
		// Technically, the format of the device path is undocumented.
		// However, this format has remained stable since Win95 OSR2
		// and is unlikely to change in our lifetime.
#if 0
		/* remove the following code for getting camera VID/PID */
		int i = szName.Find(L"vid_");
		ULONG vid = wcstol(szName.Mid(i + 4, 4), NULL, 16);
		i = szName.Find(L"pid_");
		ULONG pid = wcstol(szName.Mid(i + 4, 4), NULL, 16);

		ULONG VidPid = (vid << 16) | pid;

		FLONG Attributes = 0;
		for (
			const CameraAttributes* camAttr = CameraPids;
			camAttr->VidPid;  //if camAttr->VidPid == 0, the loop is stopped. -- wcheng's note
			camAttr++
			)
		{
			if (VidPid == camAttr->VidPid) // check the camera type based on VidPid -- wcheng's note
			{
				// This is one of ours.
				Attributes = camAttr->Attributes;
				//break;  // let record all available cameras -- wcheng
			}
		}

		// Have we reached the chosen index?
#if 0 // move following code out of the while loop.
		if (Attributes && !index--)  //index ??? -wcheng
		{
			if (!(*ppCap)) //check if a camera binded -- wcheng's note
				pM->BindToObject(0, 0, IID_IBaseFilter, (void**)ppCap);
			//break;
		}
#endif
		/* to get the camera records */
		AvailableCameraAttr[uIndex].VidPid = VidPid;
		AvailableCameraAttr[uIndex].Attributes = Attributes;
#endif
		hr = pBag->Read(L"FriendlyName", &var, NULL);
		if (FAILED(hr))
			continue;

		// If this is one of our devices, go bind to it to get the
		// base filter interface.

		AvailableCam[uIndex].AvailableCameraName = var.bstrVal;
		AvailableCam[uIndex].AvailabeCameraIMo = pM;
		uIndex++;
		pM.Release();
		pBag.Release();
	}
	pM.Release();
	NumCam = uIndex;
	pEm.Release();
	pCreateDevEnum.Release();

	return S_OK;
}


BOOL CSelectdev::OnInitDialog()
{
	CDialog::OnInitDialog();
	//devCap->fDeviceMenuPopulated = false;
	DeviceNameToMenu(); // enumerate devide list for extended control.

	// TODO:  Add extra initialization here
	for (int i = 0; i < NumCam; i++)
	{
		m_DevNameList.AddString(AvailableCam[i].AvailableCameraName);
	}
	//m_DevNameList.UpdateData();
	for (int i = 0; i < NumCam; i++)
	{
		int index = m_DevNameList.FindString(-1, AvailableCam[i].AvailableCameraName);
		m_DevNameList.SetItemData(index, i);
	}


	// Assume no selection for now.
	// gcap.iSelectedDeviceIndex = (UINT32)-1;

	if (NumCam == 0)
	{
		// If there are no devices, disable the "OK" button.
		//EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

}


void CSelectdev::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	int sel = m_DevNameList.GetCurSel();

	if (sel != LB_ERR)
	{
		SelDevIn.AvailabeCameraIMo = AvailableCam[(UINT32)m_DevNameList.GetItemData(sel)].AvailabeCameraIMo;
		SelDevIn.AvailableCameraName = AvailableCam[(UINT32)m_DevNameList.GetItemData(sel)].AvailableCameraName;
		uIndex = sel;
#if 0
		int j;
		for (j = 0; j < NumCam; j++){
			if (devCap->vis_camID[devCap->iSelectedDeviceIndex].VidPid == visCamID[j].VidPid){
				devCap->CamIndex = j;
				break;
			}
		}
		if (j >= NumCam){
			devCap->CamIndex = 0xff; //it's not VIS camera.
		}
#endif
	}
	else{
		SelDevIn.AvailabeCameraIMo = AvailableCam[(UINT32)m_DevNameList.GetItemData(0)].AvailabeCameraIMo;
		SelDevIn.AvailableCameraName = AvailableCam[(UINT32)m_DevNameList.GetItemData(0)].AvailableCameraName;
#
	}

	CDialog::OnOK();
}


void CSelectdev::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}
