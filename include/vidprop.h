/// \file vidprop.h
/// \brief Definitions to support the COM interface for our ksproxy plugin.
/// \author Tim N Roberts, Providenza & Boekelheide, Inc.
/// &copy; 2007, Videology, Inc.

#pragma once

// Note that this file is included by the IDL compiler.  As such, it
// must be C compatible.  That's why we use "typedef enum { } x;
// instead of enum x { };

typedef enum {
    ilProgressive       = 0,
    ilBob               = 1,
    ilWeave             = 2,
    ilDropEven          = 3,
    ilDropOdd           = 4
} eInterlaceOptions;

// One H and one V are or-ed together.  8x8 is not valid.

typedef enum {
    blc1H = 0x00,
    blc2H = 0x04,
    blc4H = 0x08,
    blc8H = 0x0c,
    blc1V = 0x00,
    blc2V = 0x01,
    blc4V = 0x02,
    blc8V = 0x03,
} eBlcSize;

typedef enum {
    ss1x        = 0,           // 50/60
    ss2x        = 1,           // 100/120
    ss250       = 2,
    ss500       = 3,
    ss1000      = 4,
    ss2000      = 5,
    ss5000      = 6,
    ss10000     = 7,
    ss20000     = 8,
    ss50000     = 9,
    ss100000    = 10,
    ssx_2       = 11,          // 25/30
    ssx_4       = 12,          // 12.5/15
    ssx_8       = 13,          // 6.25/7.5
    ssAuto1     = 14,          // 50/60 to max shutter in 5
    ssAuto2     = 15,          // 50/60 to 1/100,000
    ssMax       = 16
} eShutterSpeed;

typedef enum {
    ssc2         = 0,           // 1/2 sec
    ssc4         = 1,           // 1/4 sec
    ssc7_5       = 2,           // 2/15 sec
    ssc15        = 3,
    ssc20        = 4,
    ssc30        = 5,
    ssc50        = 6,
    ssc60        = 7,
    ssc100       = 8,
    ssc120       = 9,
    ssc200       = 10,
    ssc250       = 11,
    ssc500       = 12,
    ssc750       = 13,
    ssc1000      = 14,
    ssc2000      = 15,
    ssc3000      = 16,
    ssc4000      = 17,
    ssc5000      = 18,
    sscMax       = 19
} eShutterSpeedCMOS;

typedef enum {
    ssdx_0_5    = 0,            // 100/120
    ssdx_1      = 1,            // 50/60
    ssdx_2      = 2,            // 25/30
    ssdx_4      = 3,            // 12.5/15
    ssdAuto     = 4,
    ssdMax      = 5,
} eShutterSpeed24C13;

typedef enum {
    wbAuto        = 0,
    wbIndoor      = 1,
    wbFluorescent = 2,
    wbOutdoor     = 3,
    wbPush2White  = 7
} eWhiteBalanceMode;

typedef enum {
    wbaManual     = 0,
    wbaAuto1      = 1,
    wbaAuto2      = 2,
    wbaFreezeLock = 3,
    wbaFreezeSeek = 7,
} eWhiteBalance24C13;

typedef enum {
    deviceCamera,
    deviceSensor,
    deviceMicro = 0x40,
    deviceDSP0 = 0x80,
    deviceDSP7 = 0x87,
    deviceEepromPage1 = 0xa0,
    deviceEepromPage2 = 0xa2,
    deviceEepromPage3 = 0xa4,
    deviceEepromPage4 = 0xa6
} eDeviceNames;

enum OSD_20C205 {
    OSD_START = 0,
    OSD_ENTER = 1,
    OSD_LEFT = 2,
    OSD_RIGHT = 3,
    OSD_UP = 4,
    OSD_DOWN = 5
};
