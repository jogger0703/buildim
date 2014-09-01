#include "char_operation.h"
#include <tchar.h>
#include <Windows.h>


// std::string mb2utf8(const char* src, int len)
// {
// 	int nLen = MultiByteToWideChar(CP_ACP, 0, src, len, NULL, 0);
// }

/*
** Convert a UTF-8 string to microsoft unicode (UTF-16?). 
**
** Space to hold the returned string is obtained from malloc.
*/
static WCHAR *utf8ToUnicode(const char *zFilename, int len){
	int nChar;
	WCHAR *zWideFilename;

	nChar = MultiByteToWideChar(CP_UTF8, 0, zFilename, len, NULL, 0);
	zWideFilename = (WCHAR*)malloc((nChar+1)*sizeof(zWideFilename[0]));
	if( zWideFilename==0 ){
		return 0;
	}
	nChar = MultiByteToWideChar(CP_UTF8, 0, zFilename, len, zWideFilename, nChar);
	if( nChar==0 ){
		free(zWideFilename);
		zWideFilename = 0;
	}
	zWideFilename[nChar] = '\0';
	return zWideFilename;
}

/*
** Convert microsoft unicode to multibyte character string, based on the
** user's Ansi codepage.
**
** Space to hold the returned string is obtained from
** malloc().
*/
static char *unicodeToMbcs(const WCHAR *zWideFilename, int len){
	int nByte;
	char *zFilename;
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;

	nByte = WideCharToMultiByte(codepage, 0, zWideFilename, len, 0, 0, 0, 0);
	zFilename = (char*)malloc(nByte+1);
	if( zFilename==0 ){
		return 0;
	}
	nByte = WideCharToMultiByte(codepage, 0, zWideFilename, len, zFilename, nByte,
		0, 0);
	if( nByte == 0 ){
		free(zFilename);
		zFilename = 0;
	}
	zFilename[nByte] = '\0';
	return zFilename;
}

/*
** Convert UTF-8 to multibyte character string.  Space to hold the 
** returned string is obtained from malloc().
*/
static char *utf8ToMbcs(const char *zFilename, int len){
	char *zFilenameMbcs;
	WCHAR *zTmpWide;

	zTmpWide = utf8ToUnicode(zFilename, len);
	if( zTmpWide==0 ){
		return 0;
	}
	zFilenameMbcs = unicodeToMbcs(zTmpWide, wcslen(zTmpWide));
	free(zTmpWide);
	return zFilenameMbcs;
}

/*
** Convert an ansi string to microsoft unicode, based on the
** current codepage settings for file apis.
** 
** Space to hold the returned string is obtained
** from malloc.
*/
static WCHAR *mbcsToUnicode(const char *zFilename, int len){
	int nByte;
	WCHAR *zMbcsFilename;
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;

	nByte = MultiByteToWideChar(codepage, 0, zFilename, len, NULL,0)*sizeof(WCHAR);
	zMbcsFilename = (WCHAR *)malloc( (nByte+1)*sizeof(zMbcsFilename[0]) );
	if( zMbcsFilename==0 ){
		return 0;
	}
	nByte = MultiByteToWideChar(codepage, 0, zFilename, len, zMbcsFilename, nByte);
	if( nByte==0 ){
		free(zMbcsFilename);
		zMbcsFilename = 0;
	}
	zMbcsFilename[nByte] = '\0';
	return zMbcsFilename;
}

/*
** Convert microsoft unicode to UTF-8.  Space to hold the returned string is
** obtained from malloc().
*/
static char *unicodeToUtf8(const WCHAR *zWideFilename, int len){
	int nByte;
	char *zFilename;

	nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, len, 0, 0, 0, 0);
	zFilename = (char *)malloc( nByte+1 );
	if( zFilename==0 ){
		return 0;
	}
	nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, len, zFilename, nByte,
		0, 0);
	if( nByte == 0 ){
		free(zFilename);
		zFilename = 0;
	}
	zFilename[nByte] = '\0';
	return zFilename;
}

static char * mbcs_to_utf8(const char *zFilename, int len){
	char *zFilenameUtf8;
	WCHAR *zTmpWide;

	zTmpWide = mbcsToUnicode(zFilename, len);
	if( zTmpWide==0 ){
		return 0;
	}
	zFilenameUtf8 = unicodeToUtf8(zTmpWide, len);
	free(zTmpWide);
	return zFilenameUtf8;
}


std::string ansi2utf8(const char* src, int len)
{
	char* utf8 = mbcs_to_utf8(src, len);
	std::string ret(utf8);
	free(utf8);

	return ret;
}
std::string utf82ansi(const char* src, int len)
{
	char* mbcs = utf8ToMbcs(src, len);
	std::string ret(mbcs);
	free(mbcs);

	return ret;
}