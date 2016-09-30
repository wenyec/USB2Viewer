#pragma once
#define KS_NO_CREATE_FUNCTIONS
#include "vidiface.h"
#include "vidks.h"

// We can use either the ATL CComPtr or the built-in _com_ptr_t.
// Default is CComPtr; define COMPTR to use _com_ptr_t.

#ifdef COMPTR
#include <comdef.h>
#endif /* COMPTR */

#define	ERROR_VIDUSB2_REMOVED					0x80070001

#ifdef COMPTR
_COM_SMARTPTR_TYPEDEF(IBaseFilter, __uuidof(IBaseFilter));
_COM_SMARTPTR_TYPEDEF(IVideology20K1XX, __uuidof(IVideology20K1XX));
_COM_SMARTPTR_TYPEDEF(IVideologyCommon, __uuidof(IVideologyCommon));
_COM_SMARTPTR_TYPEDEF(IVideologyCMOS, __uuidof(IVideologyCMOS));
_COM_SMARTPTR_TYPEDEF(IVideology24C13, __uuidof(IVideology24C13));
_COM_SMARTPTR_TYPEDEF(IVideology24C13PanZoom, __uuidof(IVideology24C13PanZoom));
_COM_SMARTPTR_TYPEDEF(IVideology60V002, __uuidof(IVideology60V002));
#endif /* COMPTR */

enum {
    CAMID_D14X_MR_NTSC,     // mono
    CAMID_D14X_MR_PAL,
    CAMID_D14X_HR_NTSC,
    CAMID_D14X_HR_PAL,

    CAMID_D15X_MR_NTSC,     // color
    CAMID_D15X_MR_PAL,
    CAMID_D15X_HR_NTSC,
    CAMID_D15X_HR_PAL,

    CAMID_20K45_NTSC,
    CAMID_21K45_PAL,

    CAMID_SCHICKUSB,
    CAMID_SCHICKUSB_PAL,    // does not exist

    CAMID_24B13X,           // 1.3MP CMOS Mono
    CAMID_NULL1,
    CAMID_24C13X,           // 1.3MP CMOS Color
    CAMID_NULL2,

    CAMID_20C205 = 0x0052,
    CAMID_21C205,
    CAMID_22C205,
    CAMID_23C705,

    CAMID_20B45 = 0x0072,
    CAMID_21B45,

    CAMID_60V002N = 0x0142,
    CAMID_60V002P,

    CAMID_22C215P = 0x0452,
    CAMID_23C215P,
    CAMID_20C115 = 0x1442,
    CAMID_21C115,
    CAMID_20C215 = 0x1452,
    CAMID_21C215,
    CAMID_22C215,

    CAMID_GENERICN = 0x5332,
    CAMID_GENERICP = 0x6261,

    CAMID_UNKNOWN = 999,
};

#define IsTweety(x) ((x)<= CAMID_SCHICKUSB_PAL)
#define IsColor(x)  ((x)>= CAMID_D15X_MR_NTSC)
#define IsNTSC(x)   (((x)&1)==0)
#define IsK45(x)    (((x)&~1) == CAMID_20K45_NTSC)


#define D14_WBM             0x00000000
#define D14_RESET           0x00000004
#define D14_MIRROR          0x00000005
#define D14_SHUTTERMODE     0x00000006
#define D14_GAIN            0x00000007
#define D14_BLCWINSIZE      0x00000008
#define D14_BLCWINPOS       0x00000009
#define D14_NONINTERLACED   0x0000000a
#define D14_EDGEENHANCE     0x0000000b
#define D14_BLCWEIGH        0x0000000c
#define D14_RGAIN           0x0000000d
#define D14_BGAIN           0x0000000e
#define D14_HUE             0x0000000f

#define D14_VALIDMASK       0x0000fff1

class CVidUSB2Prop  
{
protected:
#ifndef COMPTR
    CComPtr<IBaseFilter>        m_pDevice;
    CComQIPtr<IVideology20K1XX> m_pCamera;
    CComQIPtr<IVideologyCommon> m_pI2C;
    CComQIPtr<IVideologyCMOS>   m_p24B13;
    CComQIPtr<IVideology24C13>  m_p24C13;
    CComQIPtr<IVideology60V002> m_p60V002;
#else /* COMPTR */
    IBaseFilterPtr      m_pDevice;
    IVideology20K1XXPtr m_pCamera;
    IVideologyCommonPtr m_pI2C;
    IVideologyCMOSPtr   m_p24B13;
    IVideology24C13Ptr  m_p24C13;
    IVideology60V002Ptr m_p60V002;
#endif /* COMPTR */

public:
    CVidUSB2Prop( IBaseFilter* pCapture )
        : m_pDevice( pCapture )
#ifndef COMPTR
        , m_pCamera( pCapture )
        , m_pI2C( pCapture )
        , m_p24B13( pCapture )
        , m_p24C13( pCapture )
        , m_p60V002( pCapture )
#endif /* not COMPTR */
    {
#ifdef COMPTR
        m_pDevice.QueryInterface( __uuidof(IVideology20K1XX), &m_pCamera );
        m_pDevice.QueryInterface( __uuidof(IVideologyCommon), &m_pI2C );
        m_pDevice.QueryInterface( __uuidof(IVideologyCMOS),   &m_p24B13 );
        m_pDevice.QueryInterface( __uuidof(IVideology24C13),  &m_p24C13 );
        m_pDevice.QueryInterface( __uuidof(IVideology60V002), &m_p60V002 );
#endif /* COMPTR */
    }

    ~CVidUSB2Prop()
	{}

    //
    //  These functions apply to all cameras.
    //


    // Start and stop port.

    bool vidInitPort(LPCTSTR szDeviceName=NULL)
    {
        return !!m_pI2C;
    }

    VOID vidDestroyPort()
    {
#ifndef COMPTR
        m_pCamera.Release();
        m_pI2C.Release();
        m_p24B13.Release();
        m_p24C13.Release();
        m_p60V002.Release();
#else /* COMPTR */
        m_pCamera = NULL;
        m_pI2C = NULL;
        m_p24B13 = NULL;
        m_p24C13 = NULL;
        m_p60V002 = NULL;
#endif /* COMPTR */
        delete this;
    }

    VOID vidSetPower( ULONG State )
    {
        m_pI2C->SetPower( State );
    }

    bool vidIsAvailable()
    {
        int iFree;
        m_pI2C->IsAvailable( &iFree );
        return iFree != 0;
    }

    bool vidIsSnapshotMode()
    {
        long Mode = 0;
        if( m_p24B13 )
            m_p24B13->GetSnapshotMode( &Mode );
        return Mode != 0;
    }

    //set and get camera features
    HRESULT vidGetFeature(ULONG ulKeyCode, ULONG *pulValue)
    {
        if( !m_pCamera )
            return E_NOTIMPL;

        switch( ulKeyCode )
        {
            case D14_SHUTTERMODE:
                m_pCamera->GetShutterSpeed( (eShutterSpeed*)pulValue );
                break;
            case D14_MIRROR:
                m_pCamera->GetMirror( (long*)pulValue );
                break;
            case D14_BLCWINSIZE:
                m_pCamera->GetBacklightCompSize( (eBlcSize*)pulValue );
                break;
            case D14_BLCWINPOS:
            {
                short h;
                short v;
                m_pCamera->GetBacklightCompPosition( &h, &v );
                *pulValue = (v << 3) | h;
                break;
            }
            case D14_BLCWEIGH:
                m_pCamera->GetBacklightCompWeight( (long*)pulValue );
                break;
            case D14_NONINTERLACED:
            {
                eInterlaceOptions ilo;
                m_pCamera->GetInterlace( &ilo );
                *pulValue = ilo;
                break;
            }
            case D14_EDGEENHANCE:
            {
                short h, v;
                m_pCamera->GetEdgeEnhancement( &h, &v );
                if( h & 0x8000 || v & 0x8000 )
                    *pulValue = 0xff;
                else
                    *pulValue = h;
                break;
            }
            case D14_WBM:
            {
                eWhiteBalanceMode wbm;
                m_pCamera->GetWhiteBalanceMode( &wbm );
                *pulValue = wbm;
                break;
            }
            case D14_RGAIN:
                *pulValue = 0;
                m_pCamera->GetWB1RedGain( (short*)pulValue );
                break;
            case D14_BGAIN:
                *pulValue = 0;
                m_pCamera->GetWB1BlueGain( (short*)pulValue );
                break;
            case D14_GAIN:
                // This returns 0..255, with bit 31 set for auto.
                m_pCamera->GetAGC( (long*)pulValue );
                break;
        }
        CStringA sz;
        sz.Format( __FUNCTION__ "(%d) => %04x\n",	ulKeyCode, *pulValue );
        OutputDebugStringA( sz );
        return S_OK;
    }

    HRESULT vidSetFeature(ULONG ulKeyCode, ULONG *pulValue)
    {
        CStringA sz;
        sz.Format( __FUNCTION__ "(%d) <= %04x\n",	ulKeyCode, *pulValue );
        OutputDebugStringA( sz );
        if( !m_pCamera )
            return E_NOTIMPL;
        switch( ulKeyCode )
        {
            case D14_RESET:
                m_pCamera->Reset();
                break;
            case D14_SHUTTERMODE:
                m_pCamera->SetShutterSpeed( (eShutterSpeed)*pulValue );
                break;
            case D14_MIRROR:
                m_pCamera->SetMirror( (long)*pulValue );
                break;
            case D14_BLCWINSIZE:
                m_pCamera->SetBacklightCompSize( (eBlcSize)*pulValue );
                break;
            case D14_BLCWINPOS:
            {
                short h = (short)(*pulValue & 7);
                short v = (short)(*pulValue >> 3);
                m_pCamera->SetBacklightCompPosition( h, v );
                break;
            }
            case D14_BLCWEIGH:
                m_pCamera->SetBacklightCompWeight( (long)*pulValue );
                break;
            case D14_NONINTERLACED:
                m_pCamera->SetInterlace( (eInterlaceOptions)*pulValue );
                break;
            case D14_EDGEENHANCE:
                if( *pulValue > 0xc0 )
                    m_pCamera->SetEdgeEnhancement( -0x7fff, -0x7fff );
                else
                    m_pCamera->SetEdgeEnhancement( (short)*pulValue, (short)*pulValue );
                break;
            case D14_WBM:
                m_pCamera->SetWhiteBalanceMode( (eWhiteBalanceMode)*pulValue );
                break;
            case D14_RGAIN:
                m_pCamera->SetWB1RedGain( (short)*pulValue );
                break;
            case D14_BGAIN:
                m_pCamera->SetWB1BlueGain( (short)*pulValue );
                break;
            case D14_GAIN:
                m_pCamera->SetAGC( *pulValue );
                break;
        }
        return S_OK;
    }

    //get all the camera features at a time
    HRESULT vidGetAllFeatures(ULONG *pulFeatures)
    { 
        for( int i = 0; i < 16; i++ )
            if( D14_VALIDMASK & (1 << i) )
                vidGetFeature( i, pulFeatures+i );
        return S_OK;
    }


    // Get camera ID.
    HRESULT vidGetCamID(ULONG *pulCamID)
    { 
        if( !m_pI2C )
        {
            *pulCamID = CAMID_UNKNOWN;
            return S_OK;
        }

        // TODO
        // Shouldn't all of this actually be in the driver, or at least
        // the proxy?

        int value;
        m_pI2C->GetModel( &value );
        switch( value ) {
            // Tweetys need extra processing to categorize.
            case 0x0042:
            case 0x0043:
            case 0x8117:
                break;

            case 0x0014:
                *pulCamID = CAMID_21B45;
                return S_OK;
            case 0x0015:
                *pulCamID = CAMID_20B45;
                return S_OK;
            case 0x0060:
                *pulCamID = CAMID_24B13X;
                return S_OK;
            case 0x0064:
            case 0x0065:
            case 0x0066:
                *pulCamID = CAMID_24C13X;
                return S_OK;

            // Many of the newer CAMID values equal the USB PID.
            case 0x0052:
            case 0x0053:
            case 0x0054:
            case 0x0055:
            case 0x0142:
            case 0x0143:
            case 0x1442:
            case 0x1443:
            case 0x1452:
            case 0x1453:
            case 0x1454:
            case 0x1455:
            case 0x5332:
            case 0x6261:
                *pulCamID = value;
                return S_OK;

            default:
                *pulCamID = CAMID_UNKNOWN;
                return S_OK;
        }

        ULONG Model = CAMID_D14X_MR_NTSC;

        vidGetEEPROM( 0xA0, (PULONG)&value );
        bool Is20K45 = (value == 0xff);

        vidGetEEPROM( 0x01, (PULONG)&value );

        if( Is20K45 )
        {
            // Use a different base model.  We only care about NTSC vs PAL.
            Model = CAMID_20K45_NTSC;
            value = (value & 0x40) | 0x80;
        }

        // Bump by four if color (20K15X).
        if( (value & 0x80) == 0 )
            Model += 4;

        // Bump by two if high-res.
        if( (value & 0x20) != 0 )
            Model += 2;

        // Bump by one if PAL.
        if( (value & 0x40) != 0 )
            Model ++;

        *pulCamID = Model;
        return S_OK;
    }

    // Take a snapshot right now.
    HRESULT vidTakeSnapshot()
    {
        return m_pI2C->Snapshot();
    }

    HRESULT vidFactoryReset()
    {
        if( !m_p24C13 )
            return E_NOTIMPL;
        return m_pI2C->WriteI2C( deviceCamera, 0x12, 0x5405 );
    }

    // Following functions vidGetCamID, vidSetDSP, vidGetDSP, vidSetEEPROM, vidGetEEPROM
    // and vidGetDSPFactoryDefault only apply to camera IDs from CAMID_D14X_MR_NTSC to
    // CAMID_D15X_HR_PAL.

    HRESULT vidGetEEPROM(ULONG ulAddress, ULONG *pulValue, ULONG count = 1)
    { 
        WORD Data = 0;
        m_pI2C->ReadI2C( deviceEepromPage1, (BYTE)ulAddress, &Data );
        *pulValue = Data;
        return S_OK; 
    }

	HRESULT vidWriteI2C(BYTE jDevice, BYTE jAddress, unsigned short jValue)
    {
        CStringA sz;
        sz.Format( __FUNCTION__ "Write(%02x,%02x,%02x)\n", jDevice, jAddress, jValue );
        OutputDebugStringA( sz );
        return m_pI2C->WriteI2C( jDevice, jAddress, jValue );
    }

	HRESULT vidReadI2C(BYTE jDevice, BYTE jAddress, unsigned short *pjValue)
	{
		CStringA sz;
		sz.Format(__FUNCTION__ "Write(%02x,%02x,%02x)\n", jDevice, jAddress, *pjValue);
		OutputDebugStringA(sz);
		return m_pI2C->ReadI2C(jDevice, jAddress, pjValue);
	}

};
