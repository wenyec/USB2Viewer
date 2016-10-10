

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 10 14:56:33 2016
 */
/* Compiler settings for vidiface.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __vidiface_h__
#define __vidiface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVideology20K1XX_FWD_DEFINED__
#define __IVideology20K1XX_FWD_DEFINED__
typedef interface IVideology20K1XX IVideology20K1XX;

#endif 	/* __IVideology20K1XX_FWD_DEFINED__ */


#ifndef __IVideologyCommon_FWD_DEFINED__
#define __IVideologyCommon_FWD_DEFINED__
typedef interface IVideologyCommon IVideologyCommon;

#endif 	/* __IVideologyCommon_FWD_DEFINED__ */


#ifndef __IVideologyCMOS_FWD_DEFINED__
#define __IVideologyCMOS_FWD_DEFINED__
typedef interface IVideologyCMOS IVideologyCMOS;

#endif 	/* __IVideologyCMOS_FWD_DEFINED__ */


#ifndef __IVideology24C13_FWD_DEFINED__
#define __IVideology24C13_FWD_DEFINED__
typedef interface IVideology24C13 IVideology24C13;

#endif 	/* __IVideology24C13_FWD_DEFINED__ */


#ifndef __IVideology24C13PanZoom_FWD_DEFINED__
#define __IVideology24C13PanZoom_FWD_DEFINED__
typedef interface IVideology24C13PanZoom IVideology24C13PanZoom;

#endif 	/* __IVideology24C13PanZoom_FWD_DEFINED__ */


#ifndef __IVideology60V002_FWD_DEFINED__
#define __IVideology60V002_FWD_DEFINED__
typedef interface IVideology60V002 IVideology60V002;

#endif 	/* __IVideology60V002_FWD_DEFINED__ */


#ifndef __IVideology21B45_FWD_DEFINED__
#define __IVideology21B45_FWD_DEFINED__
typedef interface IVideology21B45 IVideology21B45;

#endif 	/* __IVideology21B45_FWD_DEFINED__ */


#ifndef __IVideology20C205_FWD_DEFINED__
#define __IVideology20C205_FWD_DEFINED__
typedef interface IVideology20C205 IVideology20C205;

#endif 	/* __IVideology20C205_FWD_DEFINED__ */


#ifndef __IVideology2xC215_FWD_DEFINED__
#define __IVideology2xC215_FWD_DEFINED__
typedef interface IVideology2xC215 IVideology2xC215;

#endif 	/* __IVideology2xC215_FWD_DEFINED__ */


#ifndef __Videology20K1XXPage_FWD_DEFINED__
#define __Videology20K1XXPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology20K1XXPage Videology20K1XXPage;
#else
typedef struct Videology20K1XXPage Videology20K1XXPage;
#endif /* __cplusplus */

#endif 	/* __Videology20K1XXPage_FWD_DEFINED__ */


#ifndef __VideologyCommonPage_FWD_DEFINED__
#define __VideologyCommonPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideologyCommonPage VideologyCommonPage;
#else
typedef struct VideologyCommonPage VideologyCommonPage;
#endif /* __cplusplus */

#endif 	/* __VideologyCommonPage_FWD_DEFINED__ */


#ifndef __Videology24B13Page_FWD_DEFINED__
#define __Videology24B13Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology24B13Page Videology24B13Page;
#else
typedef struct Videology24B13Page Videology24B13Page;
#endif /* __cplusplus */

#endif 	/* __Videology24B13Page_FWD_DEFINED__ */


#ifndef __Videology24C13Page_FWD_DEFINED__
#define __Videology24C13Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology24C13Page Videology24C13Page;
#else
typedef struct Videology24C13Page Videology24C13Page;
#endif /* __cplusplus */

#endif 	/* __Videology24C13Page_FWD_DEFINED__ */


#ifndef __Videology24C13PanPage_FWD_DEFINED__
#define __Videology24C13PanPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology24C13PanPage Videology24C13PanPage;
#else
typedef struct Videology24C13PanPage Videology24C13PanPage;
#endif /* __cplusplus */

#endif 	/* __Videology24C13PanPage_FWD_DEFINED__ */


#ifndef __Videology60V002Page_FWD_DEFINED__
#define __Videology60V002Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology60V002Page Videology60V002Page;
#else
typedef struct Videology60V002Page Videology60V002Page;
#endif /* __cplusplus */

#endif 	/* __Videology60V002Page_FWD_DEFINED__ */


#ifndef __Videology21B45Page_FWD_DEFINED__
#define __Videology21B45Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology21B45Page Videology21B45Page;
#else
typedef struct Videology21B45Page Videology21B45Page;
#endif /* __cplusplus */

#endif 	/* __Videology21B45Page_FWD_DEFINED__ */


#ifndef __Videology20C205Page_FWD_DEFINED__
#define __Videology20C205Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology20C205Page Videology20C205Page;
#else
typedef struct Videology20C205Page Videology20C205Page;
#endif /* __cplusplus */

#endif 	/* __Videology20C205Page_FWD_DEFINED__ */


#ifndef __Videology2xC215Page_FWD_DEFINED__
#define __Videology2xC215Page_FWD_DEFINED__

#ifdef __cplusplus
typedef class Videology2xC215Page Videology2xC215Page;
#else
typedef struct Videology2xC215Page Videology2xC215Page;
#endif /* __cplusplus */

#endif 	/* __Videology2xC215Page_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"
#include "vidprop.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __VideologyInterface_LIBRARY_DEFINED__
#define __VideologyInterface_LIBRARY_DEFINED__

/* library VideologyInterface */
/* [control][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VideologyInterface;

#ifndef __IVideology20K1XX_INTERFACE_DEFINED__
#define __IVideology20K1XX_INTERFACE_DEFINED__

/* interface IVideology20K1XX */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology20K1XX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb16-3c8e-476c-9068-eb4555a99231")
    IVideology20K1XX : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInterlace( 
            /* [retval][out] */ eInterlaceOptions *plInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterlace( 
            /* [in] */ eInterlaceOptions lInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMirror( 
            /* [retval][out] */ long *plMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMirror( 
            /* [in] */ long lMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSnapshotState( 
            /* [retval][out] */ long *plButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompSize( 
            /* [retval][out] */ eBlcSize *plBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompSize( 
            /* [in] */ eBlcSize lBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompPosition( 
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompPosition( 
            /* [in] */ short wHoriz,
            /* [in] */ short wVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompWeight( 
            /* [retval][out] */ long *plBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompWeight( 
            /* [in] */ long lBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAGC( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAGC( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEdgeEnhancement( 
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEdgeEnhancement( 
            /* [in] */ short pwHoriz,
            /* [in] */ short pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShutterSpeed( 
            /* [retval][out] */ eShutterSpeed *plShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShutterSpeed( 
            /* [in] */ eShutterSpeed lShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWhiteBalanceMode( 
            /* [retval][out] */ eWhiteBalanceMode *plMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWhiteBalanceMode( 
            /* [in] */ eWhiteBalanceMode lMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWB1RedGain( 
            /* [retval][out] */ short *pwGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWB1RedGain( 
            /* [in] */ short wGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWB1BlueGain( 
            /* [retval][out] */ short *pwGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWB1BlueGain( 
            /* [in] */ short wGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSnapshotMode( 
            /* [retval][out] */ long *lPulse) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSnapshotMode( 
            /* [in] */ long lPulse) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology20K1XXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology20K1XX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology20K1XX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology20K1XX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInterlace )( 
            IVideology20K1XX * This,
            /* [retval][out] */ eInterlaceOptions *plInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *SetInterlace )( 
            IVideology20K1XX * This,
            /* [in] */ eInterlaceOptions lInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *GetMirror )( 
            IVideology20K1XX * This,
            /* [retval][out] */ long *plMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *SetMirror )( 
            IVideology20K1XX * This,
            /* [in] */ long lMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *GetSnapshotState )( 
            IVideology20K1XX * This,
            /* [retval][out] */ long *plButton);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompSize )( 
            IVideology20K1XX * This,
            /* [retval][out] */ eBlcSize *plBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompSize )( 
            IVideology20K1XX * This,
            /* [in] */ eBlcSize lBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompPosition )( 
            IVideology20K1XX * This,
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompPosition )( 
            IVideology20K1XX * This,
            /* [in] */ short wHoriz,
            /* [in] */ short wVert);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompWeight )( 
            IVideology20K1XX * This,
            /* [retval][out] */ long *plBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompWeight )( 
            IVideology20K1XX * This,
            /* [in] */ long lBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetAGC )( 
            IVideology20K1XX * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetAGC )( 
            IVideology20K1XX * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetEdgeEnhancement )( 
            IVideology20K1XX * This,
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *SetEdgeEnhancement )( 
            IVideology20K1XX * This,
            /* [in] */ short pwHoriz,
            /* [in] */ short pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *GetShutterSpeed )( 
            IVideology20K1XX * This,
            /* [retval][out] */ eShutterSpeed *plShutter);
        
        HRESULT ( STDMETHODCALLTYPE *SetShutterSpeed )( 
            IVideology20K1XX * This,
            /* [in] */ eShutterSpeed lShutter);
        
        HRESULT ( STDMETHODCALLTYPE *GetWhiteBalanceMode )( 
            IVideology20K1XX * This,
            /* [retval][out] */ eWhiteBalanceMode *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetWhiteBalanceMode )( 
            IVideology20K1XX * This,
            /* [in] */ eWhiteBalanceMode lMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetWB1RedGain )( 
            IVideology20K1XX * This,
            /* [retval][out] */ short *pwGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetWB1RedGain )( 
            IVideology20K1XX * This,
            /* [in] */ short wGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetWB1BlueGain )( 
            IVideology20K1XX * This,
            /* [retval][out] */ short *pwGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetWB1BlueGain )( 
            IVideology20K1XX * This,
            /* [in] */ short wGain);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IVideology20K1XX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSnapshotMode )( 
            IVideology20K1XX * This,
            /* [retval][out] */ long *lPulse);
        
        HRESULT ( STDMETHODCALLTYPE *SetSnapshotMode )( 
            IVideology20K1XX * This,
            /* [in] */ long lPulse);
        
        END_INTERFACE
    } IVideology20K1XXVtbl;

    interface IVideology20K1XX
    {
        CONST_VTBL struct IVideology20K1XXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology20K1XX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology20K1XX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology20K1XX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology20K1XX_GetInterlace(This,plInterlace)	\
    ( (This)->lpVtbl -> GetInterlace(This,plInterlace) ) 

#define IVideology20K1XX_SetInterlace(This,lInterlace)	\
    ( (This)->lpVtbl -> SetInterlace(This,lInterlace) ) 

#define IVideology20K1XX_GetMirror(This,plMirroring)	\
    ( (This)->lpVtbl -> GetMirror(This,plMirroring) ) 

#define IVideology20K1XX_SetMirror(This,lMirroring)	\
    ( (This)->lpVtbl -> SetMirror(This,lMirroring) ) 

#define IVideology20K1XX_GetSnapshotState(This,plButton)	\
    ( (This)->lpVtbl -> GetSnapshotState(This,plButton) ) 

#define IVideology20K1XX_GetBacklightCompSize(This,plBlcSize)	\
    ( (This)->lpVtbl -> GetBacklightCompSize(This,plBlcSize) ) 

#define IVideology20K1XX_SetBacklightCompSize(This,lBlcSize)	\
    ( (This)->lpVtbl -> SetBacklightCompSize(This,lBlcSize) ) 

#define IVideology20K1XX_GetBacklightCompPosition(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> GetBacklightCompPosition(This,pwHoriz,pwVert) ) 

#define IVideology20K1XX_SetBacklightCompPosition(This,wHoriz,wVert)	\
    ( (This)->lpVtbl -> SetBacklightCompPosition(This,wHoriz,wVert) ) 

#define IVideology20K1XX_GetBacklightCompWeight(This,plBlcWeight)	\
    ( (This)->lpVtbl -> GetBacklightCompWeight(This,plBlcWeight) ) 

#define IVideology20K1XX_SetBacklightCompWeight(This,lBlcWeight)	\
    ( (This)->lpVtbl -> SetBacklightCompWeight(This,lBlcWeight) ) 

#define IVideology20K1XX_GetAGC(This,plGain)	\
    ( (This)->lpVtbl -> GetAGC(This,plGain) ) 

#define IVideology20K1XX_SetAGC(This,lGain)	\
    ( (This)->lpVtbl -> SetAGC(This,lGain) ) 

#define IVideology20K1XX_GetEdgeEnhancement(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> GetEdgeEnhancement(This,pwHoriz,pwVert) ) 

#define IVideology20K1XX_SetEdgeEnhancement(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> SetEdgeEnhancement(This,pwHoriz,pwVert) ) 

#define IVideology20K1XX_GetShutterSpeed(This,plShutter)	\
    ( (This)->lpVtbl -> GetShutterSpeed(This,plShutter) ) 

#define IVideology20K1XX_SetShutterSpeed(This,lShutter)	\
    ( (This)->lpVtbl -> SetShutterSpeed(This,lShutter) ) 

#define IVideology20K1XX_GetWhiteBalanceMode(This,plMode)	\
    ( (This)->lpVtbl -> GetWhiteBalanceMode(This,plMode) ) 

#define IVideology20K1XX_SetWhiteBalanceMode(This,lMode)	\
    ( (This)->lpVtbl -> SetWhiteBalanceMode(This,lMode) ) 

#define IVideology20K1XX_GetWB1RedGain(This,pwGain)	\
    ( (This)->lpVtbl -> GetWB1RedGain(This,pwGain) ) 

#define IVideology20K1XX_SetWB1RedGain(This,wGain)	\
    ( (This)->lpVtbl -> SetWB1RedGain(This,wGain) ) 

#define IVideology20K1XX_GetWB1BlueGain(This,pwGain)	\
    ( (This)->lpVtbl -> GetWB1BlueGain(This,pwGain) ) 

#define IVideology20K1XX_SetWB1BlueGain(This,wGain)	\
    ( (This)->lpVtbl -> SetWB1BlueGain(This,wGain) ) 

#define IVideology20K1XX_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IVideology20K1XX_GetSnapshotMode(This,lPulse)	\
    ( (This)->lpVtbl -> GetSnapshotMode(This,lPulse) ) 

#define IVideology20K1XX_SetSnapshotMode(This,lPulse)	\
    ( (This)->lpVtbl -> SetSnapshotMode(This,lPulse) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology20K1XX_INTERFACE_DEFINED__ */


#ifndef __IVideologyCommon_INTERFACE_DEFINED__
#define __IVideologyCommon_INTERFACE_DEFINED__

/* interface IVideologyCommon */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideologyCommon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb17-3c8e-476c-9068-eb4555a99231")
    IVideologyCommon : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadI2C( 
            /* [in] */ unsigned char SubDevice,
            /* [in] */ unsigned short Register,
            /* [retval][out] */ unsigned short *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteI2C( 
            /* [in] */ unsigned char SubDevice,
            /* [in] */ unsigned short Register,
            /* [in] */ unsigned short Data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetModel( 
            /* [retval][out] */ int *iModel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Snapshot( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPower( 
            /* [in] */ int iPower) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAltSetting( 
            /* [in] */ int *iSetting) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAltSetting( 
            /* [in] */ int iSetting) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsAvailable( 
            /* [retval][out] */ int *iAvailable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSnapshotState( 
            /* [retval][out] */ long *plButton) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadFx2EEPROM( 
            /* [in] */ unsigned short Address,
            /* [in] */ unsigned short Size,
            /* [retval][out] */ unsigned char *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteFx2EEPROM( 
            /* [in] */ unsigned short Address,
            /* [in] */ unsigned short Size,
            /* [retval][out] */ unsigned char *pData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideologyCommonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideologyCommon * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideologyCommon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideologyCommon * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReadI2C )( 
            IVideologyCommon * This,
            /* [in] */ unsigned char SubDevice,
            /* [in] */ unsigned short Register,
            /* [retval][out] */ unsigned short *pData);
        
        HRESULT ( STDMETHODCALLTYPE *WriteI2C )( 
            IVideologyCommon * This,
            /* [in] */ unsigned char SubDevice,
            /* [in] */ unsigned short Register,
            /* [in] */ unsigned short Data);
        
        HRESULT ( STDMETHODCALLTYPE *GetModel )( 
            IVideologyCommon * This,
            /* [retval][out] */ int *iModel);
        
        HRESULT ( STDMETHODCALLTYPE *Snapshot )( 
            IVideologyCommon * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetPower )( 
            IVideologyCommon * This,
            /* [in] */ int iPower);
        
        HRESULT ( STDMETHODCALLTYPE *GetAltSetting )( 
            IVideologyCommon * This,
            /* [in] */ int *iSetting);
        
        HRESULT ( STDMETHODCALLTYPE *SetAltSetting )( 
            IVideologyCommon * This,
            /* [in] */ int iSetting);
        
        HRESULT ( STDMETHODCALLTYPE *IsAvailable )( 
            IVideologyCommon * This,
            /* [retval][out] */ int *iAvailable);
        
        HRESULT ( STDMETHODCALLTYPE *GetSnapshotState )( 
            IVideologyCommon * This,
            /* [retval][out] */ long *plButton);
        
        HRESULT ( STDMETHODCALLTYPE *ReadFx2EEPROM )( 
            IVideologyCommon * This,
            /* [in] */ unsigned short Address,
            /* [in] */ unsigned short Size,
            /* [retval][out] */ unsigned char *pData);
        
        HRESULT ( STDMETHODCALLTYPE *WriteFx2EEPROM )( 
            IVideologyCommon * This,
            /* [in] */ unsigned short Address,
            /* [in] */ unsigned short Size,
            /* [retval][out] */ unsigned char *pData);
        
        END_INTERFACE
    } IVideologyCommonVtbl;

    interface IVideologyCommon
    {
        CONST_VTBL struct IVideologyCommonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideologyCommon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideologyCommon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideologyCommon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideologyCommon_ReadI2C(This,SubDevice,Register,pData)	\
    ( (This)->lpVtbl -> ReadI2C(This,SubDevice,Register,pData) ) 

#define IVideologyCommon_WriteI2C(This,SubDevice,Register,Data)	\
    ( (This)->lpVtbl -> WriteI2C(This,SubDevice,Register,Data) ) 

#define IVideologyCommon_GetModel(This,iModel)	\
    ( (This)->lpVtbl -> GetModel(This,iModel) ) 

#define IVideologyCommon_Snapshot(This)	\
    ( (This)->lpVtbl -> Snapshot(This) ) 

#define IVideologyCommon_SetPower(This,iPower)	\
    ( (This)->lpVtbl -> SetPower(This,iPower) ) 

#define IVideologyCommon_GetAltSetting(This,iSetting)	\
    ( (This)->lpVtbl -> GetAltSetting(This,iSetting) ) 

#define IVideologyCommon_SetAltSetting(This,iSetting)	\
    ( (This)->lpVtbl -> SetAltSetting(This,iSetting) ) 

#define IVideologyCommon_IsAvailable(This,iAvailable)	\
    ( (This)->lpVtbl -> IsAvailable(This,iAvailable) ) 

#define IVideologyCommon_GetSnapshotState(This,plButton)	\
    ( (This)->lpVtbl -> GetSnapshotState(This,plButton) ) 

#define IVideologyCommon_ReadFx2EEPROM(This,Address,Size,pData)	\
    ( (This)->lpVtbl -> ReadFx2EEPROM(This,Address,Size,pData) ) 

#define IVideologyCommon_WriteFx2EEPROM(This,Address,Size,pData)	\
    ( (This)->lpVtbl -> WriteFx2EEPROM(This,Address,Size,pData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideologyCommon_INTERFACE_DEFINED__ */


#ifndef __IVideologyCMOS_INTERFACE_DEFINED__
#define __IVideologyCMOS_INTERFACE_DEFINED__

/* interface IVideologyCMOS */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideologyCMOS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb19-3c8e-476c-9068-eb4555a99231")
    IVideologyCMOS : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAGC( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAGC( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMirror( 
            /* [retval][out] */ long *plMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMirror( 
            /* [in] */ long lMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlip( 
            /* [retval][out] */ long *plFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlip( 
            /* [in] */ long lFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShutterSpeed( 
            /* [retval][out] */ eShutterSpeedCMOS *plShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShutterSpeed( 
            /* [in] */ eShutterSpeedCMOS lShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSnapshotMode( 
            /* [retval][out] */ long *lOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSnapshotMode( 
            /* [in] */ long lOn) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideologyCMOSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideologyCMOS * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideologyCMOS * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideologyCMOS * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAGC )( 
            IVideologyCMOS * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetAGC )( 
            IVideologyCMOS * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetMirror )( 
            IVideologyCMOS * This,
            /* [retval][out] */ long *plMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *SetMirror )( 
            IVideologyCMOS * This,
            /* [in] */ long lMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlip )( 
            IVideologyCMOS * This,
            /* [retval][out] */ long *plFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlip )( 
            IVideologyCMOS * This,
            /* [in] */ long lFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *GetShutterSpeed )( 
            IVideologyCMOS * This,
            /* [retval][out] */ eShutterSpeedCMOS *plShutter);
        
        HRESULT ( STDMETHODCALLTYPE *SetShutterSpeed )( 
            IVideologyCMOS * This,
            /* [in] */ eShutterSpeedCMOS lShutter);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IVideologyCMOS * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSnapshotMode )( 
            IVideologyCMOS * This,
            /* [retval][out] */ long *lOn);
        
        HRESULT ( STDMETHODCALLTYPE *SetSnapshotMode )( 
            IVideologyCMOS * This,
            /* [in] */ long lOn);
        
        END_INTERFACE
    } IVideologyCMOSVtbl;

    interface IVideologyCMOS
    {
        CONST_VTBL struct IVideologyCMOSVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideologyCMOS_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideologyCMOS_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideologyCMOS_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideologyCMOS_GetAGC(This,plGain)	\
    ( (This)->lpVtbl -> GetAGC(This,plGain) ) 

#define IVideologyCMOS_SetAGC(This,lGain)	\
    ( (This)->lpVtbl -> SetAGC(This,lGain) ) 

#define IVideologyCMOS_GetMirror(This,plMirroring)	\
    ( (This)->lpVtbl -> GetMirror(This,plMirroring) ) 

#define IVideologyCMOS_SetMirror(This,lMirroring)	\
    ( (This)->lpVtbl -> SetMirror(This,lMirroring) ) 

#define IVideologyCMOS_GetFlip(This,plFlipping)	\
    ( (This)->lpVtbl -> GetFlip(This,plFlipping) ) 

#define IVideologyCMOS_SetFlip(This,lFlipping)	\
    ( (This)->lpVtbl -> SetFlip(This,lFlipping) ) 

#define IVideologyCMOS_GetShutterSpeed(This,plShutter)	\
    ( (This)->lpVtbl -> GetShutterSpeed(This,plShutter) ) 

#define IVideologyCMOS_SetShutterSpeed(This,lShutter)	\
    ( (This)->lpVtbl -> SetShutterSpeed(This,lShutter) ) 

#define IVideologyCMOS_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IVideologyCMOS_GetSnapshotMode(This,lOn)	\
    ( (This)->lpVtbl -> GetSnapshotMode(This,lOn) ) 

#define IVideologyCMOS_SetSnapshotMode(This,lOn)	\
    ( (This)->lpVtbl -> SetSnapshotMode(This,lOn) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideologyCMOS_INTERFACE_DEFINED__ */


#ifndef __IVideology24C13_INTERFACE_DEFINED__
#define __IVideology24C13_INTERFACE_DEFINED__

/* interface IVideology24C13 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology24C13;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1a-3c8e-476c-9068-eb4555a99231")
    IVideology24C13 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompSize( 
            /* [retval][out] */ eBlcSize *plBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompSize( 
            /* [in] */ eBlcSize lBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompPosition( 
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompPosition( 
            /* [in] */ short wHoriz,
            /* [in] */ short wVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompWeight( 
            /* [retval][out] */ long *plBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompWeight( 
            /* [in] */ long lBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAGC( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAGC( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEdgeEnhancement( 
            /* [retval][out] */ short *pwLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEdgeEnhancement( 
            /* [in] */ short pwLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShutterSpeed( 
            /* [retval][out] */ eShutterSpeed24C13 *plShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShutterSpeed( 
            /* [in] */ eShutterSpeed24C13 lShutter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWhiteBalanceMode( 
            /* [retval][out] */ eWhiteBalance24C13 *plMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWhiteBalanceMode( 
            /* [in] */ eWhiteBalance24C13 lMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWBGains( 
            /* [out] */ short *pwRed,
            /* [out] */ short *pwBlue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWBGains( 
            /* [in] */ short wRed,
            /* [in] */ short wBlue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPowerFreq( 
            /* [retval][out] */ short *pwFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPowerFreq( 
            /* [in] */ short wFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSaturation( 
            /* [retval][out] */ short *pwSat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSaturation( 
            /* [in] */ short wSat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMirror( 
            /* [retval][out] */ long *plMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMirror( 
            /* [in] */ long lMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlip( 
            /* [retval][out] */ long *plFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlip( 
            /* [in] */ long lFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSnapshotMode( 
            /* [retval][out] */ long *lOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSnapshotMode( 
            /* [in] */ long lOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoSaturation( 
            /* [retval][out] */ long *plSat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAutoSaturation( 
            /* [in] */ long lSat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGamma( 
            /* [retval][out] */ double *plGamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGamma( 
            /* [in] */ double lGamma) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlash( 
            /* [retval][out] */ long *lOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlash( 
            /* [in] */ long lOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBrightness( 
            /* [retval][out] */ long *plBrightness) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBrightness( 
            /* [in] */ long lBrightness) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology24C13Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology24C13 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology24C13 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology24C13 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompSize )( 
            IVideology24C13 * This,
            /* [retval][out] */ eBlcSize *plBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompSize )( 
            IVideology24C13 * This,
            /* [in] */ eBlcSize lBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompPosition )( 
            IVideology24C13 * This,
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompPosition )( 
            IVideology24C13 * This,
            /* [in] */ short wHoriz,
            /* [in] */ short wVert);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompWeight )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompWeight )( 
            IVideology24C13 * This,
            /* [in] */ long lBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetAGC )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetAGC )( 
            IVideology24C13 * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetEdgeEnhancement )( 
            IVideology24C13 * This,
            /* [retval][out] */ short *pwLevel);
        
        HRESULT ( STDMETHODCALLTYPE *SetEdgeEnhancement )( 
            IVideology24C13 * This,
            /* [in] */ short pwLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetShutterSpeed )( 
            IVideology24C13 * This,
            /* [retval][out] */ eShutterSpeed24C13 *plShutter);
        
        HRESULT ( STDMETHODCALLTYPE *SetShutterSpeed )( 
            IVideology24C13 * This,
            /* [in] */ eShutterSpeed24C13 lShutter);
        
        HRESULT ( STDMETHODCALLTYPE *GetWhiteBalanceMode )( 
            IVideology24C13 * This,
            /* [retval][out] */ eWhiteBalance24C13 *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetWhiteBalanceMode )( 
            IVideology24C13 * This,
            /* [in] */ eWhiteBalance24C13 lMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetWBGains )( 
            IVideology24C13 * This,
            /* [out] */ short *pwRed,
            /* [out] */ short *pwBlue);
        
        HRESULT ( STDMETHODCALLTYPE *SetWBGains )( 
            IVideology24C13 * This,
            /* [in] */ short wRed,
            /* [in] */ short wBlue);
        
        HRESULT ( STDMETHODCALLTYPE *GetPowerFreq )( 
            IVideology24C13 * This,
            /* [retval][out] */ short *pwFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetPowerFreq )( 
            IVideology24C13 * This,
            /* [in] */ short wFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSaturation )( 
            IVideology24C13 * This,
            /* [retval][out] */ short *pwSat);
        
        HRESULT ( STDMETHODCALLTYPE *SetSaturation )( 
            IVideology24C13 * This,
            /* [in] */ short wSat);
        
        HRESULT ( STDMETHODCALLTYPE *GetMirror )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *SetMirror )( 
            IVideology24C13 * This,
            /* [in] */ long lMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlip )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlip )( 
            IVideology24C13 * This,
            /* [in] */ long lFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IVideology24C13 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSnapshotMode )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *lOn);
        
        HRESULT ( STDMETHODCALLTYPE *SetSnapshotMode )( 
            IVideology24C13 * This,
            /* [in] */ long lOn);
        
        HRESULT ( STDMETHODCALLTYPE *GetAutoSaturation )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plSat);
        
        HRESULT ( STDMETHODCALLTYPE *SetAutoSaturation )( 
            IVideology24C13 * This,
            /* [in] */ long lSat);
        
        HRESULT ( STDMETHODCALLTYPE *GetGamma )( 
            IVideology24C13 * This,
            /* [retval][out] */ double *plGamma);
        
        HRESULT ( STDMETHODCALLTYPE *SetGamma )( 
            IVideology24C13 * This,
            /* [in] */ double lGamma);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlash )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *lOn);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlash )( 
            IVideology24C13 * This,
            /* [in] */ long lOn);
        
        HRESULT ( STDMETHODCALLTYPE *GetBrightness )( 
            IVideology24C13 * This,
            /* [retval][out] */ long *plBrightness);
        
        HRESULT ( STDMETHODCALLTYPE *SetBrightness )( 
            IVideology24C13 * This,
            /* [in] */ long lBrightness);
        
        END_INTERFACE
    } IVideology24C13Vtbl;

    interface IVideology24C13
    {
        CONST_VTBL struct IVideology24C13Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology24C13_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology24C13_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology24C13_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology24C13_GetBacklightCompSize(This,plBlcSize)	\
    ( (This)->lpVtbl -> GetBacklightCompSize(This,plBlcSize) ) 

#define IVideology24C13_SetBacklightCompSize(This,lBlcSize)	\
    ( (This)->lpVtbl -> SetBacklightCompSize(This,lBlcSize) ) 

#define IVideology24C13_GetBacklightCompPosition(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> GetBacklightCompPosition(This,pwHoriz,pwVert) ) 

#define IVideology24C13_SetBacklightCompPosition(This,wHoriz,wVert)	\
    ( (This)->lpVtbl -> SetBacklightCompPosition(This,wHoriz,wVert) ) 

#define IVideology24C13_GetBacklightCompWeight(This,plBlcWeight)	\
    ( (This)->lpVtbl -> GetBacklightCompWeight(This,plBlcWeight) ) 

#define IVideology24C13_SetBacklightCompWeight(This,lBlcWeight)	\
    ( (This)->lpVtbl -> SetBacklightCompWeight(This,lBlcWeight) ) 

#define IVideology24C13_GetAGC(This,plGain)	\
    ( (This)->lpVtbl -> GetAGC(This,plGain) ) 

#define IVideology24C13_SetAGC(This,lGain)	\
    ( (This)->lpVtbl -> SetAGC(This,lGain) ) 

#define IVideology24C13_GetEdgeEnhancement(This,pwLevel)	\
    ( (This)->lpVtbl -> GetEdgeEnhancement(This,pwLevel) ) 

#define IVideology24C13_SetEdgeEnhancement(This,pwLevel)	\
    ( (This)->lpVtbl -> SetEdgeEnhancement(This,pwLevel) ) 

#define IVideology24C13_GetShutterSpeed(This,plShutter)	\
    ( (This)->lpVtbl -> GetShutterSpeed(This,plShutter) ) 

#define IVideology24C13_SetShutterSpeed(This,lShutter)	\
    ( (This)->lpVtbl -> SetShutterSpeed(This,lShutter) ) 

#define IVideology24C13_GetWhiteBalanceMode(This,plMode)	\
    ( (This)->lpVtbl -> GetWhiteBalanceMode(This,plMode) ) 

#define IVideology24C13_SetWhiteBalanceMode(This,lMode)	\
    ( (This)->lpVtbl -> SetWhiteBalanceMode(This,lMode) ) 

#define IVideology24C13_GetWBGains(This,pwRed,pwBlue)	\
    ( (This)->lpVtbl -> GetWBGains(This,pwRed,pwBlue) ) 

#define IVideology24C13_SetWBGains(This,wRed,wBlue)	\
    ( (This)->lpVtbl -> SetWBGains(This,wRed,wBlue) ) 

#define IVideology24C13_GetPowerFreq(This,pwFreq)	\
    ( (This)->lpVtbl -> GetPowerFreq(This,pwFreq) ) 

#define IVideology24C13_SetPowerFreq(This,wFreq)	\
    ( (This)->lpVtbl -> SetPowerFreq(This,wFreq) ) 

#define IVideology24C13_GetSaturation(This,pwSat)	\
    ( (This)->lpVtbl -> GetSaturation(This,pwSat) ) 

#define IVideology24C13_SetSaturation(This,wSat)	\
    ( (This)->lpVtbl -> SetSaturation(This,wSat) ) 

#define IVideology24C13_GetMirror(This,plMirroring)	\
    ( (This)->lpVtbl -> GetMirror(This,plMirroring) ) 

#define IVideology24C13_SetMirror(This,lMirroring)	\
    ( (This)->lpVtbl -> SetMirror(This,lMirroring) ) 

#define IVideology24C13_GetFlip(This,plFlipping)	\
    ( (This)->lpVtbl -> GetFlip(This,plFlipping) ) 

#define IVideology24C13_SetFlip(This,lFlipping)	\
    ( (This)->lpVtbl -> SetFlip(This,lFlipping) ) 

#define IVideology24C13_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IVideology24C13_GetSnapshotMode(This,lOn)	\
    ( (This)->lpVtbl -> GetSnapshotMode(This,lOn) ) 

#define IVideology24C13_SetSnapshotMode(This,lOn)	\
    ( (This)->lpVtbl -> SetSnapshotMode(This,lOn) ) 

#define IVideology24C13_GetAutoSaturation(This,plSat)	\
    ( (This)->lpVtbl -> GetAutoSaturation(This,plSat) ) 

#define IVideology24C13_SetAutoSaturation(This,lSat)	\
    ( (This)->lpVtbl -> SetAutoSaturation(This,lSat) ) 

#define IVideology24C13_GetGamma(This,plGamma)	\
    ( (This)->lpVtbl -> GetGamma(This,plGamma) ) 

#define IVideology24C13_SetGamma(This,lGamma)	\
    ( (This)->lpVtbl -> SetGamma(This,lGamma) ) 

#define IVideology24C13_GetFlash(This,lOn)	\
    ( (This)->lpVtbl -> GetFlash(This,lOn) ) 

#define IVideology24C13_SetFlash(This,lOn)	\
    ( (This)->lpVtbl -> SetFlash(This,lOn) ) 

#define IVideology24C13_GetBrightness(This,plBrightness)	\
    ( (This)->lpVtbl -> GetBrightness(This,plBrightness) ) 

#define IVideology24C13_SetBrightness(This,lBrightness)	\
    ( (This)->lpVtbl -> SetBrightness(This,lBrightness) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology24C13_INTERFACE_DEFINED__ */


#ifndef __IVideology24C13PanZoom_INTERFACE_DEFINED__
#define __IVideology24C13PanZoom_INTERFACE_DEFINED__

/* interface IVideology24C13PanZoom */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology24C13PanZoom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1b-3c8e-476c-9068-eb4555a99231")
    IVideology24C13PanZoom : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetResolution( 
            /* [out] */ long *plWidth,
            /* [out] */ long *plHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPan( 
            /* [out] */ long *plPanX,
            /* [out] */ long *plPanY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPan( 
            /* [in] */ long lPanX,
            long plPanY) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology24C13PanZoomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology24C13PanZoom * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology24C13PanZoom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology24C13PanZoom * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetResolution )( 
            IVideology24C13PanZoom * This,
            /* [out] */ long *plWidth,
            /* [out] */ long *plHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetPan )( 
            IVideology24C13PanZoom * This,
            /* [out] */ long *plPanX,
            /* [out] */ long *plPanY);
        
        HRESULT ( STDMETHODCALLTYPE *SetPan )( 
            IVideology24C13PanZoom * This,
            /* [in] */ long lPanX,
            long plPanY);
        
        END_INTERFACE
    } IVideology24C13PanZoomVtbl;

    interface IVideology24C13PanZoom
    {
        CONST_VTBL struct IVideology24C13PanZoomVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology24C13PanZoom_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology24C13PanZoom_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology24C13PanZoom_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology24C13PanZoom_GetResolution(This,plWidth,plHeight)	\
    ( (This)->lpVtbl -> GetResolution(This,plWidth,plHeight) ) 

#define IVideology24C13PanZoom_GetPan(This,plPanX,plPanY)	\
    ( (This)->lpVtbl -> GetPan(This,plPanX,plPanY) ) 

#define IVideology24C13PanZoom_SetPan(This,lPanX,plPanY)	\
    ( (This)->lpVtbl -> SetPan(This,lPanX,plPanY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology24C13PanZoom_INTERFACE_DEFINED__ */


#ifndef __IVideology60V002_INTERFACE_DEFINED__
#define __IVideology60V002_INTERFACE_DEFINED__

/* interface IVideology60V002 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology60V002;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1c-3c8e-476c-9068-eb4555a99231")
    IVideology60V002 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetYGain( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetYGain( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCGain( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCGain( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSource( 
            /* [retval][out] */ long *plSource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSource( 
            /* [in] */ long lSource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [retval][out] */ long *plNtscPal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ long lNtscPal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInterlace( 
            /* [retval][out] */ eInterlaceOptions *plInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterlace( 
            /* [in] */ eInterlaceOptions lInterlace) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology60V002Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology60V002 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology60V002 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology60V002 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetYGain )( 
            IVideology60V002 * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetYGain )( 
            IVideology60V002 * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetCGain )( 
            IVideology60V002 * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetCGain )( 
            IVideology60V002 * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetSource )( 
            IVideology60V002 * This,
            /* [retval][out] */ long *plSource);
        
        HRESULT ( STDMETHODCALLTYPE *SetSource )( 
            IVideology60V002 * This,
            /* [in] */ long lSource);
        
        HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IVideology60V002 * This,
            /* [retval][out] */ long *plNtscPal);
        
        HRESULT ( STDMETHODCALLTYPE *SetFormat )( 
            IVideology60V002 * This,
            /* [in] */ long lNtscPal);
        
        HRESULT ( STDMETHODCALLTYPE *GetInterlace )( 
            IVideology60V002 * This,
            /* [retval][out] */ eInterlaceOptions *plInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *SetInterlace )( 
            IVideology60V002 * This,
            /* [in] */ eInterlaceOptions lInterlace);
        
        END_INTERFACE
    } IVideology60V002Vtbl;

    interface IVideology60V002
    {
        CONST_VTBL struct IVideology60V002Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology60V002_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology60V002_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology60V002_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology60V002_GetYGain(This,plGain)	\
    ( (This)->lpVtbl -> GetYGain(This,plGain) ) 

#define IVideology60V002_SetYGain(This,lGain)	\
    ( (This)->lpVtbl -> SetYGain(This,lGain) ) 

#define IVideology60V002_GetCGain(This,plGain)	\
    ( (This)->lpVtbl -> GetCGain(This,plGain) ) 

#define IVideology60V002_SetCGain(This,lGain)	\
    ( (This)->lpVtbl -> SetCGain(This,lGain) ) 

#define IVideology60V002_GetSource(This,plSource)	\
    ( (This)->lpVtbl -> GetSource(This,plSource) ) 

#define IVideology60V002_SetSource(This,lSource)	\
    ( (This)->lpVtbl -> SetSource(This,lSource) ) 

#define IVideology60V002_GetFormat(This,plNtscPal)	\
    ( (This)->lpVtbl -> GetFormat(This,plNtscPal) ) 

#define IVideology60V002_SetFormat(This,lNtscPal)	\
    ( (This)->lpVtbl -> SetFormat(This,lNtscPal) ) 

#define IVideology60V002_GetInterlace(This,plInterlace)	\
    ( (This)->lpVtbl -> GetInterlace(This,plInterlace) ) 

#define IVideology60V002_SetInterlace(This,lInterlace)	\
    ( (This)->lpVtbl -> SetInterlace(This,lInterlace) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology60V002_INTERFACE_DEFINED__ */


#ifndef __IVideology21B45_INTERFACE_DEFINED__
#define __IVideology21B45_INTERFACE_DEFINED__

/* interface IVideology21B45 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology21B45;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1d-3c8e-476c-9068-eb4555a99231")
    IVideology21B45 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInterlace( 
            /* [retval][out] */ eInterlaceOptions *plInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterlace( 
            /* [in] */ eInterlaceOptions lInterlace) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology21B45Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology21B45 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology21B45 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology21B45 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInterlace )( 
            IVideology21B45 * This,
            /* [retval][out] */ eInterlaceOptions *plInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *SetInterlace )( 
            IVideology21B45 * This,
            /* [in] */ eInterlaceOptions lInterlace);
        
        END_INTERFACE
    } IVideology21B45Vtbl;

    interface IVideology21B45
    {
        CONST_VTBL struct IVideology21B45Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology21B45_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology21B45_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology21B45_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology21B45_GetInterlace(This,plInterlace)	\
    ( (This)->lpVtbl -> GetInterlace(This,plInterlace) ) 

#define IVideology21B45_SetInterlace(This,lInterlace)	\
    ( (This)->lpVtbl -> SetInterlace(This,lInterlace) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology21B45_INTERFACE_DEFINED__ */


#ifndef __IVideology20C205_INTERFACE_DEFINED__
#define __IVideology20C205_INTERFACE_DEFINED__

/* interface IVideology20C205 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology20C205;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1e-3c8e-476c-9068-eb4555a99231")
    IVideology20C205 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendCommand( 
            /* [in] */ unsigned char command) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology20C205Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology20C205 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology20C205 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology20C205 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SendCommand )( 
            IVideology20C205 * This,
            /* [in] */ unsigned char command);
        
        END_INTERFACE
    } IVideology20C205Vtbl;

    interface IVideology20C205
    {
        CONST_VTBL struct IVideology20C205Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology20C205_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology20C205_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology20C205_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology20C205_SendCommand(This,command)	\
    ( (This)->lpVtbl -> SendCommand(This,command) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology20C205_INTERFACE_DEFINED__ */


#ifndef __IVideology2xC215_INTERFACE_DEFINED__
#define __IVideology2xC215_INTERFACE_DEFINED__

/* interface IVideology2xC215 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVideology2xC215;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926ddb1f-3c8e-476c-9068-eb4555a99231")
    IVideology2xC215 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInterlace( 
            /* [retval][out] */ eInterlaceOptions *plInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterlace( 
            /* [in] */ eInterlaceOptions lInterlace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMirror( 
            /* [retval][out] */ long *plMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMirror( 
            /* [in] */ long lMirroring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlip( 
            /* [retval][out] */ long *plFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlip( 
            /* [in] */ long lFlipping) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompSize( 
            /* [retval][out] */ eBlcSize *plBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompSize( 
            /* [in] */ eBlcSize lBlcSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompPosition( 
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompPosition( 
            /* [in] */ short wHoriz,
            /* [in] */ short wVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBacklightCompWeight( 
            /* [retval][out] */ long *plBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBacklightCompWeight( 
            /* [in] */ long lBlcWeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAGC( 
            /* [retval][out] */ long *plGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAGC( 
            /* [in] */ long lGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEdgeEnhancement( 
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEdgeEnhancement( 
            /* [in] */ short pwHoriz,
            /* [in] */ short pwVert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWhiteBalanceMode( 
            /* [retval][out] */ eWhiteBalanceMode *plMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWhiteBalanceMode( 
            /* [in] */ eWhiteBalanceMode lMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWBGains( 
            /* [out] */ short *pwRed,
            /* [out] */ short *pwBlue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWBGains( 
            /* [in] */ short wRed,
            /* [in] */ short wBlue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWideDynamicRange( 
            /* [retval][out] */ short *pwMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWideDynamicRange( 
            /* [in] */ short wMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetYGain( 
            /* [retval][out] */ short *pwGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetYGain( 
            /* [in] */ short wGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCGain( 
            /* [retval][out] */ short *pwGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCGain( 
            /* [in] */ short wGain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVideology2xC215Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideology2xC215 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideology2xC215 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideology2xC215 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInterlace )( 
            IVideology2xC215 * This,
            /* [retval][out] */ eInterlaceOptions *plInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *SetInterlace )( 
            IVideology2xC215 * This,
            /* [in] */ eInterlaceOptions lInterlace);
        
        HRESULT ( STDMETHODCALLTYPE *GetMirror )( 
            IVideology2xC215 * This,
            /* [retval][out] */ long *plMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *SetMirror )( 
            IVideology2xC215 * This,
            /* [in] */ long lMirroring);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlip )( 
            IVideology2xC215 * This,
            /* [retval][out] */ long *plFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlip )( 
            IVideology2xC215 * This,
            /* [in] */ long lFlipping);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompSize )( 
            IVideology2xC215 * This,
            /* [retval][out] */ eBlcSize *plBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompSize )( 
            IVideology2xC215 * This,
            /* [in] */ eBlcSize lBlcSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompPosition )( 
            IVideology2xC215 * This,
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompPosition )( 
            IVideology2xC215 * This,
            /* [in] */ short wHoriz,
            /* [in] */ short wVert);
        
        HRESULT ( STDMETHODCALLTYPE *GetBacklightCompWeight )( 
            IVideology2xC215 * This,
            /* [retval][out] */ long *plBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *SetBacklightCompWeight )( 
            IVideology2xC215 * This,
            /* [in] */ long lBlcWeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetAGC )( 
            IVideology2xC215 * This,
            /* [retval][out] */ long *plGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetAGC )( 
            IVideology2xC215 * This,
            /* [in] */ long lGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetEdgeEnhancement )( 
            IVideology2xC215 * This,
            /* [out] */ short *pwHoriz,
            /* [out] */ short *pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *SetEdgeEnhancement )( 
            IVideology2xC215 * This,
            /* [in] */ short pwHoriz,
            /* [in] */ short pwVert);
        
        HRESULT ( STDMETHODCALLTYPE *GetWhiteBalanceMode )( 
            IVideology2xC215 * This,
            /* [retval][out] */ eWhiteBalanceMode *plMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetWhiteBalanceMode )( 
            IVideology2xC215 * This,
            /* [in] */ eWhiteBalanceMode lMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetWBGains )( 
            IVideology2xC215 * This,
            /* [out] */ short *pwRed,
            /* [out] */ short *pwBlue);
        
        HRESULT ( STDMETHODCALLTYPE *SetWBGains )( 
            IVideology2xC215 * This,
            /* [in] */ short wRed,
            /* [in] */ short wBlue);
        
        HRESULT ( STDMETHODCALLTYPE *GetWideDynamicRange )( 
            IVideology2xC215 * This,
            /* [retval][out] */ short *pwMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetWideDynamicRange )( 
            IVideology2xC215 * This,
            /* [in] */ short wMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetYGain )( 
            IVideology2xC215 * This,
            /* [retval][out] */ short *pwGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetYGain )( 
            IVideology2xC215 * This,
            /* [in] */ short wGain);
        
        HRESULT ( STDMETHODCALLTYPE *GetCGain )( 
            IVideology2xC215 * This,
            /* [retval][out] */ short *pwGain);
        
        HRESULT ( STDMETHODCALLTYPE *SetCGain )( 
            IVideology2xC215 * This,
            /* [in] */ short wGain);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IVideology2xC215 * This);
        
        END_INTERFACE
    } IVideology2xC215Vtbl;

    interface IVideology2xC215
    {
        CONST_VTBL struct IVideology2xC215Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideology2xC215_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVideology2xC215_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVideology2xC215_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVideology2xC215_GetInterlace(This,plInterlace)	\
    ( (This)->lpVtbl -> GetInterlace(This,plInterlace) ) 

#define IVideology2xC215_SetInterlace(This,lInterlace)	\
    ( (This)->lpVtbl -> SetInterlace(This,lInterlace) ) 

#define IVideology2xC215_GetMirror(This,plMirroring)	\
    ( (This)->lpVtbl -> GetMirror(This,plMirroring) ) 

#define IVideology2xC215_SetMirror(This,lMirroring)	\
    ( (This)->lpVtbl -> SetMirror(This,lMirroring) ) 

#define IVideology2xC215_GetFlip(This,plFlipping)	\
    ( (This)->lpVtbl -> GetFlip(This,plFlipping) ) 

#define IVideology2xC215_SetFlip(This,lFlipping)	\
    ( (This)->lpVtbl -> SetFlip(This,lFlipping) ) 

#define IVideology2xC215_GetBacklightCompSize(This,plBlcSize)	\
    ( (This)->lpVtbl -> GetBacklightCompSize(This,plBlcSize) ) 

#define IVideology2xC215_SetBacklightCompSize(This,lBlcSize)	\
    ( (This)->lpVtbl -> SetBacklightCompSize(This,lBlcSize) ) 

#define IVideology2xC215_GetBacklightCompPosition(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> GetBacklightCompPosition(This,pwHoriz,pwVert) ) 

#define IVideology2xC215_SetBacklightCompPosition(This,wHoriz,wVert)	\
    ( (This)->lpVtbl -> SetBacklightCompPosition(This,wHoriz,wVert) ) 

#define IVideology2xC215_GetBacklightCompWeight(This,plBlcWeight)	\
    ( (This)->lpVtbl -> GetBacklightCompWeight(This,plBlcWeight) ) 

#define IVideology2xC215_SetBacklightCompWeight(This,lBlcWeight)	\
    ( (This)->lpVtbl -> SetBacklightCompWeight(This,lBlcWeight) ) 

#define IVideology2xC215_GetAGC(This,plGain)	\
    ( (This)->lpVtbl -> GetAGC(This,plGain) ) 

#define IVideology2xC215_SetAGC(This,lGain)	\
    ( (This)->lpVtbl -> SetAGC(This,lGain) ) 

#define IVideology2xC215_GetEdgeEnhancement(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> GetEdgeEnhancement(This,pwHoriz,pwVert) ) 

#define IVideology2xC215_SetEdgeEnhancement(This,pwHoriz,pwVert)	\
    ( (This)->lpVtbl -> SetEdgeEnhancement(This,pwHoriz,pwVert) ) 

#define IVideology2xC215_GetWhiteBalanceMode(This,plMode)	\
    ( (This)->lpVtbl -> GetWhiteBalanceMode(This,plMode) ) 

#define IVideology2xC215_SetWhiteBalanceMode(This,lMode)	\
    ( (This)->lpVtbl -> SetWhiteBalanceMode(This,lMode) ) 

#define IVideology2xC215_GetWBGains(This,pwRed,pwBlue)	\
    ( (This)->lpVtbl -> GetWBGains(This,pwRed,pwBlue) ) 

#define IVideology2xC215_SetWBGains(This,wRed,wBlue)	\
    ( (This)->lpVtbl -> SetWBGains(This,wRed,wBlue) ) 

#define IVideology2xC215_GetWideDynamicRange(This,pwMode)	\
    ( (This)->lpVtbl -> GetWideDynamicRange(This,pwMode) ) 

#define IVideology2xC215_SetWideDynamicRange(This,wMode)	\
    ( (This)->lpVtbl -> SetWideDynamicRange(This,wMode) ) 

#define IVideology2xC215_GetYGain(This,pwGain)	\
    ( (This)->lpVtbl -> GetYGain(This,pwGain) ) 

#define IVideology2xC215_SetYGain(This,wGain)	\
    ( (This)->lpVtbl -> SetYGain(This,wGain) ) 

#define IVideology2xC215_GetCGain(This,pwGain)	\
    ( (This)->lpVtbl -> GetCGain(This,pwGain) ) 

#define IVideology2xC215_SetCGain(This,wGain)	\
    ( (This)->lpVtbl -> SetCGain(This,wGain) ) 

#define IVideology2xC215_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVideology2xC215_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Videology20K1XXPage;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d0b-f8b0-4a65-aefd-0da48c3e2de5")
Videology20K1XXPage;
#endif

EXTERN_C const CLSID CLSID_VideologyCommonPage;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d0c-f8b0-4a65-aefd-0da48c3e2de5")
VideologyCommonPage;
#endif

EXTERN_C const CLSID CLSID_Videology24B13Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d0d-f8b0-4a65-aefd-0da48c3e2de5")
Videology24B13Page;
#endif

EXTERN_C const CLSID CLSID_Videology24C13Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d0e-f8b0-4a65-aefd-0da48c3e2de5")
Videology24C13Page;
#endif

EXTERN_C const CLSID CLSID_Videology24C13PanPage;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d0f-f8b0-4a65-aefd-0da48c3e2de5")
Videology24C13PanPage;
#endif

EXTERN_C const CLSID CLSID_Videology60V002Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d10-f8b0-4a65-aefd-0da48c3e2de5")
Videology60V002Page;
#endif

EXTERN_C const CLSID CLSID_Videology21B45Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d11-f8b0-4a65-aefd-0da48c3e2de5")
Videology21B45Page;
#endif

EXTERN_C const CLSID CLSID_Videology20C205Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d12-f8b0-4a65-aefd-0da48c3e2de5")
Videology20C205Page;
#endif

EXTERN_C const CLSID CLSID_Videology2xC215Page;

#ifdef __cplusplus

class DECLSPEC_UUID("35793d13-f8b0-4a65-aefd-0da48c3e2de5")
Videology2xC215Page;
#endif
#endif /* __VideologyInterface_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


