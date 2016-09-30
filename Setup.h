
#pragma once

// This has to match the GUID in our INF file.

DEFINE_GUID( GUID_V24ZFLASH, 
  0x5ef9dda0, 0x1cd4, 0x4cd2, 0x92, 0x13, 0x8e, 0x1d, 0x4d, 0x74, 0xb4, 0x9f );


// Set bRequest = FLASH_TRIGGER
// Set wValue = 0 or 1

enum FWCommands
{
    REQ_FLASH   = 0x01
};


PTCHAR GetDevicePath(IN  LPCGUID InterfaceGuid);
