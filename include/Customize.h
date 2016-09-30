// Customize
//
// A singleton class for allowing generic dialog customization for an OEM.
// We search the directory containing out DLL for another DLL with an 
// extension of ".vrs" (Videology resources).  If found, we use it.

// TODO
// Should we load dialogs?  We could do about boxes that way.

#pragma once
#pragma warning(push)
#pragma warning(disable:4995)
#include <atlstr.h>
#pragma warning(pop)

// #define EXTRADEBUG

class CCustomize
{
    HINSTANCE m_hSelf;
    HINSTANCE m_hResource;
    CString m_DllPath;

public:
    CCustomize()
        : m_hSelf( 0 )
        , m_hResource( 0 )
    {
    }

    void Register( HMODULE self )
    {
        // Find OUR DLL.

        TCHAR sz[512];
        GetModuleFileName(self, sz, 512);
        PathRemoveFileSpec( sz );
        m_DllPath = sz;
        m_hSelf = (HINSTANCE)self;

        // Check for a resource DLL in the same directory.

        CString szResDll = m_DllPath + _T("\\*.vrs");
#ifdef EXTRADEBUG
        OutputDebugString( szResDll );
#endif

        WIN32_FIND_DATA wfd;
        HANDLE hfd = FindFirstFile( szResDll, &wfd );

        if( hfd != INVALID_HANDLE_VALUE )
        {
            // Found one!  Load it.

            szResDll.Delete( szResDll.GetLength()-5, 5 );
            szResDll += wfd.cFileName;
#ifdef EXTRADEBUG
            OutputDebugString( szResDll );
#endif
            m_hResource = (HINSTANCE)LoadLibrary( szResDll );
            FindClose( hfd );
            return;
        }
    
        // Check in SYSTEM32.

        GetSystemDirectory( sz, 512 );
        szResDll = sz;
        szResDll += "\\*.vrs";

        hfd = FindFirstFile( szResDll, &wfd );
        if( hfd != INVALID_HANDLE_VALUE )
        {
            szResDll.Delete( szResDll.GetLength()-5, 5 );
            szResDll += wfd.cFileName;
#ifdef EXTRADEBUG
            OutputDebugString( szResDll );
#endif
            m_hResource = (HINSTANCE)LoadLibrary( szResDll );
            FindClose( hfd );
            return;
        }
    }

    CString Get( int iResourceId )
    {
        CString sz;
        if( m_hResource )
            sz.LoadString( m_hResource, iResourceId );
        if( sz.IsEmpty() )
            sz.LoadString( m_hSelf, iResourceId );
        return sz;
    }

    int AsInteger( int iResourceId )
    {
        CString sz = Get(iResourceId);
        if( sz.Left(2) == "0x" )
            return _tcstol( sz, NULL, 16 );
        else
            return _tcstol( sz, NULL, 10 );
    }

    HBITMAP GetBitmap( int iResourceId )
    {
        HBITMAP bm = NULL;
        if( m_hResource )
            bm = LoadBitmap( m_hResource, MAKEINTRESOURCE(iResourceId) );
        if( !bm )
            bm = LoadBitmap( m_hSelf, MAKEINTRESOURCE(iResourceId) );
        return bm;
    }
};

extern CCustomize Custom;
