//------------------------------------------------------------------------------
// File: RotateFilter.h
//
// Desc: Transform filter to apply brightness, contrast, and gamma correction
//       to YUV video images.
//
// Tim Roberts
// Copyright (c) 2015, Videology Imaging.  All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include <vector>

// {0B8FB3BF-F66B-403A-BD8A-5DD902C6851E}
DEFINE_GUID(CLSID_RotateFilter,
0xb8fb3bf, 0xf66b, 0x403a, 0xbd, 0x8a, 0x5d, 0xd9, 0x2, 0xc6, 0x85, 0x1e);
DEFINE_GUID(IID_Rotater,
	0x490748ca, 0x116d, 0x490c, 0xae, 0x43, 0x74, 0xab, 0x42, 0x37, 0x62, 0x65);
enum {
    rotate0 = 0,
    rotate90,
    rotate180,
    rotate270,
    rotateFlip,
    rotateMirror
};


interface
    __declspec(uuid("490748CA-116D-490C-AE43-74AB42376265"))
    __declspec(novtable)
IVideoRotation : IUnknown
{
public:
    STDMETHOD(SetRotation)(int Amount) PURE;
    STDMETHOD_(int,GetRotation)() PURE;
};

