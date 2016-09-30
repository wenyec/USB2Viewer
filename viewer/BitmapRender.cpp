//------------------------------------------------------------------------------
// File: BitmapRenderer.cpp
//
// Desc: A very simple rendering filter that passes samples to a callback
//     routine supplied by the caller.  This is an interesting example
//     because the filter is entirely local to our program; it is not
//     registered at all.  Many people are unaware this is even possible.
//
// Tim Roberts, Providenza & Boekelheide, Inc.
// Copyright (C) 2007, Videology Imaging Systems, Inc.
//------------------------------------------------------------------------------


// Summary
//
// This is a sample DirectShow video renderer - the filter is based on the
// CBaseVideoRenderer base class. The base class handles all the seeking,
// synchronization and quality management necessary for video renderers.
// We override the DoRenderSample method so we can pass frames back to 
// our caller.
//

#include "stdafx.h"
#include "BitmapRender.h"

#include <initguid.h>
#include <olectl.h>

// GUIDs

/* b3ff0a44-2559-4b74-89bf-e6b2f4744fa1 */
DEFINE_GUID(CLSID_BitmapRenderer, 
0xb3ff0a44, 0x2559, 0x4b74, 0x89, 0xbf, 0xe6, 0xb2, 0xf4, 0x74, 0x4f, 0xa1);



//
// CreateInstance
//
// This can be used to build instances of the filter, although you might
// as well use operator new directly.
//
CUnknown * WINAPI CBitmapRenderer::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CBitmapRenderer(NAME("Bitmap Video Renderer"),pUnk,phr);

}


#pragma warning(disable:4355)

//
// Constructor
//
CBitmapRenderer::CBitmapRenderer(
    TCHAR *pName,
    LPUNKNOWN pUnk,
    HRESULT *phr
)
    : CBaseVideoRenderer(CLSID_BitmapRenderer,pName,pUnk,phr)
    , m_InputPin(NAME("Video Pin"),this,&m_InterfaceLock,phr,L"Input")
{
    TRACE( __FUNCTION__ "\n" );

    // Store the video input pin.  Once we do this, CBaseRenderer will 
    // handle all of the pin enumeration for us.

    m_pInputPin = &m_InputPin;

    // Reset the current video size.

    m_VideoSize.cx = 0;
    m_VideoSize.cy = 0;
}


//
// Destructor
//
CBitmapRenderer::~CBitmapRenderer()
{
    TRACE( __FUNCTION__ "\n" );
    m_pInputPin = NULL;
}


//
// CheckMediaType
//
// Check the proposed video media type.  We are fairly picky.
//
HRESULT CBitmapRenderer::CheckMediaType(const CMediaType *pmtIn)
{
    TRACE( __FUNCTION__ "\n" );
    return
        (pmtIn->majortype == MEDIATYPE_Video)
        &&
        (pmtIn->subtype == MEDIASUBTYPE_RGB24)
            ? S_OK
            : E_FAIL;
}



//
// DoRenderSample
//
// Send the sample to the caller for processing.
//
HRESULT CBitmapRenderer::DoRenderSample(IMediaSample *pMediaSample)
{
    TRACE( __FUNCTION__ "\n" );
    if( m_Callback )
        return m_Callback->Sample( pMediaSample );
    return S_OK;
}



//
// SetMediaType
//
// We store a copy of the media type used for the connection in the renderer
// because it is required by many different parts of the running renderer.
// This can be called when we come to draw a media sample that has a format
// change with it.
//
HRESULT CBitmapRenderer::SetMediaType(const CMediaType *pmt)
{
    TRACE( __FUNCTION__ "\n" );
    CheckPointer(pmt,E_POINTER);

    CAutoLock cInterfaceLock(&m_InterfaceLock);
    m_mtIn = *pmt;

    VIDEOINFOHEADER *pVideoInfo = (VIDEOINFOHEADER *) m_mtIn.Format();
    if( !pVideoInfo )
        return E_POINTER;

    m_VideoSize.cx = pVideoInfo->bmiHeader.biWidth;
    m_VideoSize.cy = pVideoInfo->bmiHeader.biHeight;
    return NOERROR;

} // SetMediaType


//
// BreakConnect
//
// This is called when a connection or an attempted connection is terminated
// and lets us to reset the connection flag held by the base class renderer.
// The filter object may be hanging onto an image to use for refreshing the
// video window so that must be freed (the allocator decommit may be waiting
// for that image to return before completing) then we must also uninstall
// any palette we were using, reset anything set with the control interfaces
// then set our overall state back to disconnected ready for the next time.

HRESULT CBitmapRenderer::BreakConnect()
{
    TRACE( __FUNCTION__ "\n" );
    CAutoLock cInterfaceLock(&m_InterfaceLock);

    // Check we are in a valid state

    HRESULT hr = CBaseVideoRenderer::BreakConnect();
    if (FAILED(hr)) {
        return hr;
    }

    m_mtIn.ResetFormatBuffer();

    return NOERROR;

} // BreakConnect


//
// CompleteConnect
//
// When we complete connection we need to see if the video has changed sizes
// If it has then we activate the window and reset the source and destination
// rectangles. If the video is the same size then we bomb out early. By doing
// this we make sure that temporary disconnections such as when we go into a
// fullscreen mode do not cause unnecessary property changes. The basic ethos
// is that all properties should be persistent across connections if possible
//
HRESULT CBitmapRenderer::CompleteConnect(IPin *pReceivePin)
{
    TRACE( __FUNCTION__ "\n" );
    CAutoLock cInterfaceLock(&m_InterfaceLock);

    CBaseVideoRenderer::CompleteConnect(pReceivePin);

    // Has the video size changed between connections

    VIDEOINFOHEADER *pVideoInfo = (VIDEOINFOHEADER *) m_mtIn.Format();
    if(
        (pVideoInfo->bmiHeader.biWidth == m_VideoSize.cx) &&
        (pVideoInfo->bmiHeader.biHeight == m_VideoSize.cy) 
    )
    {
        return NOERROR;
    }

    // Set them for the current video dimensions

    m_VideoSize.cx = pVideoInfo->bmiHeader.biWidth;
    m_VideoSize.cy = pVideoInfo->bmiHeader.biHeight;

    return NOERROR;

} // CompleteConnect


//
// OnReceiveFirstSample
//
// Use the image just delivered to display a poster frame
//
void CBitmapRenderer::OnReceiveFirstSample(IMediaSample *pMediaSample)
{
    ASSERT(pMediaSample);
    DoRenderSample(pMediaSample);
}


// Constructor

CVideoInputPin::CVideoInputPin(
    TCHAR *pObjectName,
    CBitmapRenderer *pRenderer,
    CCritSec *pInterfaceLock,
    HRESULT *phr,
    LPCWSTR pPinName
)
    : CRendererInputPin(pRenderer,phr,pPinName)
    , m_pRenderer(pRenderer)
    , m_pInterfaceLock(pInterfaceLock)
{
    TRACE( __FUNCTION__ "\n" );
    ASSERT(m_pRenderer);
    ASSERT(pInterfaceLock);
}

HRESULT
CVideoInputPin::GetMediaType(
    int iPosition,
    CMediaType* pMediaType 
)
{
    TRACE( __FUNCTION__ "\n" );
    if( iPosition > 0 )
        return VFW_S_NO_MORE_ITEMS;

    pMediaType->SetType( &MEDIATYPE_Video );
    pMediaType->SetSubtype( &MEDIASUBTYPE_RGB24 );
    pMediaType->SetFormatType( &GUID_NULL );
    return S_OK;
}

