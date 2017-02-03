// ZipDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "zip.h"

#define DllExport   __declspec( dllexport )

#define INIT_BUFFER_SIZE	(1024*1024*16)

#ifdef __cplusplus
extern "C" {
#endif

DllExport HZIP Open_Zip();
DllExport HZIP OpenFile_Zip( const TCHAR * tPath );
DllExport VOID Close_Zip( HZIP hZip );
DllExport DWORD Add_Buf_Zip( HZIP hZip, const TCHAR * tPath, VOID * pData, unsigned int nLen );
DllExport DWORD Add_File_Zip( HZIP hZip, const TCHAR * tPath, const TCHAR * tFileName );
DllExport DWORD Get_Buf_Zip ( HZIP hZip, VOID ** ppData, unsigned long * pLen );
DllExport DWORD Get_LastBuf_Zip ( HZIP hZip, VOID ** ppData, unsigned long * pLen );
DllExport DWORD Get_BufSize_Zip ( HZIP hZip, unsigned long * pLen );
DllExport DWORD Set_Flush_Zip ( HZIP hZip, unsigned long len );

#ifdef __cplusplus
}
#endif

DllExport HZIP Open_Zip()
{
	return CreateZip(NULL, INIT_BUFFER_SIZE, NULL);
}

DllExport HZIP OpenFile_Zip( const TCHAR * tFile )
{
	return CreateZip( tFile , NULL);
}

DllExport VOID Close_Zip(HZIP hZip)
{
	if(hZip) CloseZip(hZip);
}

DllExport ZRESULT Add_Buf_Zip( HZIP hZip, const TCHAR * tPath, VOID * pData, unsigned int nLen ) 
{
	return ZipAdd( hZip, tPath, pData, nLen) ;
}

DllExport ZRESULT Add_File_Zip( HZIP hZip, const TCHAR * tPath, const TCHAR * tFileName ) 
{
	return ZipAdd( hZip, tPath, tFileName) ;
}

DllExport ZRESULT Get_Buf_Zip ( HZIP hZip, VOID ** ppData, unsigned long * pLen )
{
	return ZipGetMemory( hZip, ppData, pLen );
}

DllExport ZRESULT Get_LastBuf_Zip ( HZIP hZip, VOID ** ppData, unsigned long * pLen )
{
	return ZipGetLastMemory( hZip, ppData, pLen );
}

DllExport ZRESULT Get_BufSize_Zip ( HZIP hZip, unsigned long * pLen )
{
	return ZipGetMemorySize( hZip, pLen );
}

DllExport ZRESULT Set_Flush_Zip ( HZIP hZip, unsigned long len )
{
	return ZipFlushMemory( hZip, len );
}
