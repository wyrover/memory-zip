#include "stdafx.h"
#include <Windows.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

#define FLUSH_SIZE (1024*1024*4)

DECLARE_HANDLE(HZIP);

#define DllExport  __declspec( dllimport )

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

int _tmain(int argc, _TCHAR* argv[])
{
	HZIP hz;
	DWORD zr;
	void * pBuf;
	unsigned long size;

	struct timeb tBuffer;
	struct tm *pt;

	ftime(&tBuffer);
	pt = localtime(&tBuffer.time);
	_tprintf(_T("%02d:%02d:%02d.%03hu\n"), pt->tm_hour, pt->tm_min, pt->tm_sec, tBuffer.millitm);

	// zip 파일 열기
	hz = Open_Zip();

	if( 0 == hz ) {
		_tprintf(_T("Open_Zip error\n"));
		return -1;
	}
	// 파일 추가 // 반복
	TCHAR tFName[1024];

	HANDLE hFile = CreateFile( _T("a.zip"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	DWORD dwWrite;

	zr = Add_File_Zip( hz, _T("Image/smartmemo.gif"), (const TCHAR *)_T("Z:/Downloads/title.gif") );
	if( zr != 0 ) _tprintf(_T("Add_File_Zip error\n"));	
	zr = Get_Buf_Zip( hz, &pBuf, &size );
	if( zr != 0 ) _tprintf(_T("Get_Buf_Zip error\n"));
	WriteFile( hFile, pBuf, size, &dwWrite, NULL );
	Set_Flush_Zip( hz, size );

	zr = Add_File_Zip( hz, _T("가나다라마바사자차카다파하가나다라마바사자차카다파하가나다라마바사자차카다파하가나다라마바사자차카다파하/가나다라마바사자차카다파하가나다라마바사자차카다파하가나다라마바사자차카다파하가나다라마바사자차카다파하/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb.html"), (const TCHAR *)_T("Z:/Downloads/가나다라마바사/aaaa.html") );
	if( zr != 0 ) _tprintf(_T("Add_File_Zip error\n"));	
	zr = Get_Buf_Zip( hz, &pBuf, &size );
	if( zr != 0 ) _tprintf(_T("Get_Buf_Zip error\n"));
	WriteFile( hFile, pBuf, size, &dwWrite, NULL );
	Set_Flush_Zip( hz, size );

	zr = Add_File_Zip( hz, _T("29435.jpg"), (const TCHAR *)_T("Z:/Downloads/29435.jpg") );
	if( zr != 0 ) _tprintf(_T("Add_File_Zip error\n"));	
	zr = Get_Buf_Zip( hz, &pBuf, &size );
	if( zr != 0 ) _tprintf(_T("Get_Buf_Zip error\n"));
	WriteFile( hFile, pBuf, size, &dwWrite, NULL );
	Set_Flush_Zip( hz, size );

	zr = Get_LastBuf_Zip( hz, &pBuf, &size );
	if( zr != 0 ) _tprintf(_T("Get_LastBuf_Zip error\n"));
	WriteFile( hFile, pBuf, size, &dwWrite, NULL );
	Set_Flush_Zip( hz, size );

	CloseHandle(hFile);

	// 파일 닫기
	Close_Zip(hz);

	ftime(&tBuffer);
	pt = localtime(&tBuffer.time);
	_tprintf(_T("%02d:%02d:%02d.%03hu\n"), pt->tm_hour, pt->tm_min, pt->tm_sec, tBuffer.millitm);

	return 0;
}

