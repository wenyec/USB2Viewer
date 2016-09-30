// Setup.cpp -- Tools to find the driver filename path of the first device
//    advertising a particular device interface GUID.
//
// Tim Roberts, 2009-Aug-28, Providenza & Boekelheide, Inc.
// Copyright (C) 2009, Videology, Inc.

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <devguid.h>
#include <atlstr.h>
#include <memory>
using std::auto_ptr;

#include <initguid.h>
#include "Setup.h"

#pragma comment( lib, "setupapi.lib" )

CString TranslateLastError()
{
    CString sz = L"Unknown error";
    LPSTR lpMsgBuf;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR) &lpMsgBuf,
            0,
            NULL
    ))
    {
        sz = lpMsgBuf;
        LocalFree(lpMsgBuf);
    }

    return sz;
}

// This code interfaces with the Device Manager, using the SetupDi
// APIs.  These APIs are extremely flexible, but because of that this
// code must be very wordy.
/*
PTCHAR
GetDevicePath( IN LPCGUID InterfaceGuid )
{
    HDEVINFO HardwareDeviceInfo;
    ULONG Length, RequiredLength = 0;
    BOOL bResult;

    // Fetch the set of all devices that expose the device interface
    // given to us.

    HardwareDeviceInfo = SetupDiGetClassDevs(
        InterfaceGuid,
        NULL,
        NULL,
        (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE)
    );

    if( HardwareDeviceInfo == INVALID_HANDLE_VALUE) {
        printf("SetupDiGetClassDevs failed!\n");
        return NULL;
    }

    // Enumerate all of the devices in that set.

    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
    DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    bResult = SetupDiEnumDeviceInterfaces(
        HardwareDeviceInfo,
        0,
        InterfaceGuid,
        0,
        &DeviceInterfaceData
    );

    if( !bResult )
    {
        printf("SetupDiEnumDeviceInterfaces failed, %s\n", TranslateLastError());
        SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
        return NULL;
    }

    // Get detailed information about the first device in that set.

    SetupDiGetDeviceInterfaceDetail(
        HardwareDeviceInfo,
        &DeviceInterfaceData,
        NULL,
        0,
        &RequiredLength,
        NULL
    );

    auto_ptr<SP_DEVICE_INTERFACE_DETAIL_DATA> DeviceInterfaceDetailData (
        (PSP_DEVICE_INTERFACE_DETAIL_DATA) new char[RequiredLength]
    );

    DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    Length = RequiredLength;

    bResult = SetupDiGetDeviceInterfaceDetail(
        HardwareDeviceInfo,
        &DeviceInterfaceData,
        DeviceInterfaceDetailData.get(),
        Length,
        &RequiredLength,
        NULL
    );

    if( !bResult ) 
    {
        printf(
            "SetupDiGetDeviceInterfaceDetail failed. Error: %s\n", 
            TranslateLastError()
        );

        SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);       
        return NULL;
    }

    // Return the device's symbolic link name.

    return _tcstrdup(DeviceInterfaceDetailData->DevicePath);
}
*/
PTCHAR
GetDevicePath(IN LPCGUID InterfaceGuid)
{
	HDEVINFO HardwareDeviceInfo;
	ULONG Length, RequiredLength = 0;
	BOOL bResult;

	// Fetch the set of all devices that expose the device interface
	// given to us.

	HardwareDeviceInfo = SetupDiGetClassDevs(
		InterfaceGuid,
		NULL,
		NULL,
		(DIGCF_PRESENT | DIGCF_DEVICEINTERFACE)
		);

	if (HardwareDeviceInfo == INVALID_HANDLE_VALUE) {
		MessageBox(0, L"SetupDiGetClassDevs failed!", L"Error", MB_OK);
		return NULL;
	}

	// Enumerate all of the devices in that set.

	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	bResult = SetupDiEnumDeviceInterfaces(
		HardwareDeviceInfo,
		0,
		InterfaceGuid,
		0,
		&DeviceInterfaceData
		);

	if (!bResult)
	{
		// This is probably OK, it's just that there are none.
		OutputDebugString(TranslateLastError());
		OutputDebugString(L"<-- SetupDiEnumDeviceInterfaces\n");
		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		return NULL;
	}

	// Get detailed information about the first device in that set.

	SetupDiGetDeviceInterfaceDetail(
		HardwareDeviceInfo,
		&DeviceInterfaceData,
		NULL,
		0,
		&RequiredLength,
		NULL
		);

	auto_ptr<SP_DEVICE_INTERFACE_DETAIL_DATA> DeviceInterfaceDetailData(
		(PSP_DEVICE_INTERFACE_DETAIL_DATA) new char[RequiredLength]
		);

	DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

	Length = RequiredLength;

	bResult = SetupDiGetDeviceInterfaceDetail(
		HardwareDeviceInfo,
		&DeviceInterfaceData,
		DeviceInterfaceDetailData.get(),
		Length,
		&RequiredLength,
		NULL
		);

	if (!bResult)
	{
		MessageBox(0,
			TranslateLastError(),
			L"SetupDiGetDeviceInterfaceDetail",
			MB_OK
			);

		SetupDiDestroyDeviceInfoList(HardwareDeviceInfo);
		return NULL;
	}

	// Return the device's symbolic link name.

	return _tcsdup(DeviceInterfaceDetailData->DevicePath);
}
