/// \file vidks.h
/// \brief Definitions for the public properties offered by our capture driver.
/// \author Tim N Roberts, Providenza & Boekelheide, Inc.
/// &copy; 2007, Videology, Inc.

#pragma once

#pragma warning( push )
#pragma warning( disable : 4201 )
#include <ks.h>
#pragma warning( pop )
#include "vidprop.h"


struct I2C_DATA {
    unsigned char SubDevice;
    unsigned short Register;
    unsigned short Value;
};

// 0xffff means "off".

struct EDGE_ENHANCEMENT {
    short Horizontal;
    short Vertical;
};

// Our property set identifiers.


#define STATIC_KSPROPERTYSET_VideologyTweety \
    0x926ddb16, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb16-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_VideologyTweety );
#define KSPROPERTYSET_VideologyTweety \
        DEFINE_GUIDNAMED( KSPROPERTYSET_VideologyTweety )

#define STATIC_KSPROPERTYSET_VideologyCommon \
    0x926ddb17, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb17-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_VideologyCommon );
#define KSPROPERTYSET_VideologyCommon \
        DEFINE_GUIDNAMED( KSPROPERTYSET_VideologyCommon )

#define STATIC_KSMETHODSET_VideologyMethods \
    0x926ddb18, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb18-3c8e-476c-9068-eb4555a99231", KSMETHODSET_VideologyMethods );
#define KSMETHODSET_VideologyMethods \
        DEFINE_GUIDNAMED( KSMETHODSET_VideologyMethods )

#define STATIC_KSPROPERTYSET_VideologyCMOS \
    0x926ddb19, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb19-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_VideologyCMOS );
#define KSPROPERTYSET_VideologyCMOS \
        DEFINE_GUIDNAMED( KSPROPERTYSET_VideologyCMOS )

#define STATIC_KSPROPERTYSET_Videology24C13 \
    0x926ddb1a, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1a-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology24C13 );
#define KSPROPERTYSET_Videology24C13 \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology24C13 )

#define STATIC_KSPROPERTYSET_Videology24C13PanZoom \
    0x926ddb1b, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1b-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology24C13PanZoom );
#define KSPROPERTYSET_Videology24C13PanZoom \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology24C13PanZoom )

#define STATIC_KSPROPERTYSET_Videology60V002 \
    0x926ddb1c, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1c-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology60V002 );
#define KSPROPERTYSET_Videology60V002 \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology60V002 )

#define STATIC_KSPROPERTYSET_Videology21B45 \
    0x926ddb1d, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1d-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology21B45 );
#define KSPROPERTYSET_Videology21B45 \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology21B45 )

#define STATIC_KSPROPERTYSET_Videology20C205 \
    0x926ddb1e, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1e-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology20C205 );
#define KSPROPERTYSET_Videology20C205 \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology20C205 )

#define STATIC_KSPROPERTYSET_Videology2xC215 \
    0x926ddb1f, 0x3c8e, 0x476c, 0x90, 0x68, 0xeb, 0x45, 0x55, 0xa9, 0x92, 0x31
DEFINE_GUIDSTRUCT( "926ddb1f-3c8e-476c-9068-eb4555a99231", KSPROPERTYSET_Videology2xC215 );
#define KSPROPERTYSET_Videology2xC215 \
        DEFINE_GUIDNAMED( KSPROPERTYSET_Videology2xC215 )


// The list of properties and methods within our property sets.

typedef enum
{
    KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING,

    KSPROPERTY_VIDEOLOGYCMOS_SHUTTERSPEED = 20,
    KSPROPERTY_VIDEOLOGYCMOS_SNAPSHOTMODE,

    KSPROPERTY_VIDEOLOGY24C13_WHAT = 30,

// The *_I2C property accepts a list of I2C_DATA structures for both
// GET and SET.

    KSPROPERTY_VIDEOLOGYCOMMON_I2C = 40,
    KSPROPERTY_VIDEOLOGYCOMMON_MODEL,
    KSPROPERTY_VIDEOLOGYCOMMON_ALTSETTING,
    KSPROPERTY_VIDEOLOGYCOMMON_AVAILABLE,
    KSPROPERTY_VIDEOLOGYCOMMON_SNAPSHOT,
    KSPROPERTY_VIDEOLOGYCOMMON_EEPROM,

    KSMETHOD_VIDEOLOGYMETHODS_TAKESNAPSHOT = 60,
    KSMETHOD_VIDEOLOGYMETHODS_FIRMWARE,
    KSMETHOD_VIDEOLOGYMETHODS_SETPOWER,

    KSPROPERTY_VIDEOLOGY60V002_WHAT = 70,

    KSPROPERTY_VIDEOLOGY20C205_COMMAND = 80

} KSPROPERTY_VIDEOLOGY;

#define KSPROPERTY_VIDEOLOGY60V002_INTERLACING KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING
#define KSPROPERTY_VIDEOLOGY21B45_INTERLACING KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING
#define KSPROPERTY_VIDEOLOGY21C205_INTERLACING KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING
#define KSPROPERTY_VIDEOLOGY2XC215_INTERLACING KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING


// Property item declarations for our properties.

#define DEFINE_KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGY20K1XX_INTERLACING,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )


#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_SNAPSHOT( GetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_SNAPSHOT,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        NULL,\
        NULL, 0, NULL, NULL, 0 )


#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_I2C( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_I2C,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( I2C_DATA ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_MODEL( GetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_MODEL,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        NULL,\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_AVAILABLE( GetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_AVAILABLE,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        NULL,\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_ALTSETTING( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_ALTSETTING,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGYCOMMON_EEPROM( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCOMMON_EEPROM,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( USHORT ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )


#define DEFINE_KSMETHOD_VIDEOLOGYMETHODS_SETPOWER( Handler )\
    DEFINE_KSMETHOD_ITEM(\
        KSMETHOD_VIDEOLOGYMETHODS_SETPOWER,\
        KSMETHOD_TYPE_READ,\
        (Handler),\
        sizeof( KSMETHOD ),\
        sizeof( ULONG ),\
        NULL )

#define DEFINE_KSMETHOD_VIDEOLOGYMETHODS_TAKESNAPSHOT( Handler )\
    DEFINE_KSMETHOD_ITEM(\
        KSMETHOD_VIDEOLOGYMETHODS_TAKESNAPSHOT,\
        KSMETHOD_TYPE_NONE,\
        (Handler),\
        sizeof( KSMETHOD ),\
        0,\
        NULL )

#define DEFINE_KSMETHOD_VIDEOLOGYMETHODS_FIRMWARE( Handler )\
    DEFINE_KSMETHOD_ITEM(\
        KSMETHOD_VIDEOLOGYMETHODS_FIRMWARE,\
        KSMETHOD_TYPE_NONE,\
        (Handler),\
        sizeof( KSMETHOD ),\
        0,\
        NULL )

#define DEFINE_KSPROPERTY_VIDEOLOGYCMOS_SNAPSHOTMODE( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCMOS_SNAPSHOTMODE,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGYCMOS_SHUTTERSPEED( GetHandler, SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGYCMOS_SHUTTERSPEED,\
        (GetHandler),\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )

#define DEFINE_KSPROPERTY_VIDEOLOGY20C205_COMMAND( SetHandler )\
    DEFINE_KSPROPERTY_ITEM(\
        KSPROPERTY_VIDEOLOGY20C205_COMMAND,\
        NULL,\
        sizeof( KSPROPERTY ),\
        sizeof( ULONG ),\
        (SetHandler),\
        NULL, 0, NULL, NULL, 0 )
