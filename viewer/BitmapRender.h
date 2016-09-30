//------------------------------------------------------------------------------
// File: BitmapRender.h
//
// Desc: Very simple renderer that calls a callback when a sample is
//     received.  Kind of like the sample grabber, except we are a
//     renderer instead of a transform.
//
// Tim Roberts, Providenza & Boekelheide, Inc.
// Copyright (c) 2007, Videology Imaging Solutions.
//------------------------------------------------------------------------------

#pragma once

// The caller must implement this interface to get the samples.

interface IBitmapCallback
{
public:
	virtual HRESULT Sample( IMediaSample* sample ) = 0;
};


// Forward declarations

class CBitmapRenderer;
class CVideoInputPin;



// This class supports the renderer input pin.  It's only real behavior
// is to return our preferred media type.

class CVideoInputPin 
    : public CRendererInputPin
{
    CBitmapRenderer *m_pRenderer;       // The renderer that owns us
    CCritSec *m_pInterfaceLock;         // Main filter critical section

public:

    // Constructor

    CVideoInputPin(
        TCHAR *pObjectName,             // Object string description
        CBitmapRenderer *pRenderer,     // Used to delegate locking
        CCritSec *pInterfaceLock,       // Main critical section
        HRESULT *phr,                   // OLE failure return code
        LPCWSTR pPinName);              // This pins identification

    virtual HRESULT GetMediaType( int iPosition, CMediaType* pMediaType );
};


// This is the COM object that represents a simple rendering filter. It
// supports IBaseFilter and IMediaFilter and a single input stream (pin)
// The classes that support these interfaces have nested scope. NOTE the
// nested class objects are passed a pointer to their owning renderer
// when they are created but they should not use it during construction.

class CBitmapRenderer 
    : public CBaseVideoRenderer
{
public:

    // Constructor and destructor

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN, HRESULT *);
    CBitmapRenderer(TCHAR *pName,LPUNKNOWN pUnk,HRESULT *phr);
    ~CBitmapRenderer();

    DECLARE_IUNKNOWN

    void SetCallback( IBitmapCallback* pcb )
    {
        m_Callback = pcb;
    }

    // Override these from the filter and renderer classes.  I strongly
    // suspect we don't need BreakConnect/CompleteConnect either.

    HRESULT BreakConnect();
    HRESULT CompleteConnect(IPin *pReceivePin);
    HRESULT SetMediaType(const CMediaType *pmt);
    HRESULT CheckMediaType(const CMediaType *pmtIn);
    HRESULT DoRenderSample(IMediaSample *pMediaSample);
    void OnReceiveFirstSample(IMediaSample *pMediaSample);

public:
    CVideoInputPin  m_InputPin;        // IPin based interfaces
    CMediaType      m_mtIn;            // Source connection media type
    SIZE            m_VideoSize;       // Size of the current video stream
    IBitmapCallback* m_Callback;

}; // CBitmapRenderer

