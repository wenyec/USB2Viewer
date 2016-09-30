#include <atlfile.h>

// CFormattedFile
//
// A class derived from CAtlFile that understands how to do printfs.

class CFormattedFile
    : public CAtlFile
{
public:
    CFormattedFile() throw()
    {
    }
    CFormattedFile( __in CFormattedFile& file ) throw() 
        : CAtlFile( file )  // Transfers ownership
    {
    }
    explicit CFormattedFile( __in HANDLE hFile ) throw() 
        : CAtlFile( hFile )  // Takes ownership
    {
    }

    void Printf( __in __format_string CStringA::PCXSTR pszFormat, ... )
    {
        // You could argue that this would be slightly more efficient by
        // skipping the CString and calling _vscprintf, malloc, vsprintf, free
        // on our own.
        //
        // Or CString::StrTraits::GetFormattedLength and 
        // CString::StrTraits::Format, which are inlines for those.
        //
        // Note that this is hardcoded to ANSI even if Unicode is defined.

        if( !m_h )
            return;

        va_list args;
        va_start( args, pszFormat );
        CStringA sz;
        sz.FormatV( pszFormat, args );
        va_end( args );
        Write( sz.GetBuffer(), sz.GetLength() );
    }
};
